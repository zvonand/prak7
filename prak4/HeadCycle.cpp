#include "HeadCycle.h"
#include "vector"
#include <unistd.h>
#include <fstream>
#include <string>
#include <memory>

void HeadCycle::fileOutput(space &bestResult, bool afterLife) const {
    //std::cout << experiment_num;
    //std::cout << run_num << std::endl;
    std::string fileName = "testlogs/series_" + std::to_string(experiment_num) + "_run_" + std::to_string(run_num) + (afterLife ? "_sol_after100.txt" : ".txt");
    std::ofstream file(fileName.c_str());

    for (int i = 0; i < bestResult.size(); i++) {
        for (int j = 0; j < bestResult[i].size(); j++) {
            auto symb = bestResult[i][j] == 1 ? "X" : "-";
            file << symb;
        }
        file << std::endl;
    }
    file.close();
}

void HeadCycle::print(space &bestResult, bool detail) const {
    // detail = true;
    fileOutput(bestResult, false);
    auto afterWork = advanceNSteps(bestResult, 100);
    fileOutput(afterWork, true);

    if (detail) {
        for (int i = 0; i < bestResult.size(); i++) {
            for (int j = 0; j < bestResult[i].size(); j++) {
                auto symb = bestResult[i][j] == 1 ? "X" : "-";
                std::cout << symb;
            }
            std::cout << std::endl;
        }
        std::cout << "\n | \n V " << std::endl;
        for (int i = 0; i < bestResult.size(); i++) {
            for (int j = 0; j < bestResult[i].size(); j++) {
                auto symb = bestResult[i][j] == 1 ? "X" : "-";
                std::cout << symb;
            }
            std::cout << std::endl;
        }
    }
}

HeadCycle::HeadCycle() {
    fitness = std::make_unique<Fitness> ();
    selection = std::make_unique<Selection>();
    crossover = std::make_unique<Crossing>();
    mutation = std::make_unique<Mutation>();

    for (int p = 0; p < 100; ++p){
        populationObj.push_back(generateState(50));
    }
}



int HeadCycle::Start(float mut, int param, int launch_num) {
    std::pair <space, int> recordedBest = {{}, 0};
    int iterations_unchanged = 0;

    Mut_p = mut;

    while (iterations_unchanged < 20) {
        int pos = -1;
        population populationFitness = fitness->getFitness(populationObj);

        for (int i = 0; i < populationFitness.size(); i++) {
            if (populationFitness[i].second > recordedBest.second) {
                recordedBest.second = populationFitness[i].second;
                pos = i;
            }
        }

        if (pos != -1) {
            recordedBest.first = populationFitness[pos].first;
            iterations_unchanged = 0;
        } else {
            iterations_unchanged++;
        }
        std::vector<space> new_gen = selection->getSelection(populationFitness);

        crossover->doCrossover(new_gen);

        mutation->getMutation(new_gen, Mut_p);

        populationObj = new_gen;
    }
    //std::cout << "best result: " << recordedBest.second << std::endl;
    print(recordedBest.first);
    std::string filename = "testlogs/series_" + std::to_string(param) + "_best_result_" + std::to_string(launch_num) + ".txt";
    std::ofstream file(filename.c_str());
    file << recordedBest.second;
    file.close();
    return recordedBest.second;
}