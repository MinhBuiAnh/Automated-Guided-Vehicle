#ifndef QUEST3_H
#define QUEST3_H

#include <lib/nlohmann/json.hpp>

#include "src/ward/Ward.h"
#include "src/event/Event.h"
#include "src/pedestrian/Pedestrian.h"
#include "vector"

using json = nlohmann::json;

class Quest3{
    protected:
        int M;
        int single;
        int triple;
        std::vector<Personel> listPersonels;
        std::vector<Patient> listPatients;
        std::vector<Visitor> listVisitors;
    
    public:
        Quest3();

        std::vector<double> listAge;

        std::vector<std::string> role;

        std::vector<int> walkabilityType;

        std::vector<std::string> personalityType;

        std::vector< std::vector<double> > allEvents;

        std::vector<double> allTimeDistances;

        int getM();

        int getSingle();

        int getTriple();

        std::vector<Personel> getlistPersonel();

        std::vector<Patient> getlistPatients();

        std::vector<Visitor> getlistVisitors();

        void setM(int M);

        void setSingle(int single);

        void setTriple(int triple);

        void setlistPersonels(std::vector<Personel> &listPersonels);

        void setlistPatients(std::vector<Patient> &listPatients);

        void setlistVisitors(std::vector<Visitor> &listVisitors);

        double calculateMean(const std::vector<double> &sample);

        double calculateStdDev(const std::vector<double> &sample, double mean);

        void setRole();

        void setWalkability();

        void setPersonality();

        std::vector< std::vector<Event> > setEvents(int k1, int k2);

        void setListAgeOrAllTimeDist(int N, int k, double min_value, double max_value, int type);
        
        void setListEvents(int N, int k, double min_value, double max_value, int num_of_fields);
        
        void setListPedestrians(json inputData);
};

#endif