#include "src/event/Event.h"

Event::Event(){
    this->time = 0;
    this->intensity = 0;
}

Event::Event(float intensity, float time){
    this->intensity = intensity;
    this->time = time;
}

double Event::getTime(){
    return this->time;
}

double Event::getIntensity(){
    return this->intensity;
}

void Event::setTime(float time){
    this->time = time;
}

void Event::setIntensity(float intensity){
    this->intensity = intensity;
}