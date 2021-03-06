//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "apptrackingbs.h"
#include "apptrackingpkt_m.h"
#include "stathelper.h"
#include <fstream>

namespace twsn {

Define_Module(AppTrackingBS);

void AppTrackingBS::processTarPos(TargetPos &tp)
{
    // Store raw target position for reference
    rawTpList.push_back(tp);

    // Process data and collect traces
    if (traceList.size() == 0) {
        // Add new trace with this TargetPos
        TargetTrace trace(par("theta").doubleValue(), par("minDeltaT").doubleValue());
        trace.setId(numTrace);
        TargetPos filteredPos = trace.addTargetPos(tp);

        // Record track error
        emit(sigTrackError, distance(filteredPos.getCoord(), filteredPos.getTrueCoord()));

        traceList.push_back(trace);
        numTrace++;
        std::cerr << "First trace, ID " << trace.getId() << endl;
    } else {
        // Add TargetPos to most likely trace
        double mostLikely = -1; // Unacceptable
        TargetTrace *mostLikelyTrace = NULL;
        double likely;

        int id = 0;
        int mostLikelyId = 0;
        for (std::list<TargetTrace>::iterator it = traceList.begin(); it != traceList.end(); it++) {
            likely = (*it).checkLikelihood(tp, par("distanceThreshold").doubleValue(),
                    par("timeThreshold").doubleValue());
            if (likely >= 0) {
                if (mostLikely < 0 || likely < mostLikely) {
                    mostLikely = likely;
                    mostLikelyTrace = &(*it);
                    mostLikelyId = id;
                }
            }
            id++;
        }

        if (mostLikelyTrace != NULL) {
            TargetPos filteredPos = mostLikelyTrace->addTargetPos(tp);
            std::cerr << "Add to trace ID " << mostLikelyId << endl;

            // Record track error
            emit(sigTrackError, distance(filteredPos.getCoord(), filteredPos.getTrueCoord()));
        } else {
            // Add new trace with this TargetPos
            TargetTrace trace(par("theta").doubleValue(), par("minDeltaT").doubleValue());
            trace.setId(numTrace);
            TargetPos filteredPos = trace.addTargetPos(tp);

            // Record track error
            emit(sigTrackError, distance(filteredPos.getCoord(), filteredPos.getTrueCoord()));

            traceList.push_back(trace);
            numTrace++;
            std::cerr << "New trace, ID " << trace.getId() << endl;
        }
    }
}

void AppTrackingBS::cleanJunk()
{
    std::list<TargetTrace>::iterator ttIt = traceList.begin();

    while (ttIt != traceList.end()) {
        double lastTimestamp = (*ttIt).getPath().back().getTimestamp();

        if (simTime() - lastTimestamp > par("minJunkTraceOld").doubleValue()
                && (*ttIt).getPathLen() <= par("maxJunkTraceLen").longValue()) {
            std::cerr << "Cleaning trace ID " << (*ttIt).getId() << endl;
            ttIt = traceList.erase(ttIt);
        } else {
            ttIt++;
        }
    }
}

void AppTrackingBS::output()
{
    cConfigurationEx *configEx = ev.getConfigEx();
    // Output raw data
    std::ostringstream ossRaw;
    std::ofstream outRaw;
    // Output all trace
    std::ostringstream ossAll;
    std::ofstream outAll;
    // Output individual trace
    std::ostringstream ossTrace;
    std::ofstream outTrace;
    std::list<TargetTrace>::iterator ttIt;
    std::list<TargetPos> path;
    std::list<TargetPos>::iterator tpIt;
    double x, y, t;

    // Output raw data
    // =================
    ossRaw.seekp(0);
    ossRaw << "results/bs_output/";
    ossRaw << configEx->getActiveConfigName() << "_raw.data\0";
    outRaw.open(ossRaw.str().c_str(), std::ios::out | std::ios::trunc);

    if (outRaw) {
        outRaw << "# Config: " << configEx->getActiveConfigName() << endl;
        outRaw << "# Raw positioning data" << endl;
        outRaw << "# x y t" << endl;
        for (tpIt = rawTpList.begin(); tpIt != rawTpList.end(); tpIt++) {
            x = (*tpIt).getCoord().getX();
            y = (*tpIt).getCoord().getY();
            t = (*tpIt).getTimestamp();
            outRaw << x << ' ' << y << ' ' << t << endl;
        }
    } else {
        std::cerr << "Cannot open file " << ossRaw.str() << endl;
    }
    outRaw.close();

    // Output trace data
    // =================
    ossAll.seekp(0);
    ossAll << "results/bs_output/";
    ossAll << configEx->getActiveConfigName() << "_trace_all.data\0";
    outAll.open(ossAll.str().c_str(), std::ios::out | std::ios::trunc);

    if (outAll) {
        outAll << "# Config: " << configEx->getActiveConfigName() << endl;
        outAll << "# All traces sequenced" << endl;
        outAll << "# x y t" << endl;
    } else {
        std::cerr << "Cannot open file " << ossAll.str() << endl;
    }

    for (ttIt = traceList.begin(); ttIt != traceList.end(); ttIt++) {
        ossTrace.seekp(0);
        ossTrace << "results/bs_output/";
        ossTrace << configEx->getActiveConfigName() << "_trace_" << (*ttIt).getId() << ".data\0";
        outTrace.open(ossTrace.str().c_str(), std::ios::out | std::ios::trunc);

        if (!outTrace) {
            std::cerr << "Cannot open file " << ossTrace.str() << endl;
        } else {
            outTrace << "# Config: " << configEx->getActiveConfigName() << endl;
            outTrace << "# Trace ID " << (*ttIt).getId() << endl;
            outTrace << "# x y t" << endl;

            path = (*ttIt).getPath();
            for (tpIt = path.begin(); tpIt != path.end(); tpIt++) {
                x = (*tpIt).getCoord().getX();
                y = (*tpIt).getCoord().getY();
                t = (*tpIt).getTimestamp();
                outTrace << x << ' ' << y << ' ' << t << endl;
            }
            outTrace.close();
        }

        if (!outAll) {
            std::cerr << "Cannot open file " << ossAll.str() << endl;
        } else {
            path = (*ttIt).getPath();
            for (tpIt = path.begin(); tpIt != path.end(); tpIt++) {
                x = (*tpIt).getCoord().getX();
                y = (*tpIt).getCoord().getY();
                t = (*tpIt).getTimestamp();
                outAll << x << ' ' << y << ' ' << t << endl;
            }
        }
    }
    outAll.close();
}

void AppTrackingBS::initialize()
{
    numTrace = 0;
    sigEtoEDelay = registerSignal("sigEtoEDelay");
    sigTrackError = registerSignal("sigTrackError");

    /* Clear output folder */
    cConfigurationEx *configEx = ev.getConfigEx();
    std::ostringstream ossCmd;
    ossCmd.seekp(0);

#if defined(_WIN32)
    ossCmd << "del .\\results\\bs_output\\" << configEx->getActiveConfigName() << "_*" << '\0';
#else
    ossCmd << "exec rm ./results/bs_output/" << configEx->getActiveConfigName() << "_*" << '\0';
#endif

    system(ossCmd.str().c_str());
}

void AppTrackingBS::handleLowerMsg(cMessage* msg)
{
    StatHelper *sh = check_and_cast<StatHelper*>(getModuleByPath("statHelper"));
    AppTrackingPkt *pkt = check_and_cast<AppTrackingPkt*>(msg);

    if (pkt->getPktType() == AT_TARGET_POSITION) {
        AT_TargetPosPkt *tpPkt = check_and_cast<AT_TargetPosPkt*>(msg);
        TargetPos tp = tpPkt->getTargetPos();

        // Check timestamp before using packet
        double delay = simTime().dbl() - tp.getTimestamp();
        if (delay > par("timeThreshold").doubleValue()) {
            printError(LV_DEBUG, "Too long delay");
            // Discard packet
            sh->countLostNetPkt();
        } else {
            // Record end-to-end delay
            emit(sigEtoEDelay, delay);

            // Count delivered relay packet
            sh->countDeliveredRelayPkt();

            // Process data
            processTarPos(tp);
            cleanJunk();
        }
    }
    delete msg;
}

void AppTrackingBS::finish()
{
    // Clean junk without considering old
    std::list<TargetTrace>::iterator ttIt = traceList.begin();
    while (ttIt != traceList.end()) {
        if ((*ttIt).getPathLen() <= par("maxJunkTraceLen").longValue()) {
            std::cerr << "Cleaning trace ID " << (*ttIt).getId() << endl;
            ttIt = traceList.erase(ttIt);
        } else {
            ttIt++;
        }
    }

    /* Tracking result can be outputted in real-time. However, for efficiency, we output all at
     * finish of simulation. */
    output();
}

}  // namespace twsn
