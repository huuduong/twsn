//
// Generated file, do not edit! Created by opp_msgc 4.4 from base/messages/airframe.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "airframe_m.h"

USING_NAMESPACE

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}



namespace twsn {

Register_Class(AirFrame);

AirFrame::AirFrame(const char *name, int kind) : ::cPacket(name,kind)
{
    this->frameSize_var = 6;
}

AirFrame::AirFrame(const AirFrame& other) : ::cPacket(other)
{
    copy(other);
}

AirFrame::~AirFrame()
{
}

AirFrame& AirFrame::operator=(const AirFrame& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AirFrame::copy(const AirFrame& other)
{
    this->sender_var = other.sender_var;
    this->receiver_var = other.receiver_var;
    this->frameSize_var = other.frameSize_var;
}

void AirFrame::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->sender_var);
    doPacking(b,this->receiver_var);
    doPacking(b,this->frameSize_var);
}

void AirFrame::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->sender_var);
    doUnpacking(b,this->receiver_var);
    doUnpacking(b,this->frameSize_var);
}

twsn::moduleid_t& AirFrame::getSender()
{
    return sender_var;
}

void AirFrame::setSender(const twsn::moduleid_t& sender)
{
    this->sender_var = sender;
}

twsn::moduleid_t& AirFrame::getReceiver()
{
    return receiver_var;
}

void AirFrame::setReceiver(const twsn::moduleid_t& receiver)
{
    this->receiver_var = receiver;
}

int AirFrame::getFrameSize() const
{
    return frameSize_var;
}

void AirFrame::setFrameSize(int frameSize)
{
    this->frameSize_var = frameSize;
}

class AirFrameDescriptor : public cClassDescriptor
{
  public:
    AirFrameDescriptor();
    virtual ~AirFrameDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(AirFrameDescriptor);

AirFrameDescriptor::AirFrameDescriptor() : cClassDescriptor("twsn::AirFrame", "cPacket")
{
}

AirFrameDescriptor::~AirFrameDescriptor()
{
}

bool AirFrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AirFrame *>(obj)!=NULL;
}

const char *AirFrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AirFrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int AirFrameDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *AirFrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "sender",
        "receiver",
        "frameSize",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int AirFrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sender")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "receiver")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameSize")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AirFrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "moduleid_t",
        "moduleid_t",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *AirFrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int AirFrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AirFrame *pp = (AirFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AirFrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AirFrame *pp = (AirFrame *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSender(); return out.str();}
        case 1: {std::stringstream out; out << pp->getReceiver(); return out.str();}
        case 2: return long2string(pp->getFrameSize());
        default: return "";
    }
}

bool AirFrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AirFrame *pp = (AirFrame *)object; (void)pp;
    switch (field) {
        case 2: pp->setFrameSize(string2long(value)); return true;
        default: return false;
    }
}

const char *AirFrameDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "twsn::moduleid_t",
        "twsn::moduleid_t",
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *AirFrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AirFrame *pp = (AirFrame *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSender()); break;
        case 1: return (void *)(&pp->getReceiver()); break;
        default: return NULL;
    }
}

}; // end namespace twsn

