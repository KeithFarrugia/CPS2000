#include "AST_Nodes.h"

/* =========================================================================================================================
 * ------------------------------ Boolean Litteral
 * Traversal:
 *  - Boolean
 */
void AST_Boolean::accept(AST_Visitor& visitor){
    // ----------------------- Boolean
    visitor.visit_bool(this);
}



/* =========================================================================================================================
 * ------------------------------ Integer Litteral
 * Traversal:
 *  - Integer
 */
void AST_Integer::accept(AST_Visitor& visitor){
    // ----------------------- Integer
    visitor.visit_int(this);
}




/* =========================================================================================================================
 * ------------------------------ Float Litteral
 * Traversal:
 *  - Float
 */
void AST_Float::accept(AST_Visitor& visitor){
    // ----------------------- Float
    visitor.visit_float(this);
}



/* =========================================================================================================================
 * ------------------------------ Colour Litteral
 * Traversal:
 *  - Colour
 */
void AST_Colour::accept(AST_Visitor& visitor){
    // ----------------------- Colour
    visitor.visit_colour(this);
}



/* =========================================================================================================================
 * ------------------------------ Width litteral
 * Traversal:
 *  - Width
 */
void AST_Width::accept(AST_Visitor& visitor){
    // ----------------------- Width
    visitor.visit_width(this);
}



/* =========================================================================================================================
 * ------------------------------ Height Litteral
 * Traversal:
 *  - Height
 */
void AST_Height::accept(AST_Visitor& visitor){
    // ----------------------- Height
    visitor.visit_height(this);
}



/* =========================================================================================================================
 * ------------------------------ Read Litteral
 * Traversal:
 *  - Expression 1
 *  - Expression 2
 *  - Read
 */
void AST_Read::accept(AST_Visitor& visitor){
    // ----------------------- Expression 1
    visitor.inc_tab();
    expression1->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Expression 2
    visitor.inc_tab();
    expression2->accept(visitor);
    visitor.dec_tab();

    // ----------------------- Read
    visitor.visit_read(this);
}

void AST_Read::setExpression1   ( std::unique_ptr<AST_Expr> expression ) { expression1 = std::move(expression); }
void AST_Read::setExpression2   ( std::unique_ptr<AST_Expr> expression ) { expression2 = std::move(expression); }