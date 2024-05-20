#include "Quest3.h"

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

#include "src/ward/Ward.h"
#include "src/event/Event.h"
#include "src/pedestrian/Pedestrian.h"

Quest3::Quest3() {
    this->M = 0;
    this->listPersonels = std::vector<Personel>();
    this->listPatients = std::vector<Patient>();
    this->listVisitors = std::vector<Visitor>();
}

int Quest3::getM() {
    return this->M;
}

std::vector<Personel> Quest3::getlistPersonel() {
    return this->listPersonels;
}

std::vector<Patient> Quest3::getlistPatients() {
    return this->listPatients;
}

std::vector<Visitor> Quest3::getlistVisitors() {
    return this->listVisitors;
}

void Quest3::setM(int M) {
    this->M = M;
}

void Quest3::setlistPersonels(std::vector<Personel> &listPersonels) {
    this->listPersonels = listPersonels;
}

void Quest3::setlistPatients(std::vector<Patient> &listPatients) {
    this->listPatients = listPatients;
}

void Quest3::setlistVisitors(std::vector<Visitor> &listVisitors) {
    this->listVisitors = listVisitors;
}

// Hàm tính giá trị trung bình của vector
double Quest3::calculateMean(const std::vector<double>& sample) {
    double sum = 0.0;
    for (double value : sample) {
        sum += value;
    }
    return sum / vec.size();
}

// Hàm tính độ lệch chuẩn của vector
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
    std::uniform_int_distribution<int> dist1(0, M - 1);
    std::uniform_int_distribution<int> dist2(1, 2);

    bool selected[M];
    role.resize(M);
    while (numPersonel) {
        int u = dist1(gnr);
        if (listAge[u] >= 23 && listAge[u] <= 61) {
            if (selected[u] == false) {
                selected[u] = true;
                role[u] = "Personel"
                --numPersonel;
            }
        }
    }
    for (int v = 0; v < M; v++) {
        if (selected[v] == false) {
            selected[v] = true;

            int u = dist2(gnr);
            if (u == 1) role[u] = "Patient";
            else role[u] = "Visitor";
        }
    }
}

// Set walkability
void Quest3::setWalkability() {
    std::vector<int> walkabilityType(M);
    std::uniform_int_distribution<int> dist3(1, 5);
    for (int v = 0; v < M; v++) {
        int u = dist3(gnr);
        walkabilityType[v] = u;
    }
}

// Set personality
void Quest3::setPersonality() {
    int peopleUnder11 = 0;
    for (int v : listAge) {
        if (v < 11) ++peopleUnder11;
    }
    double under11Percentage = round(peopleUnder11 * 100 / n);

    personalityType.resize(M);
    if (under11Percentage > 55) {
        std::cout << "Error: Percentage of people under 11 years old exceeds 55%";
        return;
    }
    else if (under11Percentage >= 45) {
        for (int v = 0; v < M; v++) {
            if (listAge[v] < 11) personalityType[v] = "open";
            else personalityType[v] = "neurotic";
        }
    }
    else {
        std::default_random_engine gnr;
        std::uniform_int_distribution<int> dist4(45, 55);

        int u = dist4(gnr);
        int neuroticPeople = M * u / 100;
        if (u == 45) ++neuroticPeople;

        while (neuroticPeople) {
            int v = dist1(gnr);
            if (listAge[v] >= 11 && selected[v] == true) {
                selected[v] = false;
                personalities[v] = "neurotic";
                --neuroticPeople;
            }
        }

        for (int v = 0; v < M; v++)
            if (personalities[v] == "") personalities[v] = "open";
    }
}

