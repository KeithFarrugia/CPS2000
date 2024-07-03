#include "AST_Nodes.h"



/* =========================================================================================================================
 * ------------------------------ Variable Assignement Statement
 * Traversal:
 *  - Expresion
 *  - Array Index Expression
 *  - Assignment
 */
void AST_Assignment::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Array Index Expression
    if(array_index_expression != nullptr){
        visitor.inc_tab();
        array_index_expression->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Assignment
    visitor.visit_assignment(this);
}

void AST_Assignment::setExpr    ( std::unique_ptr<AST_Expr> exp        ) { expression               = std::move(exp)        ;}
void AST_Assignment::setExprI   ( std::unique_ptr<AST_Expr> exp_inde   ) { array_index_expression   = std::move(exp_inde)   ;}



/* =========================================================================================================================
 * ------------------------------ Variable Declaration Statement
 * Traversal:
 *  - Declaration Suffix
 *  - Declaration
 */

void AST_VariableDec::accept(AST_Visitor& visitor){
    // ----------------------- Declaration Suffix
    visitor.inc_tab();
    dec_suffix->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Declaration
    visitor.visit_var_dec(this);
}

void AST_VariableDec::setSuffix ( std::unique_ptr<AST_VariableDec_Suffix> suf ) { dec_suffix = std::move(suf)     ;}

/* ------------------------------ Variable Declaration Suffix (Not Array)
 * Traversal:
 *  - Expresion
 *  - Suffix
 */
void AST_VariableDec_Suffix_Norm::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Expression
    visitor.visit_var_dec_suf_norm(this);
}

void AST_VariableDec_Suffix_Norm::setExpr ( std::unique_ptr<AST_Expr> exp ) { expression = std::move(exp); }

/* ------------------------------ Variable Declaration Suffix (Array)
 * Traversal:
 *  - Expresion
 *  - Suffix
 */
void AST_VariableDec_Suffix_Array::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    for (int i = literal_list.size() - 1; i >= 0; i--) {
        visitor.inc_tab();
        literal_list[i]->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Expression
    visitor.visit_var_dec_suf_array(this);
}

void AST_VariableDec_Suffix_Array::pushLiteral ( std::unique_ptr<AST_Literal> lit ) { literal_list.push_back(std::move(lit)); }





/* =========================================================================================================================
 * ------------------------------ Print Statement
 * Traversal:
 *  - Expresion
 *  - Print
 */
void AST_Print::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Print
    visitor.visit_print(this);
}

void AST_Print::setExpr     ( std::unique_ptr<AST_Expr> exp ) { expression = std::move(exp); }



/* =========================================================================================================================
 * ------------------------------ Delay Statement
 * Traversal:
 *  - Expresion
 *  - Delay
 */
void AST_Delay::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Delay
    visitor.visit_delay(this);
}

void AST_Delay::setExpr     ( std::unique_ptr<AST_Expr> exp ) { expression = std::move(exp); }



/* =========================================================================================================================
 * ------------------------------ Write Box Statement
 * Traversal:
 *  - Expresion 5
 *  - Expresion 4
 *  - Expresion 3
 *  - Expresion 2
 *  - Expresion 1
 *  - Write Box
 */
void AST_Write_Box::accept(AST_Visitor& visitor){
    // ----------------------- Expression 5
    visitor.inc_tab();
    expression5->accept(visitor);
    visitor.dec_tab();
    
    // ----------------------- Expression 4
    visitor.inc_tab();
    expression4->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Expression 3
    visitor.inc_tab();
    expression3->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Expression 2
    visitor.inc_tab();
    expression2->accept(visitor);
    visitor.dec_tab();
    
    // ----------------------- Expression 1
    visitor.inc_tab();
    expression1->accept(visitor);
    visitor.dec_tab();
    

    // ----------------------- Write Box
    visitor.visit_write_box(this);
}

void AST_Write_Box::setExpr1    ( std::unique_ptr<AST_Expr> exp ) { expression1 = std::move(exp); }
void AST_Write_Box::setExpr2    ( std::unique_ptr<AST_Expr> exp ) { expression2 = std::move(exp); }
void AST_Write_Box::setExpr3    ( std::unique_ptr<AST_Expr> exp ) { expression3 = std::move(exp); }
void AST_Write_Box::setExpr4    ( std::unique_ptr<AST_Expr> exp ) { expression4 = std::move(exp); }
void AST_Write_Box::setExpr5    ( std::unique_ptr<AST_Expr> exp ) { expression5 = std::move(exp); }



