#include "Gen_Visitor.h"

Gen_Visitor::Gen_Visitor() : tab(0), in_main_scope(true) {
    // Initialize main_scope, func_scope, global_functions, and type_stack here
    main_scope.clear();
    func_scope.clear();
    instruction_stack.clear();
    compiled_code.clear();
}

void Gen_Visitor::visit_program_start (const Program* node){
    tab = 0; 
    in_main_scope = true;
    main_scope.push_back(scope_t{});
    addNewInstruction(".main");
    addNewInstruction("push 4");
    addNewInstruction("jmp");
    addNewInstruction("halt");

    addBlankInstructions();
    pushInstructionNum(getCurrentInstructionNumber());
    addNewInstruction("oframe");
}
void Gen_Visitor::visit_program_end (const Program* node){
    int instr = popInstructionNum();
    PatchNewInstruction(instr, "push "+std::to_string(main_scope[0].num_var));
    addNewInstruction("cframe");
    addNewInstruction("halt");
    main_scope.pop_back();
    printf("\n================================================================================\n");
    printf("\n=                          Successfull Generated Code                          =\n");
    printf("\n================================================================================\n");
}

/* =========================================================================================================================
 *   Statements
 * =========================================================================================================================
 */

// ----------------------------------------------------------------------------------------------- Assignment
void Gen_Visitor::visit_assignment (const AST_Assignment* node){
    variable_t var = findVariable(node->identifier);
    variable_index_t index = getVariableIndex(node->identifier);

    // If we are dealing with a normal variable just push the index
    if(node->array_index_expression == nullptr && var.length == -1){
        addNewInstruction("push "+std::to_string(index.variable_index));
        addNewInstruction("push "+std::to_string(index.scope_index));
        addNewInstruction("st");
        
    // If we are dealing with an array with an index -> add the index to the variable index
    }else if(node->array_index_expression != nullptr && var.length != -1){
        addNewInstruction("push "+std::to_string(index.variable_index));
        addNewInstruction("add");
        addNewInstruction("push "+std::to_string(index.scope_index));
        addNewInstruction("st");

    // If we are dealing with an array without an index ->
    // push the length to store
    }else{
        addNewInstruction("push "+std::to_string(var.length));
        addNewInstruction("push "+std::to_string(index.variable_index));
        addNewInstruction("push "+std::to_string(index.scope_index));
        addNewInstruction("sta");
    }
}

// ----------------------------------------------------------------------------------------------- Declaration
void Gen_Visitor::visit_var_dec (const AST_VariableDec* node){
    pushVarToScope(variable_t{node->identifier, node->dec_suffix->type, node->length});
    variable_index_t index = getVariableIndex(node->identifier);
    if(node->length == -1){
        addNewInstruction("push "+std::to_string(index.variable_index));
        addNewInstruction("push "+std::to_string(index.scope_index));
        addNewInstruction("st");
    }else{
        addNewInstruction("push "+std::to_string(node->length));
        addNewInstruction("push "+std::to_string(index.variable_index));
        addNewInstruction("push "+std::to_string(index.scope_index));
        addNewInstruction("sta");
    }
}

// ----------------------------------------------------------------------------------------------- Declaration Suffix Norm
void Gen_Visitor::visit_var_dec_suf_norm (const AST_VariableDec_Suffix_Norm*     node){}

// ----------------------------------------------------------------------------------------------- Declaration Suffix Array
void Gen_Visitor::visit_var_dec_suf_array (const AST_VariableDec_Suffix_Array*   node){}

// ----------------------------------------------------------------------------------------------- Print
void Gen_Visitor::visit_print (const AST_Print* node){
    addNewInstruction("print");
}

// ----------------------------------------------------------------------------------------------- Delay
void Gen_Visitor::visit_delay (const AST_Delay* node){
    addNewInstruction("delay");
}

// ----------------------------------------------------------------------------------------------- Write Box
void Gen_Visitor::visit_write (const AST_Write* node){
    addNewInstruction("write");
}

// ----------------------------------------------------------------------------------------------- Write
void Gen_Visitor::visit_write_box (const AST_Write_Box* node){
    addNewInstruction("writebox");
}

// ----------------------------------------------------------------------------------------------- Clear
void Gen_Visitor::visit_clear (const AST_Clear* node){
    addNewInstruction("clear");
}


// ----------------------------------------------------------------------------------------------- Return

