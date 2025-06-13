#include "setcoveringsolver/instance_builder.hpp"
#include "setcoveringsolver/solution.hpp"
#include "setcoveringsolver/algorithms/local_search_row_weighting.hpp"
#include "setcoveringsolver/algorithms/large_neighborhood_search.hpp"
#include "setcoveringsolver/algorithm_formatter.hpp"

using namespace setcoveringsolver;

Output optimize(
        const Instance& instance,
        std::mt19937_64& generator,
        const Parameters& parameters)
{
    Output output(instance);
    AlgorithmFormatter algorithm_formatter(parameters, output);
    algorithm_formatter.start("Optimize");

    // Reduction.
    if (parameters.reduction_parameters.reduce) {
        return solve_reduced_instance(
                [&generator](
                    const Instance& instance,
                    const Parameters& parameters)
                {
                    return optimize(
                            instance,
                            generator,
                            parameters);
                },
                instance,
                parameters,
                algorithm_formatter,
                output);
    }

    algorithm_formatter.print_header();

    if (!parameters.timer.needs_to_end()) {
        LargeNeighborhoodSearchParameters lns_parameters;
        lns_parameters.verbosity_level = 0;
        lns_parameters.reduction_parameters.reduce = false;
        lns_parameters.enable_new_solution_callback = parameters.enable_new_solution_callback;
        lns_parameters.maximum_number_of_iterations_without_improvement
            = 10 * instance.number_of_sets();
        //lns_parameters.timer = parameters.timer;
        lns_parameters.timer.set_time_limit(parameters.timer.remaining_time() / 2);
        lns_parameters.goal = output.bound;
        auto lns_output = large_neighborhood_search(instance, lns_parameters);
        algorithm_formatter.update_solution(lns_output.solution, "lns");
    }

    if (!parameters.timer.needs_to_end()
            && output.solution.cost() != output.bound) {
        LocalSearchRowWeighting2Parameters rwls_parameters;
        rwls_parameters.verbosity_level = 0;
        rwls_parameters.reduction_parameters.reduce = false;
        rwls_parameters.enable_new_solution_callback = parameters.enable_new_solution_callback;
        rwls_parameters.timer = parameters.timer;
        rwls_parameters.goal = output.bound;
        auto rwls_output = local_search_row_weighting_2(instance, generator, &output.solution, rwls_parameters);
        algorithm_formatter.update_solution(rwls_output.solution, "rwls");
    }

    algorithm_formatter.end();
    return output;
}

int main(int argc, char *argv[])
{
    Parameters parameters;
    parameters.verbosity_level = 0;
    parameters.timer.set_time_limit(295);
    parameters.reduction_parameters.timer.set_time_limit(150);
    parameters.reduction_parameters.reduce = true;
    parameters.reduction_parameters.remove_dominated = true;
    parameters.enable_new_solution_callback = false;

    // Build instance.
    InstanceBuilder instance_builder;
    instance_builder.read_pace2025(stdin);
    const Instance instance = instance_builder.build();

    std::mt19937_64 generator(0);

    // Run.
    auto output = optimize(instance, generator, parameters);

    output.solution.write_pace2025(std::cout);

    return 0;
}