/* =========================================================================================================================
 * ------------------------------ Write (Normal) Statement
 * Traversal:
 *  - Expresion 3
 *  - Expresion 2
 *  - Expresion 1
 *  - Write
 */
void AST_Write::accept(AST_Visitor& visitor){
    
    // ----------------------- Expression 3
    visitor.inc_tab();
    expression3->accept(visitor);
    visitor.dec_tab();
    
    // ----------------------- Expression 2
    visitor.inc_tab();
    expression2->accept(visitor);
    visitor.dec_tab();
    
    // ----------------------- Expression 1
    visitor.inc_tab();
    expression1->accept(visitor);
    visitor.dec_tab();
    
    // ----------------------- Write
    visitor.visit_write(this);
}

void AST_Write::setExpr1    ( std::unique_ptr<AST_Expr> exp ) { expression1 = std::move(exp); }
void AST_Write::setExpr2    ( std::unique_ptr<AST_Expr> exp ) { expression2 = std::move(exp); }
void AST_Write::setExpr3    ( std::unique_ptr<AST_Expr> exp ) { expression3 = std::move(exp); }

/* =========================================================================================================================
 * ------------------------------ Clear Statement
 * Traversal:
 *  - Expresion
 *  - Clear
 */
void AST_Clear::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Delay
    visitor.visit_clear(this);
}

void AST_Clear::setExpr     ( std::unique_ptr<AST_Expr> exp ) { expression = std::move(exp); }



/* =========================================================================================================================
 * ------------------------------ Return Statement
 * Traversal:
 *  - Expresion
 *  - Return
 */
void AST_Return::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Return
    visitor.visit_return(this);
}

void AST_Return::setExpr    ( std::unique_ptr<AST_Expr> exp ) { expression = std::move(exp); }



/* =========================================================================================================================
 * ------------------------------ If/Else Statement
 * Traversal:
 *  - Expresion
 *  - Start If
 *  - Block 1 (If Block)
 * 
 *  - Start Else
 *  - Block 2 (Else Block)
 *  - End Else 
 * 
 *  - End If
 */
void AST_If::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Start If
    visitor.visit_start_if(this);

    // ----------------------- Block 1
    visitor.inc_tab();
    block1->accept(visitor);
    visitor.dec_tab();

    // ----------------------- End If
    visitor.visit_end_if(this);


    if(block2 != nullptr){
        // ----------------------- Start Else
        visitor.visit_start_else(this);

        // ----------------------- Block 2
        visitor.inc_tab();
        block2->accept(visitor);
        visitor.dec_tab();

        // ----------------------- End Else
        visitor.visit_end_else(this);
    }
}

void AST_If::setExpr    ( std::unique_ptr<AST_Expr>     exp ) { expression  = std::move(exp);   }
void AST_If::setBlock1  ( std::unique_ptr<AST_Block>    b   ) { block1      = std::move(b);     }
void AST_If::setBlock2  ( std::unique_ptr<AST_Block>    b   ) { block2      = std::move(b);     }



/* =========================================================================================================================
 * ------------------------------ For Loop Statement
 * Traversal:
 *  - Start For                 (to start for-loop context)
 *  - Declaration
 *  
 *  - For Jump                  (to store start of jump condition for looping)
 *  - Expresion
 *  - For Skip                  (to allow for skipping the block statement when loop is over)
 * 
 *  - Block
 *  - Assignment
 * 
 *  - End For                   (Updated the previouse jump statements and add a jump statement for the loop)
 */
