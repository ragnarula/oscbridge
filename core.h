#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <boost/system/system_error.hpp>
#include <memory>
#include <string>
#include "bufferreader.h"
#include "globals.h"
#include "ioservicehandler.h"
#include "udposcendpoint.h"
#include "messaging.hpp"

class Core : public QObject, public messaging::IMessageListener<Server::STATE>
{
    Q_OBJECT
    //main io service handler and thread pool
    std::unique_ptr<IOServiceHandler> ptrIoServiceHandler;
    //OSC Endpoint for receiving instructions
    std::unique_ptr<UdpOscEndpoint> ptrOscEndpoint;
    //Device manager, maps device id to device, contains devices
    //(implements packetListener)
    BufferReader bufferReader;

public:
    virtual void handleMessage(const UdpOscEndpoint::STATE&);
    Core();
    ~Core();
public slots:
    void startServer(const uint16_t&);
    void stopServer();
signals:
    void serverStatusChanged(const char*);
};

#endif // CORE_H
