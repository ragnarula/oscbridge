#include "udposcendpoint.h"

// Constructor setup local ip and port, allow local ip
UdpOscEndpoint::UdpOscEndpoint(const std::shared_ptr<boost::asio::io_service>& _ptrIo)
    : ptrIo(_ptrIo), currentState(STATE::STOPPED)
{
    LOG(__PRETTY_FUNCTION__);
}

// Setup called when added to io service handler, assign ioservice, open socket
void UdpOscEndpoint::start(uint16_t _port)
{
    if(_port < 1024){
        LOG(__PRETTY_FUNCTION__, " invalid port");
        setState(STATE::ERROR);
        return;
    }

    if(getState() == STATE::RUNNING){
        LOG(__PRETTY_FUNCTION__, " already running");
        return;
    }

    try{
        socket.reset(new boost::asio::ip::udp::socket(
                         *ptrIo, boost::asio::ip::udp::endpoint(
                             boost::asio::ip::udp::v4(), _port )));
    } catch (boost::system::system_error err) {
        LOG_ERR(__PRETTY_FUNCTION__, " caught exception ", err.what());
        setState(STATE::ERROR);
        return;
    }

    LOG(__PRETTY_FUNCTION__, " port: ", _port);
    setState(STATE::RUNNING);
    run();
}

//run call recieve from to fill buffer
void UdpOscEndpoint::run()
{
    LOG(__PRETTY_FUNCTION__);

    if(getState() != STATE::RUNNING)
        return;

    socket->async_receive_from( boost::asio::buffer(recieveBuffer), remoteEndpoint,
                                boost::bind(&UdpOscEndpoint::handleReceive, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
}

//If socket is open, shutdown and close
void UdpOscEndpoint::stop()
{
    if(!socket){
        LOG(__PRETTY_FUNCTION__, " no socket");
        setState(STATE::STOPPED);
        return;
    }
    if(!socket->is_open()){
        LOG(__PRETTY_FUNCTION__," socket already closed");
        setState(STATE::STOPPED);
        return;
    }
    LOG(__PRETTY_FUNCTION__);
    socket->close();
    setState(STATE::STOPPED);
}

//recieve handler, calls run at end
void UdpOscEndpoint::handleReceive(const boost::system::error_code& error,
                                   std::size_t how_many)
{
    LOG(__PRETTY_FUNCTION__, " ", std::this_thread::get_id());

    if (error && error != boost::asio::error::message_size && error != boost::asio::error::operation_aborted){
        LOG_ERR(__PRETTY_FUNCTION__, " ",error.category().name(), " ", error.message().c_str());
        setState(STATE::ERROR);
        return;
    }

    BufferMessage msg(recieveBuffer,how_many);
    messaging::send<BufferMessage>(this,msg);
    run();
}

void UdpOscEndpoint::setState(const UdpOscEndpoint::STATE &_state)
{
    if(currentState == _state){
        LOG(__PRETTY_FUNCTION__, " no change ", _state);
        return;
    }
    LOG(__PRETTY_FUNCTION__, " ", _state);
    currentState = _state;
    messaging::send<Server::STATE>(this,currentState);
}

const UdpOscEndpoint::STATE& UdpOscEndpoint::getState()
{
    LOG(__PRETTY_FUNCTION__, " ", currentState);
    return currentState;
}

UdpOscEndpoint::~UdpOscEndpoint()
{
    LOG(__PRETTY_FUNCTION__);
    stop();
}

