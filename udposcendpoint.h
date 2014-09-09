#ifndef UDPOSCSERVERSERVICE_H
#define UDPOSCSERVERSERVICE_H

#include <array>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <mutex>
#include <string>
#include <thread>
#include "messaging.hpp"
#include "messagtypes.h"
#include "globals.h"

class Server {
public:
    enum STATE {
        RUNNING = 0,
        STOPPED = 1,
        ERROR = -1
    };
};

class UdpOscEndpoint : public Server,
        public messaging::IMessageContext<Server::STATE>,
        public messaging::IMessageContext<BufferMessage>
{

private:
    //buffer to hold recieved data
    std::array<char, MAX_RECEIVE_BUFFER> recieveBuffer;
    //socket for recieving data
    std::unique_ptr<boost::asio::ip::udp::socket> socket;
    //remote endpoint
    boost::asio::ip::udp::endpoint remoteEndpoint;
    //pointer to io_Service
    std::shared_ptr<boost::asio::io_service> ptrIo;
    //write mutex
    std::mutex writeMutex;
    //marks current state of the instance
    STATE currentState;

    void setState(STATE);

public:
    void start(uint16_t);
    void run();
    void stop();
    void handleReceive(const boost::system::error_code&, std::size_t);
    STATE getState();
    UdpOscEndpoint(const std::shared_ptr<boost::asio::io_service>&);
    ~UdpOscEndpoint();
};

#endif // UDPOSCSERVERSERVICE_H
