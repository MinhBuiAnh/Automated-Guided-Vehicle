#include "Quest3.h"

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

#include "src/ward/Ward.h"
#include "src/event/Event.h"
#include "src/pedestrian/Pedestrian.h"
#include "src/utility/Utility.h"

Quest3::Quest3() {
    this->M = 0;
    this->single = 0;
    this->triple = 0;
    this->listWards = std::vector<Ward>();
    this->listPersonels = std::vector<Personel>();
    this->listPatients = std::vector<Patient>();
    this->listVisitors = std::vector<Visitor>();
}

int Quest3::getM() {
    return this->M;
}

int Quest3::getSingle() {
    return this->single;
}

int Quest3::getTriple() {
    return this->triple;
}

std::vector<Ward> Quest3::getListWards() {
    return this->listWards;
}

std::vector<Personel> Quest3::getListPersonel() {
    return this->listPersonels;
}

std::vector<Patient> Quest3::getListPatients() {
    return this->listPatients;
}

std::vector<Visitor> Quest3::getListVisitors() {
    return this->listVisitors;
}

void Quest3::setM(int M) {
    this->M = M;
}

void Quest3::setListWards(std::vector<Ward> &listWards) {
    this->listWards = listWards;
}

void Quest3::setListPersonels(std::vector<Personel> &listPersonels) {
    this->listPersonels = listPersonels;
}

void Quest3::setListPatients(std::vector<Patient> &listPatients) {
    this->listPatients = listPatients;
}

void Quest3::setListVisitors(std::vector<Visitor> &listVisitors) {
    this->listVisitors = listVisitors;
}

// Vector's mean value
double Quest3::calculateMean(const std::vector<double>& sample) {
    double sum = 0.0;
    for (double value : sample) {
        sum += value;
    }
    return sum / sample.size();
}

// Vector's standard deviation
double Quest3::calculateStdDev(const std::vector<double>& sample, double mean) {
    double variance = 0.0;
    for (double value : sample) {
        variance += pow(value - mean, 2);
    }
    return sqrt(variance / sample.size());
}

// Set role
void Quest3::setRole() {
    int peopleUnder23 = 0;
    int peopleOver61 = 0;

    for (double v : listAge) {
        if (v < 23) ++peopleUnder23;
        if (v > 61) ++peopleOver61;
    }
    int numPersonel = (M - peopleUnder23 - peopleOver61) * 2 / 5;

    std::default_random_engine gnr;
    std::uniform_int_distribution<int> dist1(1, M);
    std::uniform_int_distribution<int> dist2(1, 2);

    int u;
    bool selected[M] = {};
    role.resize(M);
    while (numPersonel) {
        u = dist1(gnr); --u;
        if (listAge[u] >= 23 && listAge[u] <= 61) {
            if (selected[u] == false) {
                selected[u] = true;
                role[u] = "Personel";
                --numPersonel;
            }
        }
    }
    for (int v = 0; v < M; v++) {
        if (selected[v] == false) {
            u = dist2(gnr);
            if (u == 1) role[v] = "Patient";
            else role[v] = "Visitor";
        }
    }
}

// Set walkability
void Quest3::setWalkability() {
    walkabilityType.resize(M);
    int u;

    std::default_random_engine gnr;
    std::uniform_int_distribution<int> dist(1, 5);
    for (int v = 0; v < M; v++) {
        if (role[v] == "Personel") walkabilityType[v] = 0;
    	else {
    		u = dist(gnr);
        	walkabilityType[v] = u;
		}
    }
}

// Set personality
void Quest3::setPersonality() {
    std::default_random_engine gnr;
    std::uniform_int_distribution<int> dist1(1, M);

    personalityType.resize(M);
    
    if (under11Percentage >= 45) {
        for (int v = 0; v < M; v++) {
            if (listAge[v] < 11) personalityType[v] = "open";
            else personalityType[v] = "neurotic";
        }
    }
    else {
        std::uniform_int_distribution<int> dist2(45, 55);

        int u = dist2(gnr);
        int neuroticPeople = M * u / 100;
        if (u == 45) ++neuroticPeople;

        int v;
        bool selected[M] = {};
        while (neuroticPeople) {
            v = dist1(gnr); --v;
            if (listAge[v] >= 11 && selected[v] == false) {
                selected[v] = true;
                personalityType[v] = "neurotic";
                --neuroticPeople;
            }
        }

        for (int v = 0; v < M; v++)
            if (selected[v] == false) personalityType[v] = "open";
    }
}

