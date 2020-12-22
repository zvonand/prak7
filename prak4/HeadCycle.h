#ifndef PRAK4_HEADCYCLE_H
#define PRAK4_HEADCYCLE_H

#include "Genetic.h"

class HeadCycle {
private:
    std::vector<space> populationObj;
    std::unique_ptr<FitnessBase> fitness;
    std::unique_ptr<SelectionBase> selection;
    std::unique_ptr<CrossoverBase> crossover;
    std::unique_ptr<MutationBase> mutation;
    float Mut_p;
    int experiment_num;
    int run_num;

public:
    HeadCycle();
    int Start(float mut, int param, int launch_num);
    void fileOutput(space& bestResult, bool afterLife) const;
    void print(space& bestResult, bool detail = false) const;
};


#endif
