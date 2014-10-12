#ifndef DEVICEMAPPER_H
#define DEVICEMAPPER_H

#include <memory>
#include <string>
#include <map>
#include "tcpdevice.h"
#include "messaging.hpp"
#include "messagtypes.h"
#include "oscpkt.hh"

class DeviceMapper : public messaging::IMessageListener<OscDeviceMessage>,
        public messaging::IMessageContext<DeviceAddedMessage>,
        public messaging::IMessageListener<DeviceStateMessage>,
        public messaging::IMessageContext<DeviceStateMessage>,
        public messaging::IMessageContext<DeviceRemovedMessage>
{
    std::map<std::string, std::shared_ptr<TcpDevice> > devices;
    virtual void handleMessage(const OscDeviceMessage &);
    virtual void handleMessage(const DeviceStateMessage &);
    std::string& addNewLines(std::string &);
public:
    DeviceMapper();
    ~DeviceMapper();
    void addDevice(const std::string&, std::shared_ptr<TcpDevice>);
    void removeDevice(const std::string&);
    bool nameValid(const std::string &);
    std::shared_ptr<TcpDevice> getDevice(const std::string &);
};

#endif // DEVICEMAPPER_H
