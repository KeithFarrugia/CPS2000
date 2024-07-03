#include "Parser.h"

/* =========================================================================================================================
 *   Parse Relational
 * =========================================================================================================================
 */
std::unique_ptr<AST_Relational> Parser::parseRelational (int& index){
    int rollback_index = index;
    std::unique_ptr<AST_Relational> relational_node;

    tokenised_t token = nextToken(index);

    switch (token.token_type){
        case token_t::GREATER_THAN:
        case token_t::LESS_THAN:
        case token_t::EQUAL_TO:
        case token_t::NOT_EQUAL:
        case token_t::GREATER_THAN_EQUAL:
        case token_t::LESS_THAN_EQUAL:
            relational_node = std::make_unique<AST_Relational>();
            relational_node->relational_token = token.token_type;
            return std::move(relational_node);
        default:
            relational_node.reset();
            index = rollback_index;
            return nullptr;
    }
}

/* =========================================================================================================================
 *   Parse Additive
 * =========================================================================================================================
 */
std::unique_ptr<AST_Additive> Parser::parseAdditive (int& index){
    int rollback_index = index;
    std::unique_ptr<AST_Additive> additive_node;

    tokenised_t token = nextToken(index);

    switch (token.token_type){
        case token_t::ADD:
        case token_t::SUB:
        case token_t::OR:
            additive_node = std::make_unique<AST_Additive>();
            additive_node->add_token = token.token_type;
            return std::move(additive_node);
        default:
            additive_node.reset();
            index = rollback_index;
            return nullptr;
    }
}

/* =========================================================================================================================
 *   Parse Multiplicative
 * =========================================================================================================================
 */
std::unique_ptr<AST_Multiplicative> Parser::parseMultiplicative (int& index){
    int rollback_index = index;
    std::unique_ptr<AST_Multiplicative> multiplicative_node;

    tokenised_t token = nextToken(index);

    switch (token.token_type){
        case token_t::MULT:
        case token_t::DIV:
        case token_t::AND:
            multiplicative_node = std::make_unique<AST_Multiplicative>();
            multiplicative_node->mult_token = token.token_type;
            return std::move(multiplicative_node);
        default:
            multiplicative_node.reset();
            index = rollback_index;
            return nullptr;
    }
}
