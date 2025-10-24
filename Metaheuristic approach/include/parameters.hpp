#pragma once

struct MetaParameters {
    enum class LocalSearchType {
        FirstImprovement,
        BestImprovement
    };
    unsigned max_iterations;
    unsigned movement_tabu_list_size;
    unsigned max_iter_without_improvement;
    double local_search_parameter_multiplier_1;
    double local_search_parameter_multiplier_2;
    unsigned ls_active_nodes;
    unsigned ls_inactive_nodes;
    double aspiration_multiplier;
    LocalSearchType local_search_type;

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream&, const MetaParameters&);
};

void load_meta_parameters(const std::string&);

extern MetaParameters meta_parameters;

