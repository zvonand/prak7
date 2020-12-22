#ifndef PRAK4_GENETIC_H
#define PRAK4_GENETIC_H

#include "iostream"
#include "vector"
#include "memory"
#include "GoL.h"


using space = std::vector<std::vector<int>>;

using population = std::vector<std::pair<space, int>>;

class FitnessBase {
public:
    FitnessBase() = default;
    virtual ~FitnessBase() = default;

    virtual population getFitness(std::vector<space>& gen)=0;
};

class SelectionBase {
public:
    SelectionBase() = default;
    virtual ~SelectionBase() = default;

    virtual std::vector<space> getSelection(population& solution) = 0;
};

class CrossoverBase {
public:
    CrossoverBase() = default;
    virtual ~CrossoverBase() = default;

    virtual void doCrossover(std::vector <space> &solution) = 0;
};

class MutationBase {
public:
    MutationBase() = default;
    virtual ~MutationBase() = default;

    virtual void getMutation(std::vector <space> &solution, double mut_probability) = 0;
};





class Fitness: public FitnessBase
{
public:
    Fitness() = default;
    ~Fitness() = default;

    std::vector <std::pair<space,int>> getFitness(std::vector<space>& gen) override;
};

class Selection: public SelectionBase {
public:
    Selection() = default;
    ~Selection() = default;

    std::vector <space> getSelection(population& solution) override;
};

class Crossing: public CrossoverBase {
public:
    Crossing() = default;
    ~Crossing() = default;

    void doCrossover(std::vector <space> &solution) override;
};

class Mutation: public MutationBase {
public:
    Mutation() = default;
    ~Mutation() = default;

    void getMutation(std::vector<space>& solution, double P_mut) override;
};


#endif