#include "core.h"

Core::Core() : ptrIoServiceHandler(new IOServiceHandler(NUM_THREADS)),
    ptrOscEndpoint(new UdpOscEndpoint(ptrIoServiceHandler->getIoService()))
{
    LOG(__PRETTY_FUNCTION__);
    messaging::attach<Server::STATE>(ptrOscEndpoint.get(), this);
    messaging::attach<BufferMessage>(ptrOscEndpoint.get(),&bufferReader);
    messaging::attach<OscDeviceMessage>(&bufferReader, &mapper);
    messaging::attach<DeviceAddedMessage>(&mapper, this);
    messaging::attach<DeviceStateMessage>(&mapper, this);
    messaging::attach<DeviceRemovedMessage>(&mapper,this);

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

void Core::addDevice(const std::string& _name, const std::string& _host, const int _port)
{
    LOG(__PRETTY_FUNCTION__);
    std::shared_ptr<TcpDevice> dev(new TcpDevice(ptrIoServiceHandler->getIoService(), _host, _port));
    mapper.addDevice(_name,dev);
}

void Core::removeDevice(const char *_device)
{
    LOG(__PRETTY_FUNCTION__);
    mapper.removeDevice(std::string(_device));
}

void Core::checkName(const char *_name)
{
    LOG(__PRETTY_FUNCTION__);
    emit isNameAvailable(mapper.nameValid(std::string(_name)));
}

void Core::connect(const char *_name)
{
    LOG(__PRETTY_FUNCTION__);
    try{
    mapper.getDevice(_name)->start();
    } catch (const std::out_of_range &e) {
        LOG_ERR(__PRETTY_FUNCTION__, " Cant connect device with name \"", _name,"\"");
    }
}

void Core::disconnect(const char *_name)
{
    LOG(__PRETTY_FUNCTION__);
    try{
    mapper.getDevice(_name)->stop();
    } catch (const std::out_of_range &e) {
        LOG_ERR(__PRETTY_FUNCTION__, " Cant disconnect device with name \"", _name,"\"");
    }
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

void Core::handleMessage(const DeviceStateMessage &_msg)
{
    LOG(__PRETTY_FUNCTION__);
    switch(_msg.state){
    case DEVICE_STATE::CONNECTED:
        LOG(__PRETTY_FUNCTION__, "Connected");
        emit deviceStateChanged(_msg.name.c_str(), "Connected");
        break;
    case DEVICE_STATE::CONNECTING:
        LOG(__PRETTY_FUNCTION__, "Connecting");
        emit deviceStateChanged(_msg.name.c_str(), "Connecting");
        break;
    case DEVICE_STATE::DISCONNECTED:
        LOG(__PRETTY_FUNCTION__, "Disconnected");
        emit deviceStateChanged(_msg.name.c_str(), "Disconnected");
        break;
    case DEVICE_STATE::ERROR:
        LOG(__PRETTY_FUNCTION__, "Error");
        emit deviceStateChanged(_msg.name.c_str(), "Error");
        break;
    }
}

void Core::handleMessage(const DeviceAddedMessage &_msg)
{
    LOG(__PRETTY_FUNCTION__);

    switch(_msg.state){
    case DEVICE_STATE::CONNECTED:
        LOG(__PRETTY_FUNCTION__, "Connected");
        emit deviceAdded(_msg.name.c_str(), "Connected");
        break;
    case DEVICE_STATE::CONNECTING:
        LOG(__PRETTY_FUNCTION__, "Connecting");
        emit deviceAdded(_msg.name.c_str(), "Connecting");
        break;
    case DEVICE_STATE::DISCONNECTED:
        LOG(__PRETTY_FUNCTION__, "Disconnected");
        emit deviceAdded(_msg.name.c_str(), "Disonnected");
        break;
    case DEVICE_STATE::ERROR:
        LOG(__PRETTY_FUNCTION__, "Error");
        emit deviceAdded(_msg.name.c_str(), "Error");
        break;
    }
}

void Core::handleMessage(const DeviceRemovedMessage &_msg)
{
    LOG(__PRETTY_FUNCTION__);
    emit deviceRemoved(_msg.name.c_str());
}