void Gen_Visitor::visit_return (const AST_Return* node){
    for(int i = 0; i< func_scope.size()-1; i++){
        addNewInstruction("cframe");
    }
    
    function_t func = global_functions[global_functions.size()-1];

    if(func.return_length == -1){
        addNewInstruction("ret");
    }else{
        addNewInstruction("push "+std::to_string(func.return_length));
        addNewInstruction("reta");
    }
}

// ----------------------------------------------------------------------------------------------- Start If

void Gen_Visitor::visit_start_if (const AST_If* node){
    addNewInstruction("push #PC+4");
    addNewInstruction("cjmp");
    addBlankInstructions(); // instruction to jump to to skip if case
    pushInstructionNum(getCurrentInstructionNumber());
    addNewInstruction("jmp");
}

// ----------------------------------------------------------------------------------------------- End If
void Gen_Visitor::visit_end_if (const AST_If* node){
    int skip_instr  = popInstructionNum();
    
    if(node->block2 != nullptr){ // no else block
        addBlankInstructions(); // instruction to jump to to skip else case
        pushInstructionNum(getCurrentInstructionNumber());
        addNewInstruction("jmp");
    }

    int cur_instr   = getCurrentInstructionNumber();
    PatchNewInstruction(skip_instr, "push #PC+"+std::to_string(cur_instr-skip_instr+1));
}

// ----------------------------------------------------------------------------------------------- Start Else
void Gen_Visitor::visit_start_else (const AST_If* node){}

// ----------------------------------------------------------------------------------------------- End Else
void Gen_Visitor::visit_end_else (const AST_If* node){
    int skip_instr  = popInstructionNum();
    int cur_instr   = getCurrentInstructionNumber();
    PatchNewInstruction(skip_instr, "push #PC+"+std::to_string(cur_instr-skip_instr+1));
}

// ----------------------------------------------------------------------------------------------- Start For
void Gen_Visitor::visit_start_for (const AST_For* node){
    getCurrentScopeStack().push_back(scope_t{});
    addBlankInstructions(); // number of variables for oframe
    pushInstructionNum(getCurrentInstructionNumber());

    addNewInstruction("oframe");
}

// ----------------------------------------------------------------------------------------------- Jump For
void Gen_Visitor::visit_jump_for (const AST_For* node){
    pushInstructionNum(getCurrentInstructionNumber());
}

// ----------------------------------------------------------------------------------------------- Skip For
void Gen_Visitor::visit_skip_for (const AST_For* node){
    addNewInstruction("push #PC+4");
    addNewInstruction("cjmp");

    addBlankInstructions(); // instruction to jump to to skip loop
    pushInstructionNum(getCurrentInstructionNumber());
    addNewInstruction("jmp");
}

// ----------------------------------------------------------------------------------------------- End For
void Gen_Visitor::visit_end_for (const AST_For* node){
    int skip_instr = popInstructionNum();
    int jump_instr = popInstructionNum();
    int ofrm_instr = popInstructionNum();

    PatchNewInstruction(ofrm_instr, "push " + std::to_string(getCurrentScopeStack()[getCurrentScopeStack().size()-1].num_var));

    addNewInstruction("push #PC"+std::to_string(jump_instr - getCurrentInstructionNumber()));
    addNewInstruction("jmp");

    PatchNewInstruction(skip_instr, "push #PC+" + std::to_string(getCurrentInstructionNumber()+1 - skip_instr));

    addNewInstruction("cframe");
    getCurrentScopeStack().pop_back();
}

// ----------------------------------------------------------------------------------------------- Start While
void Gen_Visitor::visit_start_while (const AST_While* node){
    pushInstructionNum(getCurrentInstructionNumber());
}

// ----------------------------------------------------------------------------------------------- Skip While
void Gen_Visitor::visit_skip_while (const AST_While* node){
    addNewInstruction("push #PC+4");
    addNewInstruction("cjmp");

    addBlankInstructions(); // instruction to jump to to skip loop
    pushInstructionNum(getCurrentInstructionNumber());
    addNewInstruction("jmp");
}

// ----------------------------------------------------------------------------------------------- End While
void Gen_Visitor::visit_end_while (const AST_While* node){
    int skip_instr  = popInstructionNum();
    int jmp_instr       = popInstructionNum();


    int cur_instr   = getCurrentInstructionNumber();
    addNewInstruction("push #PC"+std::to_string(jmp_instr-cur_instr));
    addNewInstruction("jmp");

    cur_instr   = getCurrentInstructionNumber();
    PatchNewInstruction(skip_instr,"push #PC+"+std::to_string(cur_instr-skip_instr+1));
}

