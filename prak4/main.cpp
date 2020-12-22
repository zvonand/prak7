#include "cmath"
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include "HeadCycle.h"

int main(int argc, char *argv[]) {
    for (int pmut_modifier = 0; pmut_modifier < 10; ++pmut_modifier) {
        int best = 0;
        int worst = 25000;
        auto start = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        auto max_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        int launch;
        double P_mut = (1 / pow(50, 2)) * (pow(1.5, pmut_modifier));
        std::cout << P_mut << std::endl;
        for (launch = 0; launch < 10; ++launch) {
            HeadCycle headCycle;
            start = std::chrono::steady_clock::now();
            int res = headCycle.Start(P_mut, pmut_modifier, launch);
            end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            if (elapsed_ms > max_time) {
                max_time = elapsed_ms;
            }

            if (res > best) {
                best = res;
            }
            if (res < worst) {
                worst = res;
            }
        }

        std::string filename = "testlogs/wb_series_" + std::to_string(pmut_modifier) + ".txt";
        std::ofstream file(filename.c_str());
        file << "  Best: " << best << "  Stability: " << best-worst << "Max_time" << max_time;
        file.close();
        std::cout << "Stability: " << best-worst << "  Best: " << best << "  Max_time: " << max_time << std::endl;
    }

    return 0;
}
