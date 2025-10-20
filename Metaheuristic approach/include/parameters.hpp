#pragma once

struct MetaParameters {
    unsigned max_iterations;
    unsigned movement_tabu_list_size;
    unsigned max_iter_without_improvement;
};

extern MetaParameters meta_parameters;

