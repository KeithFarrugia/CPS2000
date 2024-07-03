#include "AST_Nodes.h"

/* =========================================================================================================================
 * ------------------------------ Term
 * Traversal:
 *  - Factors (reverse)
 *  - Multiplication Operators (in order)
 *  - Term
 * 
 * This is because fi we take 2-1+5
 *  - We would want the stack to be [5, 1, 2]
 *  - And first the - operator [5, 1]
 *  - Then the + operator [6]
 * 
 */
void AST_Term::accept(AST_Visitor& visitor){
    // ----------------------- Factor
    for (int i = factor_list.size() - 1; i >= 0; --i){
        visitor.inc_tab();
        factor_list[i]->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Mult Operator
    for(int i = 0; i<  mult_list.size(); i++){
        visitor.inc_tab();
        mult_list[i]->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Term
    visitor.visit_term(this);
}
void AST_Term::pushFactor   ( std::unique_ptr<AST_Factor>            factor  ) { factor_list.push_back(std::move(factor));   }
void AST_Term::pushMult     ( std::unique_ptr<AST_Multiplicative>    mult    ) { mult_list.push_back(std::move(mult));       }



/* =========================================================================================================================
 * ------------------------------ Simple Expression
 * Traversal:
 *  - Term
 * 
 *  - Term
 *  - Addative Operator
 *  - Repeat
 * 
 *  - Simple Expression
 */
void AST_Simple_Expr::accept(AST_Visitor& visitor){
    // ----------------------- Term
    for (int i = term_list.size() - 1; i >= 0; --i){
        visitor.inc_tab();
        term_list[i]->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Additive
    for(int i = 0; i<  add_list.size(); i++){
        visitor.inc_tab();
        add_list[i]->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Factor
    visitor.visit_simple_expr(this);
}

void AST_Simple_Expr::pushTerm      ( std::unique_ptr<AST_Term>      term    ) { term_list.push_back(std::move(term));   }
void AST_Simple_Expr::pushAdd       ( std::unique_ptr<AST_Additive>  add     ) { add_list.push_back(std::move(add));     }



/* =========================================================================================================================
 * ------------------------------ Expression
 * Traversal:
 *  - Simple Expression
 * 
 *  - Simple Expression
 *  - Relational Operator
 *  - Repeat
 * 
 *  - Expression
 */
void AST_Expr::accept(AST_Visitor& visitor){
    // ----------------------- Simple Expression
    for (int i = simple_expr_list.size() - 1; i >= 0; --i){
        visitor.inc_tab();
        simple_expr_list[i]->accept(visitor);
        visitor.dec_tab();
    }

    // ----------------------- Relational Operator
    for(int i = 0; i<rel_list.size(); i++){
        visitor.inc_tab();
        rel_list[i]->accept(visitor);
        visitor.dec_tab();
    }
    
    // ----------------------- Expression
    visitor.visit_expr(this);
}

void AST_Expr::pushSimpleExpr   ( std::unique_ptr<AST_Simple_Expr>  sim_expr    ) { simple_expr_list.push_back(std::move(sim_expr));    }
void AST_Expr::pushRel          ( std::unique_ptr<AST_Relational>    rel        ) { rel_list.push_back(std::move(rel));                 }