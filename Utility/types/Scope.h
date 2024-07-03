#ifndef SEMANTIC_H
#define SEMANTIC_H
#include "Tokens.h"
#include <vector>
#include <algorithm>

typedef struct{
    int variable_index;
    int scope_index;
}variable_index_t;

typedef struct {
    std::string name;
    token_t type;
    int length;
}variable_t;

typedef struct{
    std::string name;
    std::vector<token_t> param_types;
    std::vector<int> param_lengths;
    token_t return_type;
    int return_length;
}function_t;


typedef struct{
    int         length;
    token_t     type;
}type_set_t;

typedef struct{
    int num_var;
    std::vector<variable_t> variables;
}scope_t;

#endif //SEMANTIC_H