// Set pedestrian's events
std::vector< std::vector<Event> > Quest3::setEvents(int n) {
    std::default_random_engine gnr;
    std::uniform_int_distribution<int> dist(0, n - 1);

    std::vector< std::vector<Event> > events(6);
    for (int u = 0; u < 20; u++) {
        int x = dist1(gnr);

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

// For age and all time distances distriburions
// type = 1: age distribution
// type = 2: all time distances distribution
void Quest3::setListAgeOrAllTimeDist(int N, int k, double min_value, double max_value, int type) {
    // Generate random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution((min_value + max_value) / 2,
        (max_value - min_value) / 6);
    
    std::vector<double> sample;
    // Generate data sample
    for (int i = 0; i < N; ++i) {
        sample.push_back(round(distribution(gen)));
    }

    // Calculate mean value and standard deviation
    double mean = calculateMean(sample);
    double stdDev = calculateStdDev(sample, mean);

    // Calculate p-value
    double z = (mean - ((min_value + max_value) / 2)) / (stdDev / sqrt(N));
    double p_value = 2 * (1 - 0.5 * (1 + erf(fabs(z) / sqrt(2))));

    // Print p-value
    std::cout << "p-value: " << p_value << std::endl;

    // Set significance level to 0.05
    /* If p-value is less than the significance level, reject the null hypothesis
    and conclude the sample data does not follow normal distribution */
    /* If p-value is greater than or equal to the significance level, do not reject
    the null hypothesis and conclude the sample data follows normal distribution */
    double alpha = 0.05;
    if (p_value < alpha) {
        std::cout << "Sample data does not follow normal distribution" << std::endl;
        return;
    }
    else {
        std::cout << "Sample data follows normal distribution" << std::endl;
    }

    if (type == 1) listAge = sample;
    else allTimeDistances = sample;
}

// For all events distribution
void Quest3::setListEvents(int N, int k, double min_value,
    double max_value, int num_of_fields) {
    // Import necessary libraries
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution((min_value + max_value) / 2,
        (max_value - min_value) / 6);
    
    std::vector< std::vector<double> > listEvents;
    for (int i = 0; i < num_of_fields; i++) {
        // Generate random sample following normal distribution
        std::vector<double> sample(N);
        for (int j = 0; j < N; j++)
            sample[j] = std::round(distribution(gen) * 10) / 10;
        
        double mean = calculateMean(sample);
    	double stdDev = calculateStdDev(sample, mean);
    	
    	// Calculate p-value
		double z = (mean - ((min_value + max_value) / 2)) / (stdDev / sqrt(N));
		double p_value = 2 * (1 - 0.5 * (1 + erf(fabs(z) / sqrt(2))));
        
        // Print the p-value
        std::cout << "p-value: " << p_value << std::endl;

        // Set the significance level to 0.05
        double alpha = 0.05;
        if (p_value < alpha) {
            std::cout << "Sample data does not follow normal distribution" << std::endl;
            return;
        }
		else {
            std::cout << "Sample data follows normal distribution" << std::endl;
            listEvents.push_back(sample);
        }
    }

    // Adjust the values so that a negative impact on one emotion also has a negative impact on the other emotions
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

void Quest3::setListPedestrians(json inputData) {
    M = inputData["numOfAgents"]["value"];
    int k = 100;
    double min_value = 5.0;
    double max_value = 104.0;

    // Generate age
    setListAgeOrAllTimeDist(M, k, min_value, max_value, 1);

    // Set role, walkability and personality
    // TODO: set start ward and end ward
    setRole();
    setWalkability();
    setPersonality();

    int n = 43;
    k = 200;
    min_value = -1.0;
    max_value = 1.0;
    int num_of_fields = 6;

    // Generate events list
    setListEvents(n, k, min_value, max_value, num_of_fields);

    min_value = 100;
    max_value = 3600;

    // Generate 
    setListAgeOrAllTimeDist(n, k, min_value, max_value, 2);

    Emotion e;
    Walkability w;

    // Open personality
    Personality po;
    po.lambda = 1;
    po.postitiveEmotionThreshold = 0.7;
    po.negativeEmotionThreshold = -0.3;
    
    // Neurrotic personality
    Personality pn;
    pn.lambda = 4;
    pn.postitiveEmotionThreshold = 0.6;
    pn.negativeEmotionThreshold = -0.4;
    
    for (int v = 0; v < M; v++) {
        std::vector< std::vector<Event> > events;

        if (role[v] == "Personel") {
            Personel *p = new Personel();
            p->setAge(listAge[v]);

            if (personalityType[v] == "open") p->setPersonality(po);
            else p->setPersonality(pn);

            p->setEmotion(e);
            events = setEvents(k1, k2);
            p->setEvents(events);

            listPersonels.push_back(*p);
        }
        else {
            if (role[v] == "Patient") Patient *p = new Patient();
            else Visitor *p = new Visitor();

            p->setAge(listAge[v]);

            if (personalityType[v] == "open") p->setPersonality(po);
            else p->setPersonality(pn);

            p->setEmotion(e);

            switch (walkabilityType[v]) {
                case 1: { w = noDisability; p->setWalkability(w); break; }
                case 2: { w = crutches; p->setWalkability(w); break; }
                case 3: { w = sticks; p->setWalkability(w); break; }
                case 4: { w = wheelchairs; p->setWalkability(w); break; }
                case 5: { w = blind; p->setWalkability(w); break; }
            }

            events = setEvents(n);
            p->setEvents(events);

            if (role[v] == "Patient") listPatients.push_back(*p);
            else listVisitors.push_back(*p);
        }
    }
}