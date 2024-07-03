#include "AST_Nodes.h"

/* =========================================================================================================================
 * ------------------------------ Relational Operator
 * Traversal:
 *  - Relational
 */
void AST_Relational::accept(AST_Visitor& visitor){
    // ----------------------- Relational
    visitor.visit_rel(this);
}



/* =========================================================================================================================
 * ------------------------------ Multiplicative Operator
 * Traversal:
 *  - Multiplicative
 */
void AST_Multiplicative::accept(AST_Visitor& visitor){
    // ----------------------- Multiplicative
    visitor.visit_mult(this);
}



/* =========================================================================================================================
 * ------------------------------ Additive Operator
 * Traversal:
 *  - Additive
 */
void AST_Additive::accept(AST_Visitor& visitor){
    // ----------------------- Additive
    visitor.visit_add(this);
}