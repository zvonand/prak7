#include "SolutionVirtClass.h"
#include "MutationVirtClass.h"
#include "TempVirtClass.h"

#include <memory>
#include <random>
#include <chrono>
#include <cmath>
#include <iostream>
#include <SolutionScheduler.h>

template<class Sol, class Mut, class TempFlowModel>
class AnnealingSim {
    std::unique_ptr<SolutionVirtClass> tmp;
    std::unique_ptr<SolutionVirtClass> currSolution;
    std::unique_ptr<SolutionVirtClass> bestSolution;

    std::unique_ptr<MutationVirtClass> mutation;
    std::unique_ptr<TempVirtClass> temp;
public:
    AnnealingSim() = default;
    AnnealingSim(AnnealingSim&&) = default;

    AnnealingSim(const std::string& path, const double& maxTemp) {
        currSolution = std::make_unique<Sol>(path, true);

        bestSolution = std::make_unique<Sol>(path, false);
        bestSolution->updateSolution(currSolution.get());

        tmp = std::make_unique<Sol>(path, false);

        mutation = std::make_unique<Mut>();

        temp = std::make_unique<TempFlowModel>();
        temp->set_temp(maxTemp);
    }

    void updateSolution(SolutionVirtClass* sol) {
        currSolution->updateSolution(sol);
        bestSolution->updateSolution(sol);
    }

    SolutionVirtClass* getSolution() const {
        return bestSolution.get();
    }

    double calcProbability(const double& dE, const double& t) const {
        return std::exp(-dE / t);
    }

    void start() {
        std::mt19937 twisterEngine;
        twisterEngine.seed(time(NULL));
        std::uniform_real_distribution<double> realDistribution(0, 1);

        const size_t MAX_ITER_OUT = 10E9;
        const size_t MAX_TIME_UPDATE_SOLUTION = 100;
        const size_t MAX_ITERATION_IN = 100;

        size_t sinceLastUpdate = 0;
        size_t iter = 0;
        while (sinceLastUpdate < MAX_TIME_UPDATE_SOLUTION && iter < MAX_ITER_OUT) {
            for (size_t j = 0; j < MAX_ITERATION_IN; j++) {
                tmp->updateSolution(currSolution.get());
                mutation->mutate(*(tmp.get()));

                double dE = tmp->getEnergy() - currSolution->getEnergy();

                if (dE < 0 || realDistribution(twisterEngine) < calcProbability(dE, temp->getTemperature(iter))) {
                    currSolution->updateSolution(tmp.get());
                }
                if (currSolution->getEnergy() < bestSolution->getEnergy()) {
                    bestSolution->updateSolution(currSolution.get());
                    sinceLastUpdate = 0;
                }
            }
            sinceLastUpdate++;
            iter++;
        }
    }

    virtual ~AnnealingSim() = default;
};
