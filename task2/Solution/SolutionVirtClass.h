#pragma once

# define ll long long

class SolutionVirtClass {
    double energyValue;
public:
    virtual void updateSolution(SolutionVirtClass*) = 0;
    virtual void computeStateEnergy() = 0;
    virtual void init() = 0;

    ll getEnergy() const {
        return energyValue;
    }

    void setEnergy(const ll& newEnergy) {
        energyValue = newEnergy;
    }

    virtual ~SolutionVirtClass() = default;
};
