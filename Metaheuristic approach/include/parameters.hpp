#pragma once

struct MetaParameters {
    unsigned max_iterations;
    unsigned movement_tabu_list_size;
    unsigned max_iter_without_improvement;
    double local_search_parameter_multiplier_1;
    double local_search_parameter_multiplier_2;
    unsigned ls_active_nodes;
    unsigned ls_inactive_nodes;
};

extern MetaParameters meta_parameters;

