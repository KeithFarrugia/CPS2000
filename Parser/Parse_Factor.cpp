#include "Parser.h"
/* =========================================================================================================================
 *   Parse Factor
 * =========================================================================================================================
 */
std::unique_ptr<AST_Factor> Parser::parseFactor(int& index){
    int rollback_index = index;
    std::unique_ptr<AST_Factor> factor_node;

    tokenised_t token = peekToken(index);

    switch (token.token_type){

        // ------------------------------------------------------------------------------------------ Identifier or Function Call
        case token_t::IDENTIFIER:
            {
                token = nextToken(index);
        // --------------------------------------------------------------------------------- Function Call
                if(peekToken(index).token_type == token_t::OPEN_PAR){
                    nextToken(index); // consume the next token

                    // ----------------- Set the factor node to an AST_FunctionCall
                    factor_node = std::make_unique<AST_FunctionCall>();

                    // ----------------- Create and set the Identifier
                    dynamic_cast<AST_FunctionCall*>(factor_node.get())->identifier= token.lexeme_string;

                    // ----------------- Setting Parameters
                    std::unique_ptr<AST_ActualParams> parameters = std::make_unique<AST_ActualParams>();

                    // ----------------- No Parameters
                    if(peekToken(index).token_type == token_t::CLOSE_PAR){
                        nextToken(index); // consume the next token
                        dynamic_cast<AST_FunctionCall*>(factor_node.get())->setActualParam(std::move(parameters)); 
                        return std::move(factor_node);
                    }
                    
                    // ----------------- Has Parameters
                    while(true){
                        std::unique_ptr<AST_Expr> expression = parseExpression(index);
                        verifyNode(expression.get(), index, "parseFactor", "Function Call", "Expression");

                        parameters->pushExpression(std::move(expression));

                        tokenised_t temp_token = nextToken(index);
                        if(temp_token.token_type == token_t::COMMA){
                            // nothing to do

                        }else if (temp_token.token_type == token_t::CLOSE_PAR){
                            dynamic_cast<AST_FunctionCall*>(factor_node.get())->setActualParam(std::move(parameters)); 
                            return std::move(factor_node);

                        }else{ 
                            errMS("parseFactor", "Function Call", "')' or ','", index-1);
                        }
                    }


        // --------------------------------------------------------------------------------- Identifier
                }else{
                    factor_node = std::make_unique<AST_Identifier>();
                    dynamic_cast<AST_Identifier*>(factor_node.get())->identifier = token.lexeme_string;
                    
                    if(peekToken(index).token_type == token_t::OPEN_SQUARE){
                        nextToken(index); // Consume Token
                        
                        std::unique_ptr<AST_Expr> index_expression_node = parseExpression(index);
                        verifyNode(index_expression_node.get(), index, "parseAssignment", "Expression for Index");
                        dynamic_cast<AST_Identifier*>(factor_node.get())->setExpression(std::move(index_expression_node));

                        verifyNext(token_t::CLOSE_SQUARE, index, "parseAssignment", "Index Expression");
                    }else{
                        dynamic_cast<AST_Identifier*>(factor_node.get())->setExpression(nullptr);
                    }


                    return std::move(factor_node);
                }
            }

        // --------------------------------------------------------------------------------- Sub Expression
        case token_t::OPEN_PAR:
            {
                token = nextToken(index);
                factor_node = std::make_unique<AST_SubExpression>();
                std::unique_ptr<AST_Expr> expression = parseExpression(index);

                verifyNode(expression.get(), index, "parseFactor", "Sub Expression", "Expression");

                dynamic_cast<AST_SubExpression*>(factor_node.get())->setExpression(std::move(expression));

                verifyNext(token_t::CLOSE_PAR, index,"parseFactor", "Sub Expression");

                return std::move(factor_node);
            }

        // --------------------------------------------------------------------------------- Unary
        case token_t::SUB:
        case token_t::NOT:
            {
                token = nextToken(index);
                factor_node = std::make_unique<AST_Unary>();
                std::unique_ptr<AST_Factor> fact = parseFactor(index);

                verifyNode(fact.get(), index, "parseFactor", "Unary", "Factor");

                dynamic_cast<AST_Unary*>(factor_node.get())->op = token.token_type;
                dynamic_cast<AST_Unary*>(factor_node.get())->setFactor(std::move(fact));

                return std::move(factor_node);
            }

        // --------------------------------------------------------------------------------- Random
        case token_t::RANDOM:
            {
                token = nextToken(index);
                factor_node = std::make_unique<AST_Random>();
                std::unique_ptr<AST_Expr> expression = parseExpression(index);
                
                verifyNode(expression.get(), index, "parseFactor", "Random", "Expression");

                dynamic_cast<AST_Random*>(factor_node.get())->setExpression(std::move(expression));

                return std::move(factor_node);
            }

        default:
        // --------------------------------------------------------------------------------- Literal
            index =  rollback_index;

            factor_node = parseLiteral(index);
            if(factor_node != nullptr){ return std::move(factor_node); }

            index =  rollback_index;
            factor_node.reset();
            return nullptr;
    }
}


