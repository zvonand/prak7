#include "Genetic.h"

#include <random>
#include <chrono>
#include <algorithm>



population Fitness::getFitness(std::vector<space>& gen) {
    population result;

    for (const auto& s : gen){
        auto sp100 = advanceNSteps(s, 100);
        auto sp101 = advanceNSteps(sp100, 1);

        int c = 0;
        for (const auto& vv : sp100) {
            for (const auto& v : vv) {
                c += v;
            }
        }
        bool stable = true;

        for (int i = 0; i < 50; ++i) {
            for (int j = 0; j < 50; ++j) {
                if (sp100[i][j] != sp101[i][j]) {
                    stable = false;
                    break;
                }
            }
        }

        result.emplace_back(std::make_pair(s, stable ? c / 2500 + 1 : c));
    }

    return result;
}

std::vector<space> Selection::getSelection(population& solution) {
    std::vector<space> result;
    std::vector<int> included_numbers;

    int sum_fit = 0;
    for (const auto& p : solution) {
        sum_fit += p.second;
    }

    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, sum_fit-1);

    while (result.size() < 50) {
        int count = distribution(generator);
        int i = -1;
        while (count >= 0) {
            ++i;
            count -= solution[i].second;
        }
        bool wb = false;
        for (const auto& nnn : included_numbers) {
            if (nnn == i) {
                wb = true;
                break;
            }
        }
        if (!wb) {
            result.push_back(solution[i].first);
            included_numbers.push_back(i);
        }
    }
    return result;
}


void Crossing::doCrossover(std::vector<space>& solution) {
    std::vector<space> new_gen;
    int first, second, pos11, pos12, pos21, pos22;

    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

    std::uniform_real_distribution<double> realDistribution(0.0, 1.0);
    std::uniform_int_distribution<int> intDistribution(0, 49);

    while (new_gen.size() < 50) {
        first = intDistribution(generator);
        do {
            second = intDistribution(generator);
        } while (first == second);

        pos11 = intDistribution(generator); pos12 =  intDistribution(generator);
        pos21 = intDistribution(generator); pos22 =  intDistribution(generator);

        if (realDistribution(generator) < 0.8) {
            auto neu = solution[first];

            for (int i = std::min(pos11, pos21); i <= std::max(pos11, pos21); ++i) {
                for (int j = std::min(pos12, pos22); j <= std::max(pos12, pos22); ++j) {
                    neu[i][j] = solution[second][i][j];
                }
            }
            new_gen.emplace_back(neu);
        }
    }

    for (const auto& i : new_gen) {
        solution.emplace_back(i);
    }
}

void Mutation::getMutation(std::vector<space> &solution, double P_mut) {
    for (auto &item : solution) {
        for (int i = 0; i < 50; ++i)
            for (int j = 0; j < 50; ++j) {
                if ((rand() % 100) / (100.0) > P_mut)
                    item[i][j] = (item[i][j] + 1) % 2;
            }
    }
}