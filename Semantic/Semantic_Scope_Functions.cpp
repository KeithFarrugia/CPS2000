#include "Semantic_Visitor.h"

/* =========================================================================================================================
 *  ---------------- Get the current scope
 * There are 2 possible scope stacks
 *  - One is for a function declaration
 *  - the other is for the main function 
 * =========================================================================================================================
 */
std::vector<scope_t>& Semantic_Visitor::getCurrentScopeStack(){
    if(in_main_scope){
        return main_scope;
    }else{
        return func_scope;
    }
}

/* =========================================================================================================================
 *  ---------------- Find Variable
 * tries to find the variable by traversing the scopes starting from the top most stack
 * =========================================================================================================================
 */
const variable_t Semantic_Visitor::findVariable(std::string variable_name){
    std::vector<scope_t>& current_scope = getCurrentScopeStack();

    if(current_scope.empty() == true){ return variable_t{"Not Found", NULL_TOKEN}; }
    
    for(int i = current_scope.size()-1; i >=0; --i){
        for(int j = current_scope[i].variables.size()-1; j >=0; --j){
            if(current_scope[i].variables[j].name == variable_name){
                return current_scope[i].variables[j];
            }
        }
    }
    return variable_t{"Not Found", NULL_TOKEN};
}

/* =========================================================================================================================
 *  ---------------- Find Function
 * Searches for the function in the global function list
 * =========================================================================================================================
 */
const function_t Semantic_Visitor::findFunction(std::string function_name){

    if(global_functions.empty() == true){ return function_t{"Not Found",std::vector<token_t>(), }; }

    for(int i = 0; i < global_functions.size(); i++){
        if(global_functions[i].name == function_name){
            return global_functions[i];
        }
    }
    return function_t{"Not Found",std::vector<token_t>(), std::vector<int>(), token_t::NULL_TOKEN};
}

/* =========================================================================================================================
 *  ---------------- Is variable name use?
 * returns true or false if the variable's name is already in use in the current scope 
 * =========================================================================================================================
 */
bool Semantic_Visitor::isVariableNameUsed(std::string variable_name){
    std::vector<scope_t>& current_scope = getCurrentScopeStack();

    if(current_scope.empty() == true){ return false; }
    
    for(int i = current_scope[current_scope.size()-1].variables.size()-1; i >=0; --i){
        if(current_scope[current_scope.size()-1].variables[i].name == variable_name){
            return true;
        }
    }
    return false;
}

/* =========================================================================================================================
 *  ---------------- Is function name use?
 * returns true or false if the function name is used in the global function scope
 * =========================================================================================================================
 */
bool Semantic_Visitor::isFunctionNameUsed(std::string function_name){
    
    if(global_functions.empty() == true){ return false; }

    for(int i = 0; i > global_functions.size(); i++){
        if(global_functions[i].name == function_name){
            return true;
        }
    }
    return false;
}

/* =========================================================================================================================
 *  ---------------- Push a variable to the current scope
 *  - Gets the current scope stack (main /function dec)
 *  - goes the to top of the stack and pushes a variable
 * =========================================================================================================================
 */
void Semantic_Visitor::pushVarToScope(variable_t var){
    std::vector<scope_t>& current_scope = getCurrentScopeStack();
    current_scope[current_scope.size()-1].variables.push_back(var);
    current_scope[current_scope.size()-1].num_var++;
};

/* =========================================================================================================================
 *  ---------------- Pop the type stack
 * =========================================================================================================================
 */
type_set_t Semantic_Visitor::popTypeStack(){
    if(!type_stack.empty()){
        type_set_t type = type_stack[type_stack.size()-1];
        type_stack.pop_back();
        return type;
    }else{
        errMS("Type Stack", "Pop", "Stack is empty");
    }
    return type_set_t{-1, NULL_TOKEN};
}

/* =========================================================================================================================
 *  ---------------- Push to the type stack
 * =========================================================================================================================
 */
void Semantic_Visitor::pushTypeStack(token_t t){
    type_stack.push_back(type_set_t{-1, t});
}

void Semantic_Visitor::pushTypeStack(token_t t, int l){
    type_stack.push_back(type_set_t{l, t});
}