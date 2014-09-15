#ifndef TCP_DEVICE_H
#define TCP_DEVICE_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include "device.h"
#include "globals.h"
#include "messaging.hpp"


class TcpDevice : public Device,
        public std::enable_shared_from_this<TcpDevice>
{
    std::array<char, MAX_RECEIVE_BUFFER> recieveBuffer;
    std::shared_ptr<boost::asio::io_service> ptrIo;
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::socket socket;
    std::string address;
    uint16_t port;

    void handleResolve(const boost::system::error_code&,
                       boost::asio::ip::tcp::resolver::iterator);
    void handleReceive(const boost::system::error_code &,
                       std::size_t);
    void startReceive();

public:
    TcpDevice(std::shared_ptr<boost::asio::io_service>,const std::string &, uint16_t);
    void start();
    void stop();
    bool isStopped();
    void send(const std::string &);
    ~TcpDevice();
};

#endif // TCP_DEVICE_H
