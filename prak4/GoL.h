#ifndef PRAK4_GOL_H
#define PRAK4_GOL_H

#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include <unistd.h>

using state = std::vector<std::vector<int>>;

inline state generateState(const int dim=50) {
    state population(dim, std::vector<int>(dim));
    std::srand(std::time(nullptr));
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            population[i][j] = std::rand() % 2;
        }
    }
    return population;
}

inline state nextState(const state& pred) {
    int size = pred.size();
    state newPop(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int isAlive = pred[i][j];
            int neighborsAlive = 0;
            for (int k = i-1; k <= i+1; ++k) {
                for (int m = j-1; m <= j+1; ++m) {
                    if ((k == i && m == j) || (k<0) || (k==size) || (m<0) || (m==size)) {
                        continue;
                    }
                    neighborsAlive += pred[k][m];
                }
            }
            if (isAlive) {
                if (neighborsAlive != 2 && neighborsAlive != 3) {
                    newPop[i][j] = 0;
                } else {
                    newPop[i][j] = 1;
                }
            } else {
                if (neighborsAlive == 3) {
                    newPop[i][j] = 1;
                } else {
                    newPop[i][j] = 0;
                }
            }
        }
    }
    return newPop;
}

inline state advanceNSteps(const state& s, int steps) {
    auto new_s = s;
    for (int i = 0; i < steps; ++i) {
        new_s = nextState(new_s);
    }
    return new_s;
}

#endif
