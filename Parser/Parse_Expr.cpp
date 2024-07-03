#include "Parser.h"


/* =========================================================================================================================
 * -------------------- Parse Term
 * 〈Factor〉 { 〈MultiplicativeOp〉 〈Factor〉 }
 * =========================================================================================================================
 */
std::unique_ptr<AST_Term> Parser::parseTerm(int& index){
    int rollback_index = index;
    std::unique_ptr<AST_Term> term_node = std::make_unique<AST_Term>();
    std::unique_ptr<AST_Factor> factor_node = parseFactor(index);

    // ---------------------------------------- A Term must have at least 1 Factor
    if(factor_node == nullptr){
        term_node.reset();
        factor_node.reset();
        index = rollback_index;
        return nullptr;
        
    // ---------------------------------------- Parse {<Multiplicative> <Factor>}
    }else{
        term_node->pushFactor(std::move(factor_node));
        while(true){

            rollback_index = index;
            std::unique_ptr<AST_Multiplicative> mult_node = parseMultiplicative(index);

            // ---------------------------------------- No More Factors
            if(mult_node == nullptr){
                mult_node.reset();
                index = rollback_index;
                return std::move(term_node);
            }
            
            // ---------------------------------------- More Factors
            term_node->pushMult(std::move(mult_node));
            factor_node = parseFactor(index);

            verifyNode(factor_node.get(), index, "parseTerm", "Factor");

            term_node->pushFactor(std::move(factor_node));
        }
    }
}



/* =========================================================================================================================
 * -------------------- Parse Simple Expression
 *〈Term〉 { 〈AdditiveOp〉 〈Term〉 }
 * =========================================================================================================================
 */
std::unique_ptr<AST_Simple_Expr> Parser::parseSimpleExpr(int& index){
    int rollback_index = index;
    std::unique_ptr<AST_Simple_Expr> simple_expr_node = std::make_unique<AST_Simple_Expr>();
    std::unique_ptr<AST_Term> term_node = parseTerm(index);

    
    // ---------------------------------------- A Simple Expression must have at least 1 Term
    if(term_node == nullptr){
        term_node.reset();
        simple_expr_node.reset();
        index = rollback_index;
        return nullptr;

    
    }else{
        
    // ---------------------------------------- Parse {<Additive> <Term>}
        simple_expr_node->pushTerm(std::move(term_node));
        while(true){

            rollback_index = index;
            std::unique_ptr<AST_Additive> add_node = parseAdditive(index);

            // ---------------------------------------- No More Terms
            if(add_node == nullptr){
                add_node.reset();
                index = rollback_index;
                return std::move(simple_expr_node);
            }

            
            // ---------------------------------------- More Terms
            simple_expr_node->pushAdd(std::move(add_node));
            term_node = parseTerm(index);

            verifyNode(term_node.get(), index, "parseSimpleExpr", "Term");
            
            simple_expr_node->pushTerm(std::move(term_node));
        }
    }
}


/* =========================================================================================================================
 * -------------------- Parse Expression
 *〈SimpleExpr〉 { 〈RelationalOp〉 〈SimpleExpr〉 }    [ ‘as’ 〈Type〉 ]
 * =========================================================================================================================
 */
std::unique_ptr<AST_Expr> Parser::parseExpression(int& index){
    int rollback_index = index;
    std::unique_ptr<AST_Expr> expr_node = std::make_unique<AST_Expr>();
    std::unique_ptr<AST_Simple_Expr> simple_expr_node = parseSimpleExpr(index);

    // ---------------------------------------- An Expression must have at least 1 Simple Expression
    if(simple_expr_node == nullptr){
        simple_expr_node.reset();
        expr_node.reset();
        index = rollback_index;
        return nullptr;


    }else{
        
    // ---------------------------------------- Parse {<Relational> <Simple Expression>}
        expr_node->pushSimpleExpr(std::move(simple_expr_node));
        while(true){

            rollback_index = index;
            std::unique_ptr<AST_Relational> relational_node = parseRelational(index);

            // ---------------------------------------- No More Simple Expressions
            if(relational_node == nullptr){
                relational_node.reset();
                index = rollback_index;

                // --------------------- Check for " 'as' <Type> "
                rollback_index = index;
                tokenised_t token_temp = nextToken(index);

                // --------------------- Check for 'as'
                if(token_temp.token_type == token_t::AS){
                    // --------------------- Must be followed by a type
                    token_temp = verifyType(index, "parseExpression");
                    expr_node->forced_type = token_temp.token_type;

                }else{
                    expr_node->forced_type = token_t::NULL_TOKEN;
                    index = rollback_index;
                }

                return std::move(expr_node);
            }

            
            // ---------------------------------------- More Simple Expressions
            expr_node->pushRel(std::move(relational_node));
            simple_expr_node = parseSimpleExpr(index);

            verifyNode(simple_expr_node.get(), index, "parseExpression", "Simple Expression");
            
            expr_node->pushSimpleExpr(std::move(simple_expr_node));
        }
    }
}

