#include "tcpdevice.h"

TcpDevice::TcpDevice(std::shared_ptr<boost::asio::io_service> _ptrIo,const std::string &_address, uint16_t _port) :
    ptrIo(_ptrIo),
    resolver(*_ptrIo),
    socket(*_ptrIo),
    address(_address),
    port(_port)
{
    LOG(__PRETTY_FUNCTION__);
}

void TcpDevice::start()
{
    LOG(__PRETTY_FUNCTION__);

    if(getState() == DEVICE_STATE::CONNECTED ||
            getState() == DEVICE_STATE::CONNECTING)
        return;

    boost::asio::ip::tcp::resolver::query query(address, std::to_string(port));
    resolver.async_resolve(query,
                           boost::bind(&TcpDevice::handleResolve, this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::iterator));
}

void TcpDevice::handleResolve(const boost::system::error_code& _ec,
                              boost::asio::ip::tcp::resolver::iterator _endpointIterator)
{
    LOG(__PRETTY_FUNCTION__);

    if(_ec){
        LOG_ERR(__PRETTY_FUNCTION__, " error ", _ec.message());
        setState(DEVICE_STATE::ERROR, _ec.message());
        return;
    }

    boost::system::error_code hostError = boost::asio::error::host_not_found;
    boost::asio::ip::tcp::resolver::iterator end;
    setState(DEVICE_STATE::CONNECTING, "Resolving host");
    while(hostError && _endpointIterator != end){
        socket.close();
        socket.connect(*_endpointIterator++, hostError);
        if(hostError){
            socket.close();
        }
    }

    if(!socket.is_open()){
        LOG_ERR(__PRETTY_FUNCTION__, " error ", hostError.message());
        setState(DEVICE_STATE::ERROR, hostError.message());
        return;
    }
    setState(DEVICE_STATE::CONNECTED, "Ready");
    startReceive();
}

void TcpDevice::startReceive()
{
    LOG(__PRETTY_FUNCTION__);

    socket.async_receive(boost::asio::buffer(recieveBuffer),
                         boost::bind(&TcpDevice::handleReceive, shared_from_this(),
                                     boost::asio::placeholders::error(),
                                     boost::asio::placeholders::bytes_transferred()));
}


void TcpDevice::handleReceive(const boost::system::error_code &_ec, std::size_t _howMany)
{
    LOG(__PRETTY_FUNCTION__);

    if(isStopped())
        return;
    if (_ec && _ec != boost::asio::error::message_size){
        LOG_ERR(__PRETTY_FUNCTION__, " ",_ec.category().name(), " ", _ec.message().c_str());
        setState(DEVICE_STATE::ERROR, _ec.message());
        return;
    }

    std::string s(recieveBuffer.data(),_howMany);
    LOG(s);
    startReceive();
}


bool TcpDevice::isStopped()
{
    LOG(__PRETTY_FUNCTION__);

    return !socket.is_open();
}

void TcpDevice::stop()
{
    LOG(__PRETTY_FUNCTION__);
    if(isStopped() )
        return;

    socket.close();
    setState(DEVICE_STATE::DISCONNECTED, "Halted");
}

void TcpDevice::send(const std::string &_deviceMessage)
{
    LOG(__PRETTY_FUNCTION__);

    if(isStopped() || getState() != DEVICE_STATE::CONNECTED)
        return;
    socket.send(boost::asio::buffer(_deviceMessage.data(),_deviceMessage.size()));
}

TcpDevice::~TcpDevice()
{
    LOG(__PRETTY_FUNCTION__);
    stop();
}
