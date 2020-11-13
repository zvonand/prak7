#pragma once

#include "SolutionVirtClass.h"

class MutationVirtClass {
public:
    MutationVirtClass() = default;

    virtual void mutate(SolutionVirtClass& solution) = 0;

    virtual ~MutationVirtClass() = default;
};
