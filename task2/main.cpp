#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include "tinyxml2.h"

#include "Temp.h"
#include "AnnealingSim.h"
#include "SolutionScheduler.h"
#include "MutationScheduler.h"

# define ll long long

// In global scope to hold it in one place to easily modify if needed
const double INIT_TEMPERATURE = 10E5;
const size_t MAX_ITER_WO_UPDATE = 10;


void logger(SolutionScheduler* ans, ll elapsed_ms) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile("test.xml");
    ll answer = std::atol(doc.FirstChildElement("Answer")->GetText());

    std::cout << std::setw(13) << elapsed_ms
    << std::setw(13) << (((ans->getEnergy() - answer) * 100.0 / ans->getEnergy()))
//  << " |" << std::setw(13) << ans->getEnergy() << " / " << answer
    << std::endl;
}

void multiThread(size_t numThreads) {
    SolutionScheduler* ans = 0;
    std::vector<AnnealingSim<SolutionScheduler, MutationScheduler, Temp2>> solvers;
    for (size_t i = 0; i < numThreads; i++) {
        solvers.emplace_back("test.xml", INIT_TEMPERATURE);
    }
    auto startTime = std::chrono::steady_clock::now();

    size_t lastUpdated = 0;
    while (lastUpdated <= MAX_ITER_WO_UPDATE) {
        std::vector<std::thread> threadPool;

        //computing res foreach
        for (size_t i = 0; i < numThreads; i++) {
            threadPool.emplace_back([&solvers](int i) {solvers[i].start();}, i);
        }
        for (auto& thread : threadPool) {
            thread.join();
        }

        //vergleich die Loesung
        if (!ans) {
            ans = dynamic_cast<SolutionScheduler*>(solvers[0].getSolution());
        }

        for (auto& solver : solvers) {
            if (ans->getEnergy() > solver.getSolution()->getEnergy()) {
                lastUpdated = 0;
                ans = dynamic_cast<SolutionScheduler*>(solver.getSolution());
            }
        }

        for (auto& i : solvers) {
            i.updateSolution(ans);
        }
        lastUpdated++;
    }

    auto endTime = std::chrono::steady_clock::now();
    logger(ans, std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
}

int main(int argc, char *argv[]) {
    size_t numThreads = (argc == 2) ? std::atoi(argv[1]) : std::thread::hardware_concurrency();
    // std::cout << "Threads: " << numThreads << std::endl;

    multiThread(numThreads);

    return 0;
}
