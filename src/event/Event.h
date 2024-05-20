#ifndef EVENT_H
#define EVENT_H

class Event
{
protected:
    double intensity;
    double time;
public:
    Event();
    Event(float intensity, float time);
    // ~Event();
    double getIntensity();
    double getTime();
    void setIntensity(float intensity);
    void setTime(float time);
};




#endif
