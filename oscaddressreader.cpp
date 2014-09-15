#include "oscaddressreader.h"

OscAddressReader::OscAddressReader(oscpkt::Message &_msg) :
    msg(_msg),
    blank("")
{
    LOG(__PRETTY_FUNCTION__);
    splitAddress(msg.addressPattern());
}


void OscAddressReader::splitAddress(const std::string &_addressPattern)
{
    LOG(__PRETTY_FUNCTION__, _addressPattern);
    std::string::const_iterator begin = _addressPattern.begin();
    std::string::const_iterator partBegin = _addressPattern.begin();
    std::string::const_iterator partEnd = _addressPattern.end();

    for(std::string::const_iterator i = begin; i < _addressPattern.end(); ++i){
        if(*i == '/'){
            partBegin = ++i;
            partEnd = _addressPattern.end();
            while(i != _addressPattern.end()){
                if(*i == '/'){
                    partEnd = i--;
                    break;
                }
                i++;
            }

            addressParts.push_back(std::string (partBegin, partEnd));
        }
    }

    popIter = addressParts.begin();

}


std::string& OscAddressReader::get(uint32_t x)
{
    LOG(__PRETTY_FUNCTION__);
    std::string &part = blank;
    try{
        part = addressParts.at(x);
    } catch (std::out_of_range e) {
        return part;
    }
    return part;
}

std::string& OscAddressReader::pop()
{
    LOG(__PRETTY_FUNCTION__);
    if(popIter == addressParts.end())
        return blank;

    return *(popIter++);
}

std::string& OscAddressReader::head(){
    if(popIter == addressParts.end())
        return blank;
    return *(popIter);
}
