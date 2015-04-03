//
// Generated file, do not edit! Created by opp_msgc 4.4 from base/messages/mac802154pkt.msg.
//

#ifndef _TWSN_MAC802154PKT_M_H_
#define _TWSN_MAC802154PKT_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0404
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "twsndef.h"
	#include "macpkt_m.h"
// }}


namespace twsn {

/**
 * Enum generated from <tt>base/messages/mac802154pkt.msg</tt> by opp_msgc.
 * <pre>
 * enum Mac802154PktType {
 *     MAC802154_BEACON = 0; 
 *     MAC802154_DATA = 1; 
 *     MAC802154_ACK = 2; 
 *     MAC802154_CMD = 3; 
 *     
 *     MAC802154_PREAMBLE = 4;
 * };
 * </pre>
 */
enum Mac802154PktType {
    MAC802154_BEACON = 0,
    MAC802154_DATA = 1,
    MAC802154_ACK = 2,
    MAC802154_CMD = 3,
    MAC802154_PREAMBLE = 4
};

/**
 * Class generated from <tt>base/messages/mac802154pkt.msg</tt> by opp_msgc.
 * <pre>
 * packet Mac802154Pkt extends MacPkt {
 * 	int pktType = MAC802154_DATA; 
 *     pktSize = 21; 
 * }
 * </pre>
 */
class Mac802154Pkt : public ::twsn::MacPkt
{
  protected:
    int pktType_var;

  private:
    void copy(const Mac802154Pkt& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Mac802154Pkt&);

  public:
    Mac802154Pkt(const char *name=NULL, int kind=0);
    Mac802154Pkt(const Mac802154Pkt& other);
    virtual ~Mac802154Pkt();
    Mac802154Pkt& operator=(const Mac802154Pkt& other);
    virtual Mac802154Pkt *dup() const {return new Mac802154Pkt(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getPktType() const;
    virtual void setPktType(int pktType);
};

inline void doPacking(cCommBuffer *b, Mac802154Pkt& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Mac802154Pkt& obj) {obj.parsimUnpack(b);}

}; // end namespace twsn

#endif // _TWSN_MAC802154PKT_M_H_
