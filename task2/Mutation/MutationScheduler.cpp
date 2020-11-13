#include "MutationScheduler.h"
#include "SolutionScheduler.h"

#include <iostream>
#include <random>
#include <chrono>

void MutationScheduler::mutate(SolutionVirtClass& solutionVirtInstance) {
    SolutionScheduler& scheduler = dynamic_cast<SolutionScheduler&>(solutionVirtInstance);

    std::mt19937 twisterEngine;
    twisterEngine.seed(time(NULL));

    std::uniform_int_distribution<size_t> uniformDistribution_1(0, scheduler.scheduling.size() - 1);

    // select 2 procs, one of them must have at least one task
    size_t proc_1, proc_2;
    do {
        proc_1 = uniformDistribution_1(twisterEngine);
        proc_2 = uniformDistribution_1(twisterEngine);
    } while (proc_1 == proc_2 || scheduler.scheduling[proc_1].size() == 0);

    // Choose random task on non-empty proc, and move it to another
    std::uniform_int_distribution<size_t> uniformDistribution_2(0, scheduler.scheduling[proc_1].size() - 1);
    
    size_t taskIt = uniformDistribution_2(twisterEngine);
    
    size_t i = 0;
    while (i < scheduler.scheduling[proc_2].size() &&
           (*scheduler.tasksTime)[scheduler.scheduling[proc_2][i]] < (*scheduler.tasksTime)[scheduler.scheduling[proc_1][taskIt]]) {
        i++;
    }

    scheduler.scheduling[proc_2].insert(scheduler.scheduling[proc_2].begin() + i, scheduler.scheduling[proc_1][taskIt]);
    scheduler.scheduling[proc_1].erase(scheduler.scheduling[proc_1].begin() + taskIt);
}
