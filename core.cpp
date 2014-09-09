#include "core.h"

Core::Core() : ptrIoServiceHandler(new IOServiceHandler(NUM_THREADS)),
    ptrOscEndpoint(new UdpOscEndpoint(ptrIoServiceHandler->getIoService()))
{
    LOG(__PRETTY_FUNCTION__);
    messaging::attach<Server::STATE>(ptrOscEndpoint.get(), this);
    messaging::attach<BufferMessage>(ptrOscEndpoint.get(),&bufferReader);
}


Core::~Core()
{
    LOG(__PRETTY_FUNCTION__);
    ptrOscEndpoint->stop();
}


//slots
void Core::startServer(const uint16_t &_port)
{
    LOG(__PRETTY_FUNCTION__);
    ptrOscEndpoint->start(_port);
}

void Core::stopServer()
{
    LOG(__PRETTY_FUNCTION__);
    ptrOscEndpoint->stop();
}

//Listener Methods
void Core::handleMessage(const UdpOscEndpoint::STATE& _state)
{
    LOG(__PRETTY_FUNCTION__);

    switch(_state){
    case UdpOscEndpoint::STATE::RUNNING:
        LOG(__PRETTY_FUNCTION__, " running");
        emit serverStatusChanged("Running");
        break;
    case UdpOscEndpoint::STATE::STOPPED:
        LOG(__PRETTY_FUNCTION__, " stopped");
        emit serverStatusChanged("Stopped");
        break;
    case UdpOscEndpoint::STATE::ERROR:
        LOG(__PRETTY_FUNCTION__, " error");
        emit serverStatusChanged("Error");
        break;
    }
}
