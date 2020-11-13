#include "MutationVirtClass.h"

class MutationScheduler : public MutationVirtClass {
public:
    MutationScheduler() = default;
    virtual void mutate(SolutionVirtClass& solutionVirtInstance) override;
    virtual ~MutationScheduler() = default;
};
