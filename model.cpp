#include "model.h"
#include "globals.h"

void Model::addListener(ChangeListener *_listener)
{
    if(std::find(listeners.begin(), listeners.end(), _listener) == listeners.end()){
        listeners.push_back(_listener);
    }
}

void Model::removeListener(ChangeListener *_listener)
{
    listeners.erase(std::remove(listeners.begin(),listeners.end(),_listener), listeners.end());
}

void Model::changed()
{
    for(std::vector<ChangeListener*>::iterator i = listeners.begin(); i != listeners.end(); i++){
        (*i)->serverStateChanged();
    }
}
