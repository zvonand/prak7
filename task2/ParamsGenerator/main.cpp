#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    size_t nProcs = 4;
    size_t nTasks = 30000;
    size_t minTime = 1;
    size_t maxTime = 100;
    if (argc == 5) {
        nProcs = std::stoi(argv[1]);
        nTasks = std::stoi(argv[2]);
        minTime = std::stoi(argv[3]);
        maxTime = std::stoi(argv[4]);
    } else {
        std::cout << "Wrong number of arguments, default values are being used.\n"
                     "Usage: ./TesGen [nProcs] [nTasks] [minTime] [maxTask]" << std::endl;
    }

    std::ofstream fout("test.xml", std::ios_base::out | std::ios_base::trunc);
    fout << "<Proc>\n<Num>" << nProcs << "</Num>\n</Proc>\n";
    fout << "<Task>\n<Num>" << nTasks << "</Num>\n";
    fout << "<Time>";
    std::mt19937 twisterEngine;
    twisterEngine.seed(time(NULL));
    std::uniform_int_distribution<size_t> uniformIntDistribution(minTime , maxTime);
    std::vector<size_t> tasksDuration(nTasks);
    for (size_t i = 0; i < nTasks; i++) {
        tasksDuration[i] = uniformIntDistribution(twisterEngine);
        fout << tasksDuration[i] << ' ';

    }
    fout << "</Time>\n</Task>\n";

    std::sort(tasksDuration.begin(), tasksDuration.end());
    size_t answer = 0;
    for (size_t i = 0; i < nTasks; i += nProcs) {
        for (size_t j = 0 ; j < nProcs && i + j < nTasks; j++) {
            answer += tasksDuration[i + j];
            if (i + j + nProcs < nTasks) {
                tasksDuration[i + j + nProcs] += tasksDuration[i + j];
            }
        }
    }
    fout << "<Answer>" << answer << "</Answer>\n";
    return 0;
}
