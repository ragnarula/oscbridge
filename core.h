#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QByteArray>
#include <boost/system/system_error.hpp>
#include <memory>
#include <string>
#include "bufferreader.h"
#include "devicemapper.h"
#include "tcpdevice.h"
#include "globals.h"
#include "ioservicehandler.h"
#include "udposcendpoint.h"
#include "messaging.hpp"

class Core : public QObject, 
        public messaging::IMessageListener<Server::STATE>,
        public messaging::IMessageListener<DeviceStateMessage>,
        public messaging::IMessageListener<DeviceAddedMessage>,
        public messaging::IMessageListener<DeviceRemovedMessage>
{
    Q_OBJECT
    //main io service handler and thread pool
    std::unique_ptr<IOServiceHandler> ptrIoServiceHandler;
    //OSC Endpoint for receiving instructions
    std::shared_ptr<UdpOscEndpoint> ptrOscEndpoint;
    //Device manager, maps device id to device, contains devices
    BufferReader bufferReader;
    DeviceMapper mapper;

    virtual void handleMessage(const UdpOscEndpoint::STATE&);
    virtual void handleMessage(const DeviceStateMessage&);
    virtual void handleMessage(const DeviceAddedMessage&);
    virtual void handleMessage(const DeviceRemovedMessage&);
public:
    Core();
    ~Core();

public slots:
    void startServer(const uint16_t&);
    void stopServer();
    void addDevice(const std::string&, const std::string&, const int);
    void removeDevice(const char*);

    void checkName(const char*);

    void connect(const char*);
    void disconnect(const char*);
signals:
    void serverStatusChanged(const char*);
    void deviceAdded(const char*, const char*);
    void deviceRemoved(const char*);
    void deviceStateChanged(const char*, const char*);

    void isNameAvailable(bool);
};

#endif // CORE_H