// Set pedestrian's events
std::vector< std::vector<Event> > Quest3::setEvents(int n) {
    std::default_random_engine gnr;
    std::uniform_int_distribution<int> dist(1, n);

    int x;
    std::vector< std::vector<Event> > events(6);
    for (int u = 0; u < 20; u++) {
        x = dist(gnr); --x;

        Event e1, e2, e3, e4, e5, e6;
        e1.setIntensity(allEvents[0][x]); e2.setIntensity(allEvents[1][x]);
        e3.setIntensity(allEvents[2][x]); e4.setIntensity(allEvents[3][x]);
        e5.setIntensity(allEvents[4][x]); e6.setIntensity(allEvents[5][x]);

        e1.setTime(allTimeDistances[x]); e2.setTime(allTimeDistances[x]);
        e3.setTime(allTimeDistances[x]); e4.setTime(allTimeDistances[x]);
        e5.setTime(allTimeDistances[x]); e6.setTime(allTimeDistances[x]);

        events[0].push_back(e1); events[1].push_back(e2);
        events[2].push_back(e3); events[3].push_back(e4);
        events[4].push_back(e5); events[5].push_back(e6);
    }

    return events;
}

// For age and all events' time distances distriburions
// type = 1: age distribution
// type = 2: all events' time distances distribution
void Quest3::setListAgeOrAllTimeDist(int N, int k, double min_value, double max_value, int type) {
    // Generate random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution((min_value + max_value) / 2,
        (max_value - min_value) / 6);
    
    bool followDist = false;
    while (followDist == false) { // Generate samples until it follows normal distribution
        std::vector<double> sample(N);
        // Generate data sample
        for (int i = 0; i < N; ++i) {
            sample[i] = std::round(distribution(gen));
        }

        // Calculate mean value and standard deviation
        double mean = calculateMean(sample);
        double stdDev = calculateStdDev(sample, mean);

        // Calculate p-value
        double z = (mean - ((min_value + max_value) / 2)) / (stdDev / sqrt(N));
        double p_value = 2 * (1 - 0.5 * (1 + erf(fabs(z) / sqrt(2))));

        // Set significance level to 0.05
        /* If p-value is less than the significance level, reject the null hypothesis
        and conclude the sample data does not follow normal distribution */
        /* If p-value is greater than or equal to the significance level, do not reject
        the null hypothesis and conclude the sample data follows normal distribution */
        double alpha = 0.05;
        if (p_value >= alpha) {
            if (type == 1) {
            	int peopleUnder11 = 0;
			    for (int v : listAge) {
			        if (v < 11) ++peopleUnder11;
			    }
			    under11Percentage = round(peopleUnder11 * 100 / M);
			    
			    if (under11Percentage <= 55) {
			    	followDist = true;
			    	listAge = sample;
				}
			}
            else {
            	followDist = true;
            	allTimeDistances = sample;
			}
        }
    }
}

// For all events distribution
void Quest3::setListEvents(int N, int k, double min_value,
    double max_value, int num_of_fields) {
    // Import necessary libraries
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution((min_value + max_value) / 2,
        (max_value - min_value) / 6);
    
    bool followDist;
    std::vector< std::vector<double> > listEvents;
    for (int i = 0; i < num_of_fields; i++) { // Generate samples for 6 types of emotion
        followDist = false;

        while (followDist == false) { // Generate random sample until it follows normal distribution
            // Generate random sample following normal distribution
            std::vector<double> sample(N);
            for (int j = 0; j < N; j++)
                sample[j] = std::round(distribution(gen) * 10) / 10;
            
            //Calculate mean value and standard deviation
            double mean = calculateMean(sample);
            double stdDev = calculateStdDev(sample, mean);
            
            // Calculate p-value
            double z = (mean - ((min_value + max_value) / 2)) / (stdDev / sqrt(N));
            double p_value = 2 * (1 - 0.5 * (1 + erf(fabs(z) / sqrt(2))));
            
            // Set the significance level to 0.05
            double alpha = 0.05;
            if (p_value >= alpha) {
                followDist = true;
                listEvents.push_back(sample);
            }
        }
    }

    /* Adjust the values so that a negative impact on one emotion also has a negative impact
    on the other emotions */
    for (int i = 0; i < N; i++) {
        if (listEvents[0][i] < 0) {
            for (int j = 0; j < num_of_fields; j++) listEvents[j][i] = -std::abs(listEvents[j][i]);
        }
		else {
            for (int j = 0; j < num_of_fields; j++) listEvents[j][i] = std::abs(listEvents[j][i]);
        }
    }

    allEvents = listEvents;
}

