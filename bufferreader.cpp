#include "bufferreader.h"

BufferReader::BufferReader()
{
    LOG(__PRETTY_FUNCTION__);
}

BufferReader::~BufferReader()
{
    LOG(__PRETTY_FUNCTION__);
}

void BufferReader::processBuffer(std::unique_ptr<oscpkt::PacketReader> _ptrPacketReader)
{
    LOG(__PRETTY_FUNCTION__, " ",std::this_thread::get_id());
    oscpkt::Message *msg;
    while (_ptrPacketReader->isOk() && (msg = _ptrPacketReader->popMessage()) != 0) {
        OscAddressReader addReader(*msg);
        if(addReader.head() == "device"){
            addReader.pop();
            messaging::send<OscDeviceMessage>(this,OscDeviceMessage(*msg, addReader));
        }
    }
}

void BufferReader::handleMessage(const BufferMessage& _msg)
{
    LOG(__PRETTY_FUNCTION__);
    std::unique_ptr<oscpkt::PacketReader> ptrPacketReader(new oscpkt::PacketReader);

    ptrPacketReader->init(_msg.buffer.data(),_msg.howMany);

    std::thread t(&BufferReader::processBuffer, this, std::move(ptrPacketReader));
    t.detach();
}