void AST_For::accept(AST_Visitor& visitor){
    // ----------------------- Start For
    visitor.visit_start_for(this);
    
    // ----------------------- Variable Declaration
    if(var_dec != nullptr){
        visitor.inc_tab();
        var_dec->accept(visitor);
        visitor.dec_tab();
    }
    
    // ----------------------- For Jump
    visitor.visit_jump_for(this);

    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- For Skip
    visitor.visit_skip_for(this);

    // ----------------------- Block
    visitor.inc_tab();
    block->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Assignment
    if(var_assign != nullptr){
        visitor.inc_tab();
        var_assign->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- End For
    visitor.visit_end_for(this);
}

void AST_For::setVarAssign  ( std::unique_ptr<AST_Assignment>   assign  ) { var_assign  = std::move(assign); }
void AST_For::setExpr       ( std::unique_ptr<AST_Expr>         exp     ) { expression  = std::move(exp);    }
void AST_For::setVarDec     ( std::unique_ptr<AST_VariableDec>  dec     ) { var_dec     = std::move(dec);    }
void AST_For::setBlock      ( std::unique_ptr<AST_Block>        b       ) { block       = std::move(b);      }



/* =========================================================================================================================
 * ------------------------------ While Loop Statement
 * Traversal:
 *  - Start While               (to store)
 *  - Expresion
 *  - While Skip                (to allow for skipping the block statement when loop is over)
 * 
 *  - Block
 * 
 *  - End While                  (Updated the previouse jump statements and add a jump statement for the loop)
 */
void AST_While::accept(AST_Visitor& visitor){
    // ----------------------- Start While
    visitor.visit_start_while(this);

    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- While Skip
    visitor.visit_skip_while(this);

    // ----------------------- Block
    visitor.inc_tab();
    block->accept(visitor);
    visitor.dec_tab();
    
    // ----------------------- End While
    visitor.visit_end_while(this);
}

void AST_While::setExpr     ( std::unique_ptr<AST_Expr>     exp ) { expression  = std::move(exp);   }
void AST_While::setBlock    ( std::unique_ptr<AST_Block>    b   ) { block       = std::move(b);     }



/* =========================================================================================================================
 * ------------------------------ Function Declaration Statement
 * Traversal:
 *  - Start Function                (Starts Scope)
 *  - Params
 *  - Skip Function Block           (For storing Block instruction Position and storeing the function scope in parent symbol table)
 *  - Bloc
 *  - End Function Declaration      (For Ending the Scope and updating jumps)
 */
void AST_Func_Dec::accept(AST_Visitor& visitor){

    // ----------------------- Start Function
    visitor.visit_func_dec_start(this);

    // ----------------------- Parameter Declaration
    if(params != nullptr){
        visitor.inc_tab();
        params->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Function Skip
    visitor.visit_func_dec_skip(this);

    // ----------------------- Block
    visitor.inc_tab();
    weakblock->accept(visitor);
    visitor.dec_tab();

    // ----------------------- End Function Declaration
    visitor.visit_func_dec_end(this);
}
void AST_Func_Dec::setParams    ( std::unique_ptr<AST_Form_Params>  par     ) { params      = std::move(par);   }
void AST_Func_Dec::setWeakBlock ( std::unique_ptr<AST_Weak_Block>   b       ) { weakblock   = std::move(b);     }



/* =========================================================================================================================
 * ------------------------------ Parameters
 * Traversal:
 *  - Param                     (the list of parameters)
 *  - Params                    (set of parameters)
 */
void AST_Form_Params::accept(AST_Visitor& visitor){

    // ----------------------- Param 
    
    for (std::unique_ptr<AST_Form_Param>& par : params) {
        visitor.inc_tab();
        par->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Params 
    visitor.visit_form_params(this);
}

void AST_Form_Params::pushParam ( std::unique_ptr<AST_Form_Param>   par ) { params.push_back(std::move(par)); }



/* =========================================================================================================================
 * ------------------------------ Parameter
 * Traversal:
 *  - Param
 */
void AST_Form_Param::accept(AST_Visitor& visitor){
    // ----------------------- Param
    visitor.visit_form_param(this);
}



/* =========================================================================================================================
 * ------------------------------ Block
 * Traversal:
 *  - Start Block
 *  - Statements
 *  - End Block
 */
void AST_Block::accept(AST_Visitor& visitor){
    // ----------------------- Start Block
    visitor.visit_start_block(this);

    // ----------------------- Statements
    
    for (std::unique_ptr<AST_Statement>& statement : statementlist) {
        visitor.inc_tab();
        statement->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- End Block
    visitor.visit_end_block(this);
}

void AST_Block::pushStatement   ( std::unique_ptr<AST_Statement> statement ) { statementlist.push_back(std::move(statement)); }



/* =========================================================================================================================
 * ------------------------------ Weak Block
 * Traversal:
 *  - Start Weak Block
 *  - Statements
 *  - End Weak Block
 */
void AST_Weak_Block::accept(AST_Visitor& visitor){
    // ----------------------- Start Block
    visitor.visit_start_weak_block(this);

    // ----------------------- Statements
    
    for (std::unique_ptr<AST_Statement>& statement : statementlist) {
        visitor.inc_tab();
        statement->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- End Block
    visitor.visit_end_weak_block(this);
}

void AST_Weak_Block::pushStatement   ( std::unique_ptr<AST_Statement> statement ) { statementlist.push_back(std::move(statement)); }