//
// Generated file, do not edit! Created by opp_msgc 4.3 from base/messages/data/airframe.msg.
//

#ifndef _AIRFRAME_M_H_
#define _AIRFRAME_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0403
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "twsndef.h"
// }}


namespace twsn {

/**
 * Class generated from <tt>base/messages/data/airframe.msg</tt> by opp_msgc.
 * <pre>
 * packet AirFrame {
 *     moduleid_t sender;
 *     moduleid_t receiver;
 *     int frameSize = 6; 
 * }
 * </pre>
 */
class AirFrame : public ::cPacket
{
  protected:
    twsn::moduleid_t sender_var;
    twsn::moduleid_t receiver_var;
    int frameSize_var;

  private:
    void copy(const AirFrame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AirFrame&);

  public:
    AirFrame(const char *name=NULL, int kind=0);
    AirFrame(const AirFrame& other);
    virtual ~AirFrame();
    AirFrame& operator=(const AirFrame& other);
    virtual AirFrame *dup() const {return new AirFrame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual twsn::moduleid_t& getSender();
    virtual const twsn::moduleid_t& getSender() const {return const_cast<AirFrame*>(this)->getSender();}
    virtual void setSender(const twsn::moduleid_t& sender);
    virtual twsn::moduleid_t& getReceiver();
    virtual const twsn::moduleid_t& getReceiver() const {return const_cast<AirFrame*>(this)->getReceiver();}
    virtual void setReceiver(const twsn::moduleid_t& receiver);
    virtual int getFrameSize() const;
    virtual void setFrameSize(int frameSize);
};

inline void doPacking(cCommBuffer *b, AirFrame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, AirFrame& obj) {obj.parsimUnpack(b);}

}; // end namespace twsn

#endif // _AIRFRAME_M_H_
