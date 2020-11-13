#pragma once

#include "SolutionVirtClass.h"

#include <vector>
#include <string>

#define ll long long

class Runner {
    Runner(const std::string& path);
    static Runner* runnerInstance;
    std::vector<ll> value;
public:
    Runner() = delete;

    Runner(Runner& other) = delete;

    void operator=(const Runner&) = delete;

    static Runner* getInstance(const std::string& file) {
        if(runnerInstance == nullptr) {
            runnerInstance = new Runner(file);
        }
        return runnerInstance;
    }

    size_t size() const {
        return value.size();
    }

    const ll& operator[](const size_t& i) {
        return value[i];
    }
};

class SolutionScheduler : public SolutionVirtClass {
    Runner* tasksTime;
    std::vector<std::vector<size_t>> scheduling;
public:
    SolutionScheduler() = delete;
    SolutionScheduler(const std::string& path, bool initFlag = true);
    virtual void computeStateEnergy() override;
    virtual void init() override;
    virtual void updateSolution(SolutionVirtClass* s) override;
    virtual ~SolutionScheduler() = default;
    friend class MutationScheduler;

    auto& getAns() {
        return scheduling;
    }
};
