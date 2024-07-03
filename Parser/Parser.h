#ifndef PARSER_H
#define PARSER_H

#include "Abstract_Syntax_Tree/AST_Nodes.h"
#include "../Lexer/Lexer.h"
#include "../Utility/types/Generic_Types.h"
#include "../Utility/types/Tokens.h"
#include "../Utility/Utility.h"
class Parser {
public:

    Parser(std::vector<tokenised_t>& tokens);

    Program* GetASTRoot() { return &ASTroot; }

    std::unique_ptr<Program>                parseProgram            (int& index);
private:

    tokenised_t nextToken(int& index);
    tokenised_t peekToken(int index);

    
    std::unique_ptr<AST_Factor>             parseFactor                 (int& index );

    std::unique_ptr<AST_Literal>            parseLiteral                (int& index );
    std::unique_ptr<AST_Term>               parseTerm                   (int& index );
    std::unique_ptr<AST_Simple_Expr>        parseSimpleExpr             (int& index );
    std::unique_ptr<AST_Expr>               parseExpression             (int& index );

    std::unique_ptr<AST_Relational>         parseRelational             (int& index );
    std::unique_ptr<AST_Additive>           parseAdditive               (int& index );
    std::unique_ptr<AST_Multiplicative>     parseMultiplicative         (int& index );

    std::unique_ptr<AST_Statement>          parseStatement              (int& index );
    std::unique_ptr<AST_Block>              parseBlock                  (int& index );
    
    std::unique_ptr<AST_Assignment>         parseAssignment             (int& index );
    std::unique_ptr<AST_VariableDec>        parseVariableDeclaration    (int& index );
    std::unique_ptr<AST_Weak_Block>         parseWeakBlock              (int& index );

    tokenised_t verifyNext(token_t t, int& i, std::string loc                      );
    tokenised_t verifyNext(token_t t, int& i, std::string loc1, std::string loc2   );
    tokenised_t verifyType(int& i, std::string loc );
    tokenised_t verifyType(int& i, std::string loc1, std::string loc2);

    void verifyNode(AST_Node* n,    int i, std::string loc,                    std::string m);
    void verifyNode(AST_Node* n,    int i, std::string loc1, std::string loc2, std::string m);

    void errMS( std::string loc ,                   std::string mes, int i  );
    void errMS( std::string loc1, std::string loc2, std::string mes, int i  );

    std::vector<tokenised_t>& tokens;
    Program ASTroot;
    bool end_of_tokens;
};

#endif // PARSER_H
