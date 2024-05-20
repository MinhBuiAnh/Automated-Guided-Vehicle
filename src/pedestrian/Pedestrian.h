#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "src/ward/Ward.h"
#include "src/event/Event.h"
#include "vector"

enum Walkability{noDisability, crutches, sticks, wheelchairs, blind};
struct Personality
{
    int lambda;
    double postitiveEmotionThreshold;
    double negativeEmotionThreshold;
};

struct Emotion
{
    double pleasure = 0.75;
    double surprise = 0.5;
    double anger = -0.2;
    double fear = -0.2;
    double hate = -0.4;
    double sad = -0.4;
};

class Pedestrian
{
protected:
    int ID;
    Ward start;
    Ward end;
    std::vector<Ward> journey;
    double velocity;
    Personality personality;
    Emotion emotion;
    std::vector< std::vector<Event> > events;
    double walkingTime;
    double distance;
    double age;
    Event impactOfAGV;
    Point tempPoints;
public:
    static int curr_id;
    
    Pedestrian();
    // ~Pedestrian();

    int getID();

    Ward getStart();

    Ward getEnd();

    std::vector<Ward> getJourney();

    double getVelocity();

    Personality getPersonality();

    Emotion getEmotion();

    std::vector< std::vector<Event> > getEvents();

    double getWalkingTime();

    double getDistance();

    double getAge();

    Event getImapactOfAGV();

    Point getTempPoints();

    void setStart(Ward start);

    void setEnd(Ward end);

    void setJourney(std::vector<Ward> journey);

    void setVelocity(double velocity);

    void setPersonality(Personality personality);

    void setEmotion(Emotion emotion);

    void setEvents(std::vector< std::vector<Event> > events);

    void setWalkingTime(double walkingTime);

    void setDistance(double distance);

    void setAge(double age);

    void setImpactOfAGV(Event impactOfAGV);

    void setTempPoints(Point tempPoints);
};

class Patient:Pedestrian
{
private:
    Walkability walkability;
public:
    Patient();
    Patient(Walkability walkability);

    Walkability getWalkability();

    void setWalkability(Walkability walkability);
};

class Visitor:Pedestrian
{
private:
    Walkability walkability;
public:
    Visitor();

    Walkability getWalkability();

    void setWalkability(Walkability walkability);
};

class Personel:Pedestrian
{
private:
public:
    Personel();
};

#endif