#include "Display_Visitor.h"


void Display_Visitor::visit_program_start (const Program* node){
    std::cout << "\n\n============================= AST TREE =============================\n\n" << "Program\n";
}
void Display_Visitor::visit_program_end (const Program* node){
    printEnding(); std::cout << "Program End" << "\n";
}

/* =========================================================================================================================
 *   Statements
 * =========================================================================================================================
 */

// ----------------------------------------------------------------------------------------------- Assignment
void Display_Visitor::visit_assignment (const AST_Assignment* node){
    printJoint();   std::cout   <<  "Assignment Node"   << "\n";
    printEnding();  std::cout   <<  node->identifier    << "\n";
}

// ----------------------------------------------------------------------------------------------- Declaration
void Display_Visitor::visit_var_dec (const AST_VariableDec* node){
    printJoint();   std::cout   <<  "Declaration Node"                      << "\n";
    printJoint();   std::cout   <<  "Variable Length: " << node->length     << "\n";
    printEnding();  std::cout   <<  node->identifier                        << "\n";
}

// ----------------------------------------------------------------------------------------------- Declaration Suffix Norm
void Display_Visitor::visit_var_dec_suf_norm (const AST_VariableDec_Suffix_Norm* node){
    printJoint();   std::cout   <<  "Declaration Suffix Norm Node"  << "\n";
    printEnding();  std::cout   <<  tk_string(node->type)  << "\n";
}

// ----------------------------------------------------------------------------------------------- Declaration Suffix Array
void Display_Visitor::visit_var_dec_suf_array (const AST_VariableDec_Suffix_Array* node){
    printJoint();   std::cout   <<  "Declaration Suffix Array Node"  << "\n";
    printEnding();  std::cout   <<  tk_string(node->type)  << "\n";
}

