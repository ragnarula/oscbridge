#include "devicemapper.h"

void DeviceMapper::handleMessage(const OscDeviceMessage &_msg)
{
    LOG(__PRETTY_FUNCTION__);
    TcpDevice *device;

    try {
         device = devices.at(_msg.addReader.head()).get();
    } catch (const std::out_of_range &e){
        LOG_ERR(__PRETTY_FUNCTION__, "Device \"", _msg.addReader.head(),"\" not found");
        return;
    }

    _msg.addReader.pop();
    if(_msg.addReader.head()=="message"){
        std::string s;
        if(_msg.msg.arg().popStr(s).isOkNoMoreArgs()){
            device->send(addNewLines(s));
        }
    } else {
        LOG_ERR(__PRETTY_FUNCTION__, " Method \"", _msg.addReader.head(), "\" not found");
    }
}

void DeviceMapper::handleMessage(const DeviceStateMessage &_msg)
{
    LOG(__PRETTY_FUNCTION__);
    messaging::send<DeviceStateMessage>(this,_msg);
}

std::string& DeviceMapper::addNewLines(std::string &s)
{
    LOG(__PRETTY_FUNCTION__);
    std::string::size_type pos = 0;
    while ((pos = s.find("\\n", pos)) != std::string::npos)
    {
        s.replace(pos, 2, "\n");
    }
    return s;
}

DeviceMapper::DeviceMapper()
{
    LOG(__PRETTY_FUNCTION__);
}

void DeviceMapper::addDevice(const std::string &_name, std::shared_ptr<TcpDevice> _ptrDevice)
{
    LOG(__PRETTY_FUNCTION__);
    std::string nameTrimmed = _name;
    nameTrimmed.erase(std::remove(nameTrimmed.begin(), nameTrimmed.end(), ' '), nameTrimmed.end());

    if(devices.count(nameTrimmed) != 0){
        return;
    }
    _ptrDevice->setName(nameTrimmed);
    devices[nameTrimmed] = _ptrDevice;

    DeviceAddedMessage msg(_ptrDevice->getName(), _ptrDevice->getState());
    messaging::send<DeviceAddedMessage>(this, msg);
    messaging::attach<DeviceStateMessage>(_ptrDevice.get(), this);
}

void DeviceMapper::removeDevice(const std::string &_name)
{
    LOG(__PRETTY_FUNCTION__);
    if(devices.count(_name) != 1){
        return;
    }
    devices.at(_name)->stop();
    devices.erase(_name);
    DeviceRemovedMessage msg(_name);
    messaging::send<DeviceRemovedMessage>(this,msg);
}

bool DeviceMapper::nameValid(const std::string &_name)
{
    LOG(__PRETTY_FUNCTION__);

    std::string nameTrimmed = _name;
    nameTrimmed.erase(std::remove(nameTrimmed.begin(), nameTrimmed.end(), ' '), nameTrimmed.end());

    if(nameTrimmed.empty() || devices.count(nameTrimmed) != 0)
        return false;
    return true;
}

std::shared_ptr<TcpDevice> DeviceMapper::getDevice(const std::string &_name)
{
    LOG(__PRETTY_FUNCTION__);
    return devices.at(_name);
}

DeviceMapper::~DeviceMapper()
{
    LOG(__PRETTY_FUNCTION__);
    std::map<std::string,std::shared_ptr<TcpDevice> >::iterator i;
    for(i = devices.begin(); i != devices.end(); ++i){
        i->second->stop();
    }
}