// ----------------------------------------------------------------------------------------------- Function Declaration Start
void Gen_Visitor::visit_func_dec_start (const AST_Func_Dec* node){
    // ----------------------- Global Function
    function_t this_func;
    this_func.name = node->identifier;
    this_func.return_type = node->type;
    this_func.return_length = node->length;
    global_functions.push_back(this_func);

    // ----------------------- Code Gen
    addBlankInstructions(); // Jump patch

    pushInstructionNum(getCurrentInstructionNumber());
    addNewInstruction("jmp");

    addNewInstruction("."+node->identifier);

    addBlankInstructions(); // variable alloc patch
    pushInstructionNum(getCurrentInstructionNumber());
    addNewInstruction("alloc");
    in_main_scope = false;
    func_scope.clear();
    func_scope.push_back(scope_t{});
    
}

// ----------------------------------------------------------------------------------------------- Function Declaration Skip
void Gen_Visitor::visit_func_dec_skip (const AST_Func_Dec* node){}

// ----------------------------------------------------------------------------------------------- Function Declaration End
void Gen_Visitor::visit_func_dec_end (const AST_Func_Dec* node){
    int alloc_instr = popInstructionNum();
    int jump_instr  = popInstructionNum();
    PatchNewInstruction(alloc_instr, "push "+std::to_string(func_scope[0].num_var));

    int cur_instr   = getCurrentInstructionNumber();

    PatchNewInstruction(jump_instr,"push #PC+"+std::to_string(cur_instr-jump_instr+1));

    func_scope.clear();
    in_main_scope = true;
}

// ----------------------------------------------------------------------------------------------- Formal Parameters
void Gen_Visitor::visit_form_params (const AST_Form_Params* node){}

// ----------------------------------------------------------------------------------------------- Formal Parameter
void Gen_Visitor::visit_form_param (const AST_Form_Param* node){
    global_functions[global_functions.size()-1].param_types.push_back(node->type);
    global_functions[global_functions.size()-1].param_lengths.push_back(node->length);
    pushVarToScope(variable_t{node->identifier, node->type, node->length});
}

// ----------------------------------------------------------------------------------------------- Start Block
void Gen_Visitor::visit_start_block (const AST_Block* node){
    getCurrentScopeStack().push_back(scope_t{});

    //addBlankInstructions(); // Empty space for readibility
    addBlankInstructions(); // Empty space to be patched with the number of variables for frame
    pushInstructionNum(getCurrentInstructionNumber());
    addNewInstruction("oframe");
}

// ----------------------------------------------------------------------------------------------- End Block
void Gen_Visitor::visit_end_block (const AST_Block* node){
    int num_var = getCurrentScopeStack()[getCurrentScopeStack().size()-1].num_var;
    int patch   = popInstructionNum();
    PatchNewInstruction(patch, "push " + std::to_string(num_var));
    addNewInstruction("cframe");
    getCurrentScopeStack().pop_back();
    //addBlankInstructions();
}

// ----------------------------------------------------------------------------------------------- Start Weak Block
void Gen_Visitor::visit_start_weak_block (const AST_Weak_Block* node){}

// ----------------------------------------------------------------------------------------------- End Weak Block
void Gen_Visitor::visit_end_weak_block (const AST_Weak_Block*                       node){}


/* =========================================================================================================================
 *   Expressions
 * =========================================================================================================================
 */
// ----------------------------------------------------------------------------------------------- Term
void Gen_Visitor::visit_term (const AST_Term* node){}

// ----------------------------------------------------------------------------------------------- Simple Expression
void Gen_Visitor::visit_simple_expr (const AST_Simple_Expr* node){}

// ----------------------------------------------------------------------------------------------- Expression
void Gen_Visitor::visit_expr (const AST_Expr* node){}




/* =========================================================================================================================
 *   Factors
 * =========================================================================================================================
 */
