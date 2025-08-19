#include "setcoveringsolver/instance_builder.hpp"
#include "setcoveringsolver/solution.hpp"
#include "setcoveringsolver/algorithms/local_search_row_weighting.hpp"

using namespace setcoveringsolver;

int main(int argc, char *argv[])
{
    LocalSearchRowWeightingParameters parameters;
    parameters.verbosity_level = 0;
    parameters.timer.set_time_limit(285);
    parameters.reduction_parameters.timer.set_time_limit(100);
    parameters.reduction_parameters.twin = false;
    parameters.enable_new_solution_callback = false;
    parameters.best_solution_update_frequency = std::numeric_limits<Counter>::max();

    // Build instance.
    InstanceBuilder instance_builder;
    instance_builder.read_pace2025_ds(stdin);
    const Instance instance = instance_builder.build();

    std::mt19937_64 generator(0);

    // Run.
    auto output = local_search_row_weighting(instance, generator, nullptr, parameters);

    output.solution.write_pace2025(std::cout);

    std::_Exit(0);
    return 0;
}
