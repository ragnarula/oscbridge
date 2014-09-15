#ifndef DEVICE_H
#define DEVICE_H

#include "messaging.hpp"
#include "messagtypes.h"

class Device :
        public messaging::IMessageContext<DeviceStateMessage>
{
    DEVICE_STATE currentState;
    std::string status;
    std::string name;
protected:
    void setState(const DEVICE_STATE &, const std::string &);
public:
    Device();
    DEVICE_STATE getState();
    std::string &getName();
    void setName(const std::string&);
};

#endif // DEVICE_H
