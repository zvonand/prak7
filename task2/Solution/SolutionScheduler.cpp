#include "SolutionScheduler.h"

#include "tinyxml2.h"

#include <sstream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <algorithm>

#define ll long long


Runner* Runner::runnerInstance = 0;

//TODO: change .csv to .xml
Runner::Runner(const std::string& path) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());
    size_t numTask = std::atoi(doc.FirstChildElement("Task")->FirstChildElement("Num")->GetText());
    std::string workTime(doc.FirstChildElement("Task")->FirstChildElement("Time")->GetText());
    value.resize(numTask);
    std::stringstream ss(workTime);
    for (auto& i : value) {
         ss >> i;
    }
}

void SolutionScheduler::updateSolution(SolutionVirtClass* s) {
    SolutionScheduler* sol = dynamic_cast<SolutionScheduler*>(s);
    if (sol == this) {
        return;
    }
    for (size_t i = 0; i < scheduling.size(); i++) {
        scheduling[i].clear();
        for (auto& j : sol->scheduling[i]) {
            scheduling[i].push_back(j);
        }
    }
    setEnergy(sol->getEnergy());
}

void SolutionScheduler::init() {
    std::mt19937 engine;
    engine.seed(time(NULL));
    std::uniform_int_distribution<size_t> intDistribution(0, scheduling.size() - 1);

    for (size_t i = 0; i < tasksTime->size(); i++) {
        scheduling[intDistribution(engine)].push_back(i);
    }
    computeStateEnergy();
}

void SolutionScheduler::computeStateEnergy() {
    ll e = 0;
    for (size_t i = 0; i < scheduling.size(); i++) {
        ll start = 0;
        for (auto& j : scheduling[i]) {
            start += (*tasksTime)[j];
            e += start;
        }
    }
    setEnergy(e);
}

SolutionScheduler::SolutionScheduler(const std::string& path, bool initFlag) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());
    size_t numProc = std::atoi(doc.FirstChildElement("Proc")->FirstChildElement("Num")->GetText());
    scheduling.resize(numProc);
    tasksTime = Runner::getInstance(path);

    if (initFlag) {
        init();
    }
}