// ----------------------------------------------------------------------------------------------- Print
void Display_Visitor::visit_print (const AST_Print* node){
    printEnding();  std::cout   <<  "Print Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Delay
void Display_Visitor::visit_delay (const AST_Delay* node){
    printEnding();  std::cout   << "Delay Node" << "\n";
}

// ----------------------------------------------------------------------------------------------- Write Box
void Display_Visitor::visit_write_box (const AST_Write_Box* node){
    printEnding();  std::cout   <<  "Write Box Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Write
void Display_Visitor::visit_write (const AST_Write* node){
    printEnding();  std::cout   <<  "Write Node"    << "\n";
}
// ----------------------------------------------------------------------------------------------- Clear
void Display_Visitor::visit_clear (const AST_Clear* node){
    printEnding();  std::cout   <<  "Clear Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Return
void Display_Visitor::visit_return (const AST_Return* node){
    printEnding();  std::cout   <<  "Return Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Start If

void Display_Visitor::visit_start_if (const AST_If* node){
    printJoint();   std::cout   <<  "Start If Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- End If
void Display_Visitor::visit_end_if              (const AST_If*                          node){
    printJoint();   std::cout   <<  "End If Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Start Else
void Display_Visitor::visit_start_else (const AST_If* node){
    printJoint(); std::cout   <<  "Start Else Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- End Else
void Display_Visitor::visit_end_else (const AST_If* node){
    printEnding();  std::cout   <<  "End Else Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Start For
void Display_Visitor::visit_start_for (const AST_For* node){
    printJoint();   std::cout   <<  "Start For Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Jump For
void Display_Visitor::visit_jump_for (const AST_For* node){
    printJoint();   std::cout   <<  "Jump For Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Skip For
void Display_Visitor::visit_skip_for(const AST_For* node){
    printJoint();   std::cout   <<  "Skip For Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- End For
void Display_Visitor::visit_end_for (const AST_For* node){
    printEnding();  std::cout   <<  "End For Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Start While
void Display_Visitor::visit_start_while (const AST_While* node){
    printJoint();   std::cout   <<  "Start While Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Skip While
void Display_Visitor::visit_skip_while (const AST_While* node){
    printJoint();   std::cout   <<  "Skip While Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- End While
void Display_Visitor::visit_end_while (const AST_While* node){
    printEnding();  std::cout   <<  "End While Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Function Declaration Start
void Display_Visitor::visit_func_dec_start (const AST_Func_Dec* node){
    printJoint();   std::cout <<  "Function Declaration Start Node" << "\n";
    printJoint();   std::cout <<  node->identifier                  << "\n";
    printJoint();   std::cout <<  tk_string(node->type)             << "\n";
    printJoint();   std::cout <<  "Return Length: " << node->length << "\n";
}

// ----------------------------------------------------------------------------------------------- Function Declaration Skip
void Display_Visitor::visit_func_dec_skip (const AST_Func_Dec* node){
    printJoint();   std::cout <<  "Function Declaration Skip Node" << "\n";
}

// ----------------------------------------------------------------------------------------------- Function Declaration End
void Display_Visitor::visit_func_dec_end (const AST_Func_Dec* node){
    printEnding();  std::cout <<  "Function Declaration End Node" << "\n";
}

// ----------------------------------------------------------------------------------------------- Formal Parameters
void Display_Visitor::visit_form_params (const AST_Form_Params* node){
    printEnding();  std::cout   <<  "Formal Parameters Node"            << "\n";
}

// ----------------------------------------------------------------------------------------------- Formal Parameter
void Display_Visitor::visit_form_param (const AST_Form_Param* node){
    printJoint();   std::cout   <<  "Formal Parameter Node"             << "\n";
    printJoint();   std::cout   <<  node->identifier                    << "\n";
    printJoint();   std::cout   <<  "Length: " << node->length          << "\n";
    printEnding();  std::cout   <<  tk_string(node->type)               << "\n";
}

// ----------------------------------------------------------------------------------------------- Start Block

void Display_Visitor::visit_start_block (const AST_Block* node){
    printJoint();   std::cout   <<  "Start Block Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- End Block
void Display_Visitor::visit_end_block (const AST_Block* node){
    printEnding();  std::cout   <<  "End Block Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Start Weak Block

void Display_Visitor::visit_start_weak_block (const AST_Weak_Block* node){
    printJoint();   std::cout   <<  "Start Weak Block Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- End Weak Block
void Display_Visitor::visit_end_weak_block (const AST_Weak_Block* node){
    printEnding();  std::cout   <<  "End Weak Block Node"    << "\n";
}


/* =========================================================================================================================
 *   Expressions
 * =========================================================================================================================
 */
// ----------------------------------------------------------------------------------------------- Term
void Display_Visitor::visit_term (const AST_Term* node){
    printEnding();  std::cout   <<  "Term Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Simple Expression
void Display_Visitor::visit_simple_expr (const AST_Simple_Expr* node){
    printEnding();  std::cout   <<  "Simple Expression Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Expression
void Display_Visitor::visit_expr (const AST_Expr* node){
    printJoint();   std::cout   <<  "Expression Node"               << "\n";
    printEnding();  std::cout   <<  tk_string(node->forced_type)    << "\n";
}




/* =========================================================================================================================
 *   Factors
 * =========================================================================================================================
 */
// ----------------------------------------------------------------------------------------------- Identifier
void Display_Visitor::visit_iden (const AST_Identifier* node){
    printJoint();   std::cout   <<  "Identifier Node"    << "\n";
    printEnding();  std::cout   <<  node->identifier     << "\n";
}

// ----------------------------------------------------------------------------------------------- Actual Params 
void Display_Visitor::visit_act_params (const AST_ActualParams* node){
    printEnding();   std::cout   <<  "Actual Params Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Function Call
void Display_Visitor::visit_func_call (const AST_FunctionCall* node){
    printJoint();   std::cout   <<  "Function Call Node"    << "\n";
    printEnding();  std::cout   <<  node->identifier        << "\n";
}

// ----------------------------------------------------------------------------------------------- Sub Expression
void Display_Visitor::visit_sub_expr (const AST_SubExpression* node){
    printEnding();   std::cout   <<  "Sub Expression Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- 
void Display_Visitor::visit_unary (const AST_Unary* node){
    printJoint();   std::cout   <<  "Unary Node"            << "\n";
    printEnding();  std::cout   <<  tk_string(node->op)     << "\n";
}

// ----------------------------------------------------------------------------------------------- 
void Display_Visitor::visit_random (const AST_Random* node){
    printEnding();   std::cout   <<  "Random Node"    << "\n";
}



/* =========================================================================================================================
 *   Literals
 * =========================================================================================================================
 */

// ----------------------------------------------------------------------------------------------- Literals
void Display_Visitor::visit_bool (const AST_Boolean* node){
    printJoint();   std::cout   <<  "Boolean Node"                  << "\n";
    printEnding();  std::cout   <<  tk_string(node->bool_token)     << "\n";
}

// ----------------------------------------------------------------------------------------------- Integer
void Display_Visitor::visit_int (const AST_Integer* node){
    printJoint();   std::cout   <<  "Integer Node"          << "\n";
    printEnding();  std::cout   <<  node->integer_value     << "\n";
}

// ----------------------------------------------------------------------------------------------- Float
void Display_Visitor::visit_float (const AST_Float* node){
    printJoint();   std::cout   <<  "Float Node"            << "\n";
    printEnding();  std::cout   <<  node->float_value       << "\n";
}

// ----------------------------------------------------------------------------------------------- Colour
void Display_Visitor::visit_colour (const AST_Colour* node){
    printJoint();   std::cout   <<  "Colour Node"           << "\n";
    printEnding();  std::cout   <<  node->colour_value      << "\n";
}

// ----------------------------------------------------------------------------------------------- Width
void Display_Visitor::visit_width (const AST_Width* node){
    printEnding();  std::cout   <<  "Width Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Height
void Display_Visitor::visit_height (const AST_Height* node){
    printEnding();  std::cout   <<  "Height Node"    << "\n";
}

// ----------------------------------------------------------------------------------------------- Read
void Display_Visitor::visit_read (const AST_Read* node){
    printEnding();   std::cout   <<  "Read Node"    << "\n";
}



/* =========================================================================================================================
 *   Operators
 * =========================================================================================================================
 */
 
// ----------------------------------------------------------------------------------------------- Relational
void Display_Visitor::visit_rel (const AST_Relational* node){
    printJoint();   std::cout   <<  "Relational Node"                   << "\n";
    printEnding();  std::cout   <<  tk_string(node->relational_token)   << "\n";
}

// ----------------------------------------------------------------------------------------------- Multiplicative
void Display_Visitor::visit_mult (const AST_Multiplicative* node){
    printJoint();   std::cout   <<  "Multiplicative Node"           << "\n";
    printEnding();  std::cout   <<  tk_string(node->mult_token)     << "\n";
}

// ----------------------------------------------------------------------------------------------- Additive
void Display_Visitor::visit_add (const AST_Additive* node){
    printJoint();   std::cout   <<  "Additive Node"                 << "\n";
    printEnding();  std::cout   <<  tk_string(node->add_token)      << "\n";
}