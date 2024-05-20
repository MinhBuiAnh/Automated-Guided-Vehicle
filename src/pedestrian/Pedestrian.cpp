#include "src/pedestrian/Pedestrian.h"
#include "src/ward/Ward.h"


Pedestrian::Pedestrian()
{
    this->ID = ++curr_id;
    this->start = Ward();
    this->end = Ward();
    this->journey = std::vector<Ward>();
    this->velocity = 0;
    this->personality = Personality();
    this->emotion = Emotion();
    this->events = std::vector< std::vector<Event> >();
    this->walkingTime = 0;
    this->distance = 0;
    this->age = 20;
    this->impactOfAGV = Event();
    this->tempPoints = Point();
}

int Pedestrian::curr_id = -1;

int Pedestrian::getID(){
    return this->ID;
}

Ward Pedestrian::getStart(){
    return this->start;
}

Ward Pedestrian::getEnd(){
    return this->end;
}

std::vector<Ward> Pedestrian::getJourney(){
    return this->journey;
}

double Pedestrian::getVelocity(){
    return this->velocity;
}

Personality Pedestrian::getPersonality(){
    return this->personality;
}

Emotion Pedestrian::getEmotion(){
    return this->emotion;
}

std::vector<Event> Pedestrian::getEvents(){
    return this->events;
}

double Pedestrian::getWalkingTime(){
    return this->walkingTime;
}

double Pedestrian::getDistance(){
    return this->distance;
}

double Pedestrian::getAge(){
    return this->age;
}

Event Pedestrian::getImapactOfAGV(){
    return this->impactOfAGV;
}

Point Pedestrian::getTempPoints(){
    return this->tempPoints;
}


void Pedestrian::setStart(Ward start){
    this->start = start;
}

void Pedestrian::setEnd(Ward end){
    this->end = end;
}

void Pedestrian::setJourney(std::vector<Ward> journey){
    this->journey = journey;
}

void Pedestrian::setVelocity(double velocity){
    this->velocity = velocity;
}

void Pedestrian::setPersonality(Personality personality){
    this->personality = personality;
}

void Pedestrian::setEmotion(Emotion emotion){
    this->emotion = emotion;
}

void Pedestrian::setEvents(std::vector< std::vector<Event> > events){
    this->events = events;
}

void Pedestrian::setWalkingTime(double walkingTime){
    this->walkingTime = walkingTime;
}

void Pedestrian::setDistance(double distance){
    this->distance = distance;
}

void Pedestrian::setAge(double age){
    this->age = age;
}

void Pedestrian::setImpactOfAGV(Event impactOfAGV){
    this->impactOfAGV = impactOfAGV;
}

void Pedestrian::setTempPoints(Point tempPoints){
    this->tempPoints = tempPoints;
}

Patient::Patient() : Pedestrian(){
    this->walkability = noDisability;
};

Patient::Patient(Walkability walkability) : Pedestrian(){
    this->walkability = walkability;
}

Visitor::Visitor() : Pedestrian(){
    this->walkability = noDisability;
}

Personel::Personel() : Pedestrian(){

}







