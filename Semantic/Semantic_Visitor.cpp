#include "Semantic_Visitor.h"

Semantic_Visitor::Semantic_Visitor() : tab(0), in_main_scope(true) {
    // Initialize main_scope, func_scope, global_functions, and type_stack here
    main_scope.clear();
    func_scope.clear();
    global_functions.clear();
    type_stack.clear();
    main_scope.push_back(scope_t{});
}

void Semantic_Visitor::visit_program_start (const Program* node){
    tab = 0; 
    in_main_scope = true;
}
void Semantic_Visitor::visit_program_end (const Program* node){
    main_scope.pop_back();
    printf("\n================================================================================\n");
    printf("\n=                         Successfull Semantic Parsing                         =\n");
    printf("\n================================================================================\n");
}

/* =========================================================================================================================
 *   Statements
 * =========================================================================================================================
 */

// ----------------------------------------------------------------------------------------------- Assignment
void Semantic_Visitor::visit_assignment (const AST_Assignment* node){
    variable_t var = findVariable(node->identifier);
    type_set_t expr_type = popTypeStack();

    if(isType_an_Array(var.type) && node->array_index_expression != nullptr){
        // Convert array to normal var if the index is specified
        var.type = convert_Array_to_Type(var.type);
        var.length = -1;
    }else if(!isType_an_Array(var.type) && node->array_index_expression != nullptr){
        errMS("Assignment", node->identifier, "Cannot specify an index on a non-array variable");
    }

    if(var.type == token_t::NULL_TOKEN){
        errMS("Assignment", node->identifier, "Variable not found");

    }else if(   (var.type == token_t::FLOAT         && expr_type.type == token_t::INT       ) ||
                (var.type == token_t::FLOAT_ARRAY   && expr_type.type == token_t::INT_ARRAY )      ){ 
        /* DO NOTING - It is ok */

    }else if(var.length != expr_type.length){
        errMS("Assignment", node->identifier, "Cannot assign an expression of length [" +std::to_string(expr_type.length)+ "] to a variable of length ["+std::to_string(var.length)+"]");

    }else if(var.type != expr_type.type){
        errMS("Assignment", node->identifier, "Variable is of type [" + tk_string(var.type) + "] found ["+tk_string(expr_type.type)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- Declaration
void Semantic_Visitor::visit_var_dec (const AST_VariableDec* node){
    if(isVariableNameUsed(node->identifier) == true){
        errMS("Variable Declaration", node->identifier, "Variable name is already in use in current scope");
    };
    type_set_t var_type = popTypeStack();
    if(node->dec_suffix)
    pushVarToScope(variable_t{node->identifier, var_type.type, var_type.length });
}

// ----------------------------------------------------------------------------------------------- Declaration Suffix Norm
void Semantic_Visitor::visit_var_dec_suf_norm (const AST_VariableDec_Suffix_Norm*     node){
    token_t expr_type = popTypeStack().type;
    if          (node->type == token_t::FLOAT && expr_type == token_t::INT){ 
    
    } else if   (node->type != expr_type){
        errMS("Variable Dec Suffix", "Variable is of type ["+tk_string(node->type)+"] but found ["+tk_string(expr_type)+"]");
    }
    pushTypeStack(node->type);
}

// ----------------------------------------------------------------------------------------------- Declaration Suffix Array
void Semantic_Visitor::visit_var_dec_suf_array (const AST_VariableDec_Suffix_Array* node){
    token_t array_type = convert_Array_to_Type(node->type);
    for(int i = 0; i < node->literal_list.size(); i++){
        token_t expr_type = popTypeStack().type;
        if          (array_type == token_t::FLOAT && expr_type == token_t::INT){ 
        
        } else if   (array_type != expr_type){
            errMS("Variable Dec Suffix Array", "Array is of type ["+tk_string(node->type)+"] but found ["+tk_string(expr_type)+"]");
        }
    }
    pushTypeStack(node->type, node->literal_list.size());
}

// ----------------------------------------------------------------------------------------------- Print
void Semantic_Visitor::visit_print (const AST_Print* node){
    token_t expr_type = popTypeStack().type;
    if(isType_an_Array(expr_type)){
        errMS("Print", "Cannot print an array");
    }
}

// ----------------------------------------------------------------------------------------------- Delay
void Semantic_Visitor::visit_delay (const AST_Delay* node){
    token_t expr_type = popTypeStack().type;
    if(expr_type != token_t::INT){
        errMS("Delay", "Expects type [Int] but found ["+tk_string(expr_type)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- Write Box
void Semantic_Visitor::visit_write (const AST_Write* node){
    token_t x = popTypeStack().type;
    if(x != token_t::INT){errMS("Write", "1st parameter expects type [int] but found ["+tk_string(x)+"]"); }

    token_t y = popTypeStack().type;
    if(y != token_t::INT){errMS("Write", "2nd parameter expects type [int] but found ["+tk_string(y)+"]"); }

    token_t colour = popTypeStack().type;
    if(colour != token_t::COLOUR){errMS("Write", "3rd parameter expects type [colour] but found ["+tk_string(colour)+"]"); }
}

// ----------------------------------------------------------------------------------------------- Write
void Semantic_Visitor::visit_write_box (const AST_Write_Box* node){
    token_t x = popTypeStack().type;
    if(x != token_t::INT){errMS("Write Box", "1st parameter expects type [int] but found ["+tk_string(x)+"]"); }

    token_t y = popTypeStack().type;
    if(y != token_t::INT){errMS("Write Box", "2nd parameter expects type [int] but found ["+tk_string(y)+"]"); }

    token_t h = popTypeStack().type;
    if(h != token_t::INT){errMS("Write Box", "3rd parameter expects type [int] but found ["+tk_string(h)+"]"); }

    token_t w = popTypeStack().type;
    if(w != token_t::INT){errMS("Write Box", "4th parameter expects type [int] but found ["+tk_string(w)+"]"); }

    token_t colour = popTypeStack().type;
    if(colour != token_t::COLOUR){errMS("Write Box", "5th parameter expects type [colour] but found ["+tk_string(colour)+"]"); }
    
}

// ----------------------------------------------------------------------------------------------- Clear
void Semantic_Visitor::visit_clear (const AST_Clear* node){

    token_t colour = popTypeStack().type;
    if(colour != token_t::COLOUR){errMS("Clear", "Expects type [colour] but found ["+tk_string(colour)+"]"); }
    
}


// ----------------------------------------------------------------------------------------------- Return

void Semantic_Visitor::visit_return (const AST_Return* node){
    if(in_main_scope == true){
        errMS("Return","Can only be in a function");
    }
    function_t func = global_functions[global_functions.size()-1];
    type_set_t expr_type = popTypeStack();

    if(func.return_length != expr_type.length ){
        errMS(  "Function ["+func.name+"]", "Return", "Function return length is ["+std::to_string(func.return_length)+"] but found expression of length ["+std::to_string(expr_type.length)+"]");

    }else if(   (func.return_type == token_t::FLOAT          && expr_type.type == token_t::INT       ) ||
                (func.return_type == token_t::FLOAT_ARRAY    && expr_type.type == token_t::INT_ARRAY )       ){
            /* DO Nothing - This is Correct*/

    }else if(func.return_type != expr_type.type){
        errMS(  "Function ["+func.name+"]", "Return", "Function Return type is ["+tk_string(func.return_type)+"] but found ["+tk_string(expr_type.type)+"]");
    }

    pushTypeStack(func.return_type);
    
    if(tab == 3){ func_has_return = true; }
}

// ----------------------------------------------------------------------------------------------- Start If

void Semantic_Visitor::visit_start_if (const AST_If* node){
    token_t expr_type = popTypeStack().type;
    if(expr_type != token_t::BOOL){
        errMS("If","Condition expects Boolean Value, but found ["+tk_string(expr_type)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- End If
void Semantic_Visitor::visit_end_if (const AST_If* node){}

// ----------------------------------------------------------------------------------------------- Start Else
void Semantic_Visitor::visit_start_else (const AST_If* node){}

// ----------------------------------------------------------------------------------------------- End Else
void Semantic_Visitor::visit_end_else (const AST_If* node){}

// ----------------------------------------------------------------------------------------------- Start For
void Semantic_Visitor::visit_start_for           (const AST_For*                         node){
    getCurrentScopeStack().push_back(scope_t{});
}

// ----------------------------------------------------------------------------------------------- Jump For
void Semantic_Visitor::visit_jump_for (const AST_For* node){}

// ----------------------------------------------------------------------------------------------- Skip For
void Semantic_Visitor::visit_skip_for (const AST_For* node){
    token_t expr_type = popTypeStack().type;
    if(expr_type != token_t::BOOL){
        errMS("For","Condition expects Boolean Value, but found ["+tk_string(expr_type)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- End For
void Semantic_Visitor::visit_end_for (const AST_For* node){
    getCurrentScopeStack().pop_back();
}

// ----------------------------------------------------------------------------------------------- Start While
void Semantic_Visitor::visit_start_while (const AST_While* node){}

// ----------------------------------------------------------------------------------------------- Skip While
void Semantic_Visitor::visit_skip_while (const AST_While* node){
    token_t expr_type = popTypeStack().type;
    if(expr_type != token_t::BOOL){
        errMS("While","Condition expects Boolean Value, but found ["+tk_string(expr_type)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- End While
void Semantic_Visitor::visit_end_while (const AST_While* node){}

// ----------------------------------------------------------------------------------------------- Function Declaration Start
void Semantic_Visitor::visit_func_dec_start (const AST_Func_Dec* node){
    if(in_main_scope == false || tab != 1){
        errMS("Function Declaration", "Can only declare a function in main block");
    }
    if(isFunctionNameUsed(node->identifier)){
        errMS("Function Declaration", "Function name is already in use");
    }
    in_main_scope = false;
    func_has_return = false;

    func_scope.clear();
    func_scope.push_back(scope_t{});

    function_t this_func;
    this_func.name = node->identifier;
    this_func.return_type = node->type;
    this_func.return_length = node->length;

    global_functions.push_back(this_func);
}

// ----------------------------------------------------------------------------------------------- Function Declaration Skip
void Semantic_Visitor::visit_func_dec_skip (const AST_Func_Dec* node){}

// ----------------------------------------------------------------------------------------------- Function Declaration End
void Semantic_Visitor::visit_func_dec_end (const AST_Func_Dec* node){
    if(func_has_return == false){
        errMS("Function Dec End", "Function must have at least 1 return statement in its main scope");
    }
    func_has_return = false;
    func_scope.clear();
    in_main_scope = true;
}

// ----------------------------------------------------------------------------------------------- Formal Parameters
void Semantic_Visitor::visit_form_params (const AST_Form_Params* node){}

// ----------------------------------------------------------------------------------------------- Formal Parameter
void Semantic_Visitor::visit_form_param (const AST_Form_Param* node){
    if(isVariableNameUsed(node->identifier)){
        errMS("Formal Parameter", global_functions[global_functions.size()-1].name, "Parameter name ["+node->identifier+"] is already in use");
    }
    global_functions[global_functions.size()-1].param_types.push_back(node->type);
    global_functions[global_functions.size()-1].param_lengths.push_back(node->length);
    pushVarToScope(variable_t{node->identifier, node->type, node->length});
}

// ----------------------------------------------------------------------------------------------- Start Block
void Semantic_Visitor::visit_start_block (const AST_Block* node){
    getCurrentScopeStack().push_back(scope_t{});
}

// ----------------------------------------------------------------------------------------------- End Block
void Semantic_Visitor::visit_end_block (const AST_Block* node){
    getCurrentScopeStack().pop_back();
}

// ----------------------------------------------------------------------------------------------- Start Weak Block
void Semantic_Visitor::visit_start_weak_block (const AST_Weak_Block* node){}

// ----------------------------------------------------------------------------------------------- End Weak Block
void Semantic_Visitor::visit_end_weak_block (const AST_Weak_Block*                       node){}


/* =========================================================================================================================
 *   Expressions
 * =========================================================================================================================
 */
// ----------------------------------------------------------------------------------------------- Term
void Semantic_Visitor::visit_term (const AST_Term* node){}

// ----------------------------------------------------------------------------------------------- Simple Expression
void Semantic_Visitor::visit_simple_expr (const AST_Simple_Expr* node){}

// ----------------------------------------------------------------------------------------------- Expression
void Semantic_Visitor::visit_expr (const AST_Expr* node){
    if(node->forced_type != NULL_TOKEN){
        popTypeStack();
        pushTypeStack(node->forced_type);
    }
}




/* =========================================================================================================================
 *   Factors
 * =========================================================================================================================
 */
// ----------------------------------------------------------------------------------------------- Identifier
void Semantic_Visitor::visit_iden (const AST_Identifier* node){
    variable_t var =  findVariable(node->identifier);
    if(var.type == token_t::NULL_TOKEN){
        errMS("Identifier","variable ["+node->identifier+"] not found in scope");
    }

    if(isType_an_Array(var.type) && node->index_expression != nullptr){
        pushTypeStack(convert_Array_to_Type(var.type));

    }else if(!isType_an_Array(var.type) && node->index_expression != nullptr){
        errMS("Identifier",node->identifier,"Cannot assign an index to a non-array variable");

    }else if(isType_an_Array(var.type) && node->index_expression == nullptr){
        pushTypeStack(var.type, var.length);

    }else{
        pushTypeStack(var.type);
    }
}

// ----------------------------------------------------------------------------------------------- Actual Params 
void Semantic_Visitor::visit_act_params (const AST_ActualParams* node){}

// ----------------------------------------------------------------------------------------------- Function Call
void Semantic_Visitor::visit_func_call (const AST_FunctionCall* node){
    function_t func = findFunction(node->identifier);
    if(func.name == "Not Found"){
        errMS("Function Call", node->identifier, "Function Not Found");
    }else if(func.param_types.size() != node->actualparam->expression_list.size()){
        errMS("Function Call", node->identifier, "Function expects ["+ std::to_string(func.param_types.size())+"] parameters");
    }
    for(int i = 0; i < func.param_types.size(); i++){
        type_set_t t = popTypeStack();
        if(func.param_lengths[i] != t.length){
            errMS("Function Call", node->identifier, "Function Parameter ["+std::to_string(i+1)+"] expected variable length ["+std::to_string(func.param_lengths[i])+"] found length ["+std::to_string(t.length)+"]");

        }else if(func.param_types[i] != t.type){
            errMS("Function Call", node->identifier, "Function Parameter ["+std::to_string(i+1)+"] expected ["+tk_string(func.param_types[i])+"] found ["+tk_string(t.type)+"]");
        }
    }
    pushTypeStack(func.return_type, func.return_length);
}

// ----------------------------------------------------------------------------------------------- Sub Expression
void Semantic_Visitor::visit_sub_expr (const AST_SubExpression* node){}

// ----------------------------------------------------------------------------------------------- 
void Semantic_Visitor::visit_unary (const AST_Unary* node){
    token_t t = popTypeStack().type;

    if(isType_an_Array(t)){
         errMS("Unary", "Cannot Perform a Unary Operation on Arrays");
    }


    if((node->op == token_t::NOT) && (t != token_t::BOOL)){
        errMS("Unary", "'Not' must be used with a boolean expression");
    }else if((node->op == token_t::SUB) && (t == token_t::BOOL)){
        errMS("Unary", "'-' must be used with a non boolean expression");
    }
    pushTypeStack(t);
    
}

// ----------------------------------------------------------------------------------------------- 
void Semantic_Visitor::visit_random (const AST_Random* node){
    token_t t = popTypeStack().type;
    if(t != token_t::INT){
        errMS("Random", "Expect integer, found ["+tk_string(t)+"]");
    }
    pushTypeStack(token_t::INT);
}



/* =========================================================================================================================
 *   Literals
 * =========================================================================================================================
 */

// ----------------------------------------------------------------------------------------------- Literals
void Semantic_Visitor::visit_bool (const AST_Boolean* node){
    pushTypeStack(token_t::BOOL);
}

// ----------------------------------------------------------------------------------------------- Integer
void Semantic_Visitor::visit_int (const AST_Integer* node){
    pushTypeStack(token_t::INT);
}

// ----------------------------------------------------------------------------------------------- Float
void Semantic_Visitor::visit_float (const AST_Float* node){
    pushTypeStack(token_t::FLOAT);
}

// ----------------------------------------------------------------------------------------------- Colour
void Semantic_Visitor::visit_colour (const AST_Colour* node){
    pushTypeStack(token_t::COLOUR);
}

// ----------------------------------------------------------------------------------------------- Width
void Semantic_Visitor::visit_width (const AST_Width* node){
    pushTypeStack(token_t::INT);
}

// ----------------------------------------------------------------------------------------------- Height
void Semantic_Visitor::visit_height (const AST_Height* node){
    pushTypeStack(token_t::INT);    
}

// ----------------------------------------------------------------------------------------------- Read
void Semantic_Visitor::visit_read (const AST_Read* node){
    token_t typeA = popTypeStack().type;
    token_t typeB = popTypeStack().type;
    if(typeA != token_t::INT || typeB != token_t::INT){
        errMS("Read", "Read Expects 2 Integer parameters");
    }
    pushTypeStack(token_t::COLOUR);
}



/* =========================================================================================================================
 *   Operators
 * =========================================================================================================================
 */
 
// ----------------------------------------------------------------------------------------------- Relational
void Semantic_Visitor::visit_rel (const AST_Relational* node){
    token_t typeA = popTypeStack().type;
    token_t typeB = popTypeStack().type;

    // =============================== Arrays Cannnot by Copared
    if(isType_an_Array(typeA) || isType_an_Array(typeB)){
        errMS("Additive Operator", "Cannot Perform an Relational Operation on Arrays");
    }

    // =============================== Normal Relational Operation
    if          (typeA == token_t::INT && typeB == token_t::FLOAT){
        pushTypeStack(token_t::BOOL);
    }else if    (typeB == token_t::INT && typeA == token_t::FLOAT){
        pushTypeStack(token_t::BOOL);
    }else if    (typeA == typeB){
        pushTypeStack(token_t::BOOL);
    }else{
        errMS("Relational Operator", "Expected same type but found [" +tk_string(typeA)+"], [" +tk_string(typeB)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- Multiplicative
void Semantic_Visitor::visit_mult (const AST_Multiplicative* node){
    token_t typeA = popTypeStack().type;
    token_t typeB = popTypeStack().type;
    
    // =============================== Verify the boolean operators are only used with boolean operands
    if          ( (typeA == token_t::BOOL || typeB == token_t::BOOL) && node->mult_token != token_t::AND){

        errMS("Additive Operator", "Bool mult Bool","For boolean types 'and' is expected as an operator");

    }else if    (node->mult_token == token_t::AND && (typeA != token_t::BOOL || typeB != token_t::BOOL)){

        errMS("Additive Operator", "and","The 'and' operator can only be used on boolean");
    }

    // =============================== Arrays Cannnot by Multiplied
    if(isType_an_Array(typeA) || isType_an_Array(typeB)){
        errMS("Additive Operator", "Cannot Perform an Multiplicative Operation on Arrays");
    }

    // =============================== Float <-> Integer Compatibility
    if          (typeA == token_t::INT && typeB == token_t::FLOAT){
        pushTypeStack(token_t::FLOAT);
    }else if    (typeB == token_t::INT && typeA == token_t::FLOAT){
        pushTypeStack(token_t::FLOAT);

    }else if(typeA == typeB){
        if(node->mult_token == token_t::DIV){ 
            pushTypeStack(token_t::FLOAT); // division always returns a float
        } else{
            pushTypeStack(typeA);
        }
    }else{
        errMS("Multiplicity Operator", "Expected same type but found [" +tk_string(typeA)+"], [" +tk_string(typeB)+"]");
    }
}

// ----------------------------------------------------------------------------------------------- Additive
void Semantic_Visitor::visit_add (const AST_Additive* node){
    token_t typeA = popTypeStack().type;
    token_t typeB = popTypeStack().type;

    // =============================== Verify the boolean operators are only used with boolean operands
    if          ( (typeA == token_t::BOOL || typeB == token_t::BOOL) && node->add_token != token_t::OR){

        errMS("Additive Operator", "Bool mult Bool","For boolean types 'and' is expected as an operator");

    }else if    (node->add_token == token_t::OR && (typeA != token_t::BOOL || typeB != token_t::BOOL)){

        errMS("Additive Operator", "and","The 'and' operator can only be used on boolean");
    }

    // =============================== Arrays Cannnot by Added
    if(isType_an_Array(typeA) || isType_an_Array(typeB)){
        errMS("Additive Operator", "Cannot Perform an Additive Operation on Arrays");
    }

    // =============================== Float <-> Integer Compatibility
    if          (typeA == token_t::INT && typeB == token_t::FLOAT){
        pushTypeStack(token_t::FLOAT);
    }else if    (typeB == token_t::INT && typeA == token_t::FLOAT){
        pushTypeStack(token_t::FLOAT);

    }else if(typeA == typeB){
        pushTypeStack(typeA);
    }else{
        errMS("Additive Operator", "Expected same type but found [" +tk_string(typeA)+"], [" +tk_string(typeB)+"]");
    }
}