// ----------------------------------------------------------------------------------------------- Identifier
void Gen_Visitor::visit_iden (const AST_Identifier* node){
    variable_t var = findVariable(node->identifier);
    variable_index_t index =  getVariableIndex(node->identifier);
    if(var.length == -1){
        addNewInstruction( "push ["+std::to_string(index.variable_index)+ ":"+ std::to_string(index.scope_index)+"]");
    
    }else if(var.length != -1 && node->index_expression != nullptr){
        addNewInstruction( "push +["+std::to_string(index.variable_index)+ ":"+ std::to_string(index.scope_index)+"]");

    }else{
        addNewInstruction( "push " + std::to_string(var.length));
        addNewInstruction( "pusha ["+std::to_string(index.variable_index)+ ":"+ std::to_string(index.scope_index)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- Actual Params 
void Gen_Visitor::visit_act_params (const AST_ActualParams* node){}

// ----------------------------------------------------------------------------------------------- Function Call
void Gen_Visitor::visit_func_call (const AST_FunctionCall* node){
    addNewInstruction("push "+std::to_string(sumFunctionParam(node->identifier)));
    addNewInstruction("push ."+node->identifier);
    addNewInstruction("call");
}

// ----------------------------------------------------------------------------------------------- Sub Expression
void Gen_Visitor::visit_sub_expr (const AST_SubExpression* node){}

// ----------------------------------------------------------------------------------------------- 
void Gen_Visitor::visit_unary (const AST_Unary* node){
    if          (node->op == token_t::NOT){
        addNewInstruction("not");
    }else if    (node->op == token_t::SUB){
        addNewInstruction("push -1");
        addNewInstruction("mult");
    }
    
}

// ----------------------------------------------------------------------------------------------- 
void Gen_Visitor::visit_random (const AST_Random* node){
    addNewInstruction("irnd");
}



/* =========================================================================================================================
 *   Literals
 * =========================================================================================================================
 */

// ----------------------------------------------------------------------------------------------- Literals
void Gen_Visitor::visit_bool (const AST_Boolean* node){
    if(node->bool_token == token_t::TRUE){
        addNewInstruction("push 1");
    }else{
        addNewInstruction("push 0");
    }
}

// ----------------------------------------------------------------------------------------------- Integer
void Gen_Visitor::visit_int (const AST_Integer* node){
    addNewInstruction("push "+node->integer_value);
}

// ----------------------------------------------------------------------------------------------- Float
void Gen_Visitor::visit_float (const AST_Float* node){
    addNewInstruction("push "+node->float_value);
}

// ----------------------------------------------------------------------------------------------- Colour
void Gen_Visitor::visit_colour (const AST_Colour* node){
    addNewInstruction("push "+node->colour_value);
}

// ----------------------------------------------------------------------------------------------- Width
void Gen_Visitor::visit_width (const AST_Width* node){
    addNewInstruction("width");
}

// ----------------------------------------------------------------------------------------------- Height
void Gen_Visitor::visit_height (const AST_Height* node){
    addNewInstruction("height");
}

// ----------------------------------------------------------------------------------------------- Read
void Gen_Visitor::visit_read (const AST_Read* node){
    addNewInstruction("read");
}



/* =========================================================================================================================
 *   Operators
 * =========================================================================================================================
 */
 
// ----------------------------------------------------------------------------------------------- Relational
void Gen_Visitor::visit_rel (const AST_Relational* node){
    if      (node->relational_token == token_t::EQUAL_TO            ){
        addNewInstruction("eq");

    }else if(node->relational_token == token_t::LESS_THAN           ){
        addNewInstruction("lt");

    }else if(node->relational_token == token_t::LESS_THAN_EQUAL     ){
        addNewInstruction("le");

    }else if(node->relational_token == token_t::GREATER_THAN        ){
        addNewInstruction("gt");

    }else if(node->relational_token == token_t::GREATER_THAN_EQUAL  ){
        addNewInstruction("ge");

    }else {
        errMS("Relational Operator", "Unkown Instruction ["+tk_string(node->relational_token)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- Multiplicative
void Gen_Visitor::visit_mult (const AST_Multiplicative* node){
    if      (node->mult_token == token_t::MULT  ){
        addNewInstruction("mul");

    }else if(node->mult_token == token_t::DIV   ){
        addNewInstruction("div");

    }else if(node->mult_token == token_t::AND   ){
        addNewInstruction("and");

    }else {
         errMS("Multiplicative Operator", "Unkown Instruction ["+tk_string(node->mult_token)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- Additive
void Gen_Visitor::visit_add (const AST_Additive* node){
    if      (node->add_token == token_t::ADD    ){
        addNewInstruction("add");

    }else if(node->add_token == token_t::SUB    ){
        addNewInstruction("sub");

    }else if(node->add_token == token_t::OR     ){
        addNewInstruction("or");

    }else {
         errMS("Multiplicative Operator", "Unkown Instruction ["+tk_string(node->add_token)+"]");
    }
}