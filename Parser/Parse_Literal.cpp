#include "Parser.h"

/* =========================================================================================================================
 *   Parse Literal
 * =========================================================================================================================
 */
std::unique_ptr<AST_Literal> Parser::parseLiteral(int& index){
    int rollback_index = index;
    std::unique_ptr<AST_Literal> literal_node;

    
    tokenised_t token = nextToken(index);

    switch (token.token_type){

        // ------------------------------- Boolean 
        case token_t::TRUE  :
        case token_t::FALSE :
            literal_node = std::make_unique<AST_Boolean>();
            dynamic_cast<AST_Boolean*>(literal_node.get())->bool_token = token.token_type;
            return std::move(literal_node);

        // ------------------------------- Integer
        case token_t::INTEGER:
            literal_node = std::make_unique<AST_Integer>();
            dynamic_cast<AST_Integer*>( literal_node.get() )->integer_value = token.lexeme_string;
            return std::move(literal_node);

        // ------------------------------- Floating Point Number
        case token_t::FLOATING_POINT :
            literal_node = std::make_unique<AST_Float>();
            dynamic_cast<AST_Float*>( literal_node.get() )->float_value = token.lexeme_string;
            return std::move(literal_node);

        // ------------------------------- Colour Literal
        case token_t::COLOUR_LITERAL :
            literal_node = std::make_unique<AST_Colour>();
            dynamic_cast<AST_Colour*>( literal_node.get() )->colour_value = token.lexeme_string;
            return std::move(literal_node);

        // ------------------------------- Width
        case token_t::WIDTH :
            literal_node = std::make_unique<AST_Width>();
            return std::move(literal_node);

        // ------------------------------- Height
        case token_t::HEIGHT :
            literal_node = std::make_unique<AST_Height>();
            return std::move(literal_node);
        
        // ------------------------------- Read
        case token_t::READ : 
            {
                literal_node = std::make_unique<AST_Read>();
                std::unique_ptr<AST_Expr> exp1 = parseExpression(index);
                verifyNode(exp1.get(), index, "parseLiteral", "Read", "Two Expressions");

                verifyNext(token_t::COMMA, index, "parseLiteral", "Read");

                std::unique_ptr<AST_Expr> exp2 = parseExpression(index);
                verifyNode(exp1.get(), index, "parseLiteral", "Read", "Two Expressions");

                // ------------------------------- Valid Expressions
                dynamic_cast<AST_Read*>( literal_node.get() )->setExpression1(std::move(exp1));
                dynamic_cast<AST_Read*>( literal_node.get() )->setExpression2(std::move(exp2));
                return std::move(literal_node);
            }
        default:
            index = rollback_index;
            literal_node.reset();
            return nullptr;
    }
}