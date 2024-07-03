#include "AST_Nodes.h"

/* =========================================================================================================================
 * ------------------------------ Identifier
 * Traversal:
 *  - Index Expression List (if array index)
 *  - Identifier
 */
void AST_Identifier::accept (AST_Visitor& visitor){ 
    if(index_expression != nullptr){
        visitor.inc_tab();
        index_expression->accept(visitor);
        visitor.dec_tab();
    }

    visitor.visit_iden(this);
}


void AST_Identifier::setExpression   ( std::unique_ptr<AST_Expr> expr ) { index_expression = std::move(expr); }

/* =========================================================================================================================
 * ------------------------------ Actual Parameters
 * Traversal:
 *  - Expressions
 *  - Actual Params (reverse order)
 */
void AST_ActualParams::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    for (int i = expression_list.size() - 1; i >= 0; --i){
        visitor.inc_tab();
        expression_list[i]->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Actual Params
    visitor.visit_act_params(this);
}

void AST_ActualParams::pushExpression   ( std::unique_ptr<AST_Expr> expression ) { expression_list.push_back(std::move(expression)); }



/* =========================================================================================================================
 * ------------------------------ Function Call
 * Traversal:
 *  - Actual Params
 *  - Function Call
 */
void AST_FunctionCall::accept(AST_Visitor& visitor){
    // ----------------------- Actual Params
    visitor.inc_tab();
    actualparam->accept(visitor);
    visitor.dec_tab();
    
    // ----------------------- Function Call
    visitor.visit_func_call(this);
}
void  AST_FunctionCall::setActualParam  ( std::unique_ptr<AST_ActualParams>     param   ) { actualparam = std::move(param);         }



/* =========================================================================================================================
 * ------------------------------ Sub Expression
 * Traversal:
 *  - Expression
 *  - Sub Expression
 */
void AST_SubExpression::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Sub Expression
    visitor.visit_sub_expr(this);
}

void AST_SubExpression::setExpression   ( std::unique_ptr<AST_Expr>     expr ) { expression = std::move(expr); } 



/* =========================================================================================================================
 * ------------------------------ Unary
 * Traversal:
 *  - Factor
 *  - Unary
 */
void AST_Unary::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    factor->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Unary
    visitor.visit_unary(this);
    
}

void AST_Unary::setFactor   ( std::unique_ptr<AST_Factor>     fact ) { factor = std::move(fact); }


/* =========================================================================================================================
 * ------------------------------ Random
 * Traversal:
 *  - Expression
 *  - Random
 */
void AST_Random::accept(AST_Visitor& visitor){
    // ----------------------- Expression
    visitor.inc_tab();
    expression->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Random
    visitor.visit_random(this);
}

void AST_Random::setExpression  ( std::unique_ptr<AST_Expr> expr ) { expression = std::move(expr); }