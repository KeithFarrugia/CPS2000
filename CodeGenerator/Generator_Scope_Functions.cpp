#include "Gen_Visitor.h"
/* =========================================================================================================================
 *  ---------------- Get the current scope
 * There are 2 possible scope stacks
 *  - One is for a function declaration
 *  - the other is for the main function 
 * =========================================================================================================================
 */
std::vector<scope_t>& Gen_Visitor::getCurrentScopeStack(){
    if(in_main_scope){
        return main_scope;
    }else{
        return func_scope;
    }
}

/* =========================================================================================================================
 *  ---------------- Get the variable index
 * This generates the variable index while searching for that variable in the scope
 * =========================================================================================================================
 */

variable_index_t Gen_Visitor::getVariableIndex(std::string variable_name){
    std::vector<scope_t>& current_scope = getCurrentScopeStack();
    for(int i = 0; i < current_scope.size(); i++){
        int scope_index = current_scope.size()-1-i;
        int var_index = 0;
        for(int j =  0 ; j < current_scope[scope_index].variables.size();  j++){
            if(current_scope[scope_index].variables[j].name == variable_name){
                return variable_index_t{var_index, i};
            }else if(isType_an_Array(current_scope[scope_index].variables[j].type)){
                var_index += current_scope[scope_index].variables[j].length;
            }else{
                var_index++;
            }
        }
    }
    return variable_index_t{-1, -1};
}

/* =========================================================================================================================
 *  ---------------- Push a variable to the current scope
 *  - Gets the current scope stack (main /function dec)
 *  - goes the to top of the stack and pushes a variable
 * =========================================================================================================================
 */
void Gen_Visitor::pushVarToScope(variable_t var){
    std::vector<scope_t>& current_scope = getCurrentScopeStack();
    current_scope[current_scope.size()-1].variables.push_back(var);
    if(var.length == -1){
        current_scope[current_scope.size()-1].num_var++;
    }else{
        current_scope[current_scope.size()-1].num_var += var.length;
    }
};

/* =========================================================================================================================
 *  ---------------- Push A new Instruction
 *  - Adds a new instruction to the compiled code
 * =========================================================================================================================
 */
void Gen_Visitor::addNewInstruction(std::string instruction){
    compiled_code.push_back(instruction);
}

/* =========================================================================================================================
 *  ---------------- Push a blank instruction
 * Pushes a blank instruction to the scope stack.
 * All blank instructions need to be patches/modified later as else they will create issues in 
 * the jump statements as they are not counted by the vm
 * =========================================================================================================================
 */
int Gen_Visitor::addBlankInstructions(){
    compiled_code.push_back("");
    return compiled_code.size()-1;
}

/* =========================================================================================================================
 *  ---------------- Patch Instruction
 * - This takes a location for an empty instruction,
 * - Makes sure it is empty
 * - And then replaces it with the passed instruction
 * =========================================================================================================================
 */
void Gen_Visitor::PatchNewInstruction( int num, std::string instruction){
    if (compiled_code[num] != ""){
        errMS("Patch New Instruction", "already an instruction at ["+std::to_string(num)+"] cannot override");
    }
    compiled_code[num] = instruction;
}

/* =========================================================================================================================
 *  ---------------- Get the current instruction number
 * gets the current instruction number by accessing the size of the list
 * =========================================================================================================================
 */
int Gen_Visitor::getCurrentInstructionNumber(){
    return compiled_code.size()-1;
}

/* =========================================================================================================================
 *  ---------------- Pus an instruction number
 * pushes the instruction number into the instruction stack.
 * =========================================================================================================================
 */
void Gen_Visitor::pushInstructionNum(int num){
    instruction_stack.push_back(num);
}

/* =========================================================================================================================
 *  ---------------- Pop instruction number
 * Pops the last pushed instruction from the instruction stack
 * =========================================================================================================================
 */
int  Gen_Visitor::popInstructionNum(){
    int x = instruction_stack[instruction_stack.size()-1];
    instruction_stack.pop_back();
    return x;
}


/* =========================================================================================================================
 *  ---------------- Find Function
 * Searches for the function in the global function list
 * =========================================================================================================================
 */
const function_t Gen_Visitor::findFunction(std::string function_name){

    if(global_functions.empty() == true){ return function_t{"Not Found",std::vector<token_t>(), }; }

    for(int i = 0; i < global_functions.size(); i++){
        if(global_functions[i].name == function_name){
            return global_functions[i];
        }
    }
    return function_t{"Not Found",std::vector<token_t>(), };
}

/* =========================================================================================================================
 *  ---------------- Find Variable
 * tries to find the variable by traversing the scopes starting from the top most stack
 * =========================================================================================================================
 */
const variable_t Gen_Visitor::findVariable(std::string variable_name){
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
 *  ---------------- Sum Total Parameters
 * This function sums the total number of parameters (including arrays)
 * needed for a function call.
 * =========================================================================================================================
 */
int Gen_Visitor::sumFunctionParam (std::string function_name){
    function_t func = findFunction(function_name);
    int total=0;
    for(int len : func.param_lengths){
        if(len == -1){
            total+=1;
        }else{
            total += len;
        }
    }
    return total;
}