// Generate a list of all pedestrians
void Quest3::setListPedestrians(int numOfAgents) {
    // Number of agents
    M = numOfAgents;
    listWards = Utility::readHospitalData("data/hospital.txt");

    // Generate age
    setListAgeOrAllTimeDist(M, 100, 5, 104, 1);

    // Set role, walkability and personality
    // TODO: set start ward and end ward for personels
    setRole();
    setWalkability();
    setPersonality();

    // Generate events list
    setListEvents(43, 200, -1.0, 1.0, 6);

    // Generate all events' time distances list
    setListAgeOrAllTimeDist(43, 200, 4, 10, 2);

    std::default_random_engine gnr;
    std::uniform_int_distribution<int> dist(1, 2);

    // One person's emotions and walkability
    Emotion e;
    Walkability w;

    // Pedestrian's velocities
    /* From left to right: noDisability (no overtaking), noDisability (overtaking), crutches,
    sticks, wheelchairs, blind */
    const double vel[] = { 1.24, 2.48, 0.94, 0.81, 0.69, 0.52 };

    // Open personality
    Personality po;
    po.lambda = 1;
    po.postitiveEmotionThreshold = 0.7;
    po.negativeEmotionThreshold = -0.3;
    
    // Neurotic personality
    Personality pn;
    pn.lambda = 4;
    pn.postitiveEmotionThreshold = 0.6;
    pn.negativeEmotionThreshold = -0.4;
    
    for (int v = 0; v < M; v++) {
        std::vector< std::vector<Event> > events;
        int x = dist(gnr);

        if (role[v] == "Personel") { // For personel
            Personel *p = new Personel();
            p->setAge(listAge[v]);

            if (personalityType[v] == "open") p->setPersonality(po);
            else p->setPersonality(pn);

            p->setEmotion(e);
            p->setVelocity(vel[x - 1]);
            events = setEvents(43);
            p->setEvents(events);

            listPersonels.push_back(*p);

            delete p;
        }
        else if (role[v] == "Patient") { // For patient
            Patient *p = new Patient();

            p->setAge(listAge[v]);

            if (personalityType[v] == "open") p->setPersonality(po);
            else p->setPersonality(pn);

            p->setEmotion(e);

            switch (walkabilityType[v]) {
                case 1: { w = noDisability; p->setWalkability(w); p->setVelocity(vel[x - 1]); break; }
                case 2: { w = crutches; p->setWalkability(w); p->setVelocity(vel[2]); break; }
                case 3: { w = sticks; p->setWalkability(w); p->setVelocity(vel[3]); break; }
                case 4: { w = wheelchairs; p->setWalkability(w); p->setVelocity(vel[4]); break; }
                case 5: { w = blind; p->setWalkability(w); p->setVelocity(vel[5]); break; }
            }

            Ward *wd = new Ward();
            p->setStart(*wd);
            p->setEnd(*wd);

            events = setEvents(43);
            p->setEvents(events);

            listPatients.push_back(*p);

            delete wd;
            delete p;
        }
        else { // For visitor
            Visitor *p = new Visitor();

            p->setAge(listAge[v]);

            if (personalityType[v] == "open") p->setPersonality(po);
            else p->setPersonality(pn);

            p->setEmotion(e);

            switch (walkabilityType[v]) {
                case 1: { w = noDisability; p->setWalkability(w); p->setVelocity(vel[x - 1]); break; }
                case 2: { w = crutches; p->setWalkability(w); p->setVelocity(vel[2]); break; }
                case 3: { w = sticks; p->setWalkability(w); p->setVelocity(vel[3]); break; }
                case 4: { w = wheelchairs; p->setWalkability(w); p->setVelocity(vel[4]); break; }
                case 5: { w = blind; p->setWalkability(w); p->setVelocity(vel[5]); break; }
            }

            Ward *wd = new Ward();
            p->setStart(*wd);
            p->setEnd(*wd);

            events = setEvents(43);
            p->setEvents(events);

            listVisitors.push_back(*p);

            delete wd;
            delete p;
        }
    }

    // single: number of visitors
    // triple: number of people who are not visitors
    single = listVisitors.size();
    triple = M - single;
}