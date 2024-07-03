#include "Parser.h"

Parser::Parser(std::vector<tokenised_t>& tokens) : tokens(tokens){

}

/* =========================================================================================================================
 * -------------------- Token Reading
 * 
 * nextToken -> returns the next tokenised "lexeme string" and increments the index
 * 
 * peakToken -> returns the next tokenised "lexeme string" and does NOT increment the index
 * =========================================================================================================================
 */

// ------------------------------------------------------------ Next Token
tokenised_t Parser::nextToken(int& index) {
    tokenised_t current_token;

    do{
        if(index < tokens.size()){
            current_token = tokens[index];
            index++;
        }else{ return tokenised_t(token_t::NULL_TOKEN, "END"); }

    }while (current_token.token_type == token_t::WHITESPACE);

    return current_token;
}

// ------------------------------------------------------------ Peek Token
tokenised_t Parser::peekToken(int index) {
    tokenised_t current_token;

    do{
        if(index < tokens.size()){
            current_token = tokens[index];
            index++;
        }else{ return tokenised_t(token_t::NULL_TOKEN, "END"); }

    }while (current_token.token_type == token_t::WHITESPACE);

    return current_token;
}


/* =========================================================================================================================
 * -------------------- Parse Program
 * This is the function that starts the parsing of the program and the one that initializes
 * the Abstract Syntax Tree
 * =========================================================================================================================
 */
std::unique_ptr<Program> Parser::parseProgram(int& index) {
    std::unique_ptr<Program> program = std::make_unique<Program>();
    while (index < tokens.size()) {

        std::unique_ptr<AST_Statement> statement = parseStatement(index);

        if (statement != nullptr) {
            program->pushStatement(std::move(statement));
        } else if (nextToken(index).token_type != token_t::NULL_TOKEN){
            throwErr("Error [Parser : parseProgram] : None Statement found\n");
            program.reset();
            return nullptr;
        }
    }

    return std::move(program);
}





/* =========================================================================================================================
 * -------------------- Verification of Next Token
 * This function is used whenever during parsing there is a situation where the next token needs to be known but
 * not needed in the creation of the tree.
 * 
 * for example during the parsing of a function call such as doSomthing();
 * the identifier needs to be followed by a '(' but this is not really needed after or during the AST node creation
 * 
 * That being said they do return the next token for a wider coverage of use cases
 * 
 * loc1, loc2 and loc respectivly are used to print the error message if the next token is not what was expected
 * 
 * =========================================================================================================================
 */
tokenised_t Parser::verifyNext(token_t t, int& i, std::string loc){
    tokenised_t next = nextToken(i);
    if( next.token_type != t ){
        errMS   (   loc, 
                    "'" + tk_string(t) + "'",
                    i-1
                );
    }
    return next;
}
tokenised_t Parser::verifyNext(token_t t, int& i, std::string loc1, std::string loc2){
    tokenised_t next = nextToken(i);
    if( next.token_type != t ){
        errMS   (   loc1,
                    loc2, 
                    "'" + tk_string(t) + "'",
                    i-1
                );
    }
    return next;
}

/* =========================================================================================================================
 * -------------------- Verification of Next Token Is type
 * This function is used whenever during parsing there is a situation where the next token needs to be a type
 * They return the found type as well
 * 
 * loc1, loc2 and loc respectivly are used to print the error message if the next token is not what was expected
 * 
 * =========================================================================================================================
 */
tokenised_t Parser::verifyType(int& i, std::string loc){
    tokenised_t next = nextToken(i);
    if( !isToken_a_Type(next.token_type) ){
        errMS   (   loc, 
                    "type",
                    i-1
                );
    }
    return next;
}

tokenised_t Parser::verifyType(int& i, std::string loc1, std::string loc2){
    tokenised_t next = nextToken(i);
    if( !isToken_a_Type(next.token_type) ){
        errMS   (   loc1,
                    loc2, 
                    "type",
                    i-1
                );
    }
    return next;
}

/* =========================================================================================================================
 * -------------------- Verification of Next Node
 * This function is used whenever during parsing there is a situation where the next token needs to be known but
 * not needed in the creation of the tree.
 * 
 * for example during the parsing of a function call such as doSomthing();
 * the identifier needs to be followed by a '(' but this is not really needed after or during the AST node creation
 * 
 * loc1, loc2 and loc respectivly are used to print the error message if the next token is not what was expected
 * =========================================================================================================================
 */
void Parser::verifyNode(AST_Node* n, int i, std::string loc, std::string m){
    if( n == nullptr){
        errMS   (   loc, 
                    m,
                    i
                );
    }
}
void Parser::verifyNode(AST_Node* n, int i, std::string loc1, std::string loc2, std::string m){
    if( n == nullptr){
        errMS   (   loc1,
                    loc2, 
                    m,
                    i
                );
    }
}
/* =========================================================================================================================
 * -------------------- Error Handling
 * This function prints an error message neatly before 
 * 
 * If a single location is specified then the error will only specify 1 place for example "Error in Parse during parse Statement"
 * =========================================================================================================================
 */

#define SPACEING 20

void Parser::errMS(std::string loc, std::string mes, int i){
    std::cout << "\n\n=============================================================================\n";
    std::cout <<     "=                               Error Message                               =\n";
    std::cout <<     "=                                  Parser                                   =\n";
    std::cout <<     "=============================================================================\n\n";

    std::cout << std::setw(SPACEING) << std::left <<  "\tLocation ";
    std::cout << std::setw(SPACEING) << std::left <<  loc;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tExpected ";
    std::cout << std::setw(SPACEING) << std::left <<  mes;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tAt Index ";
    std::cout << std::setw(SPACEING) << std::left <<  std::to_string(i);
    std::cout << "\n";

    exit(EXIT_FAILURE);
}

void Parser::errMS(std::string loc1, std::string loc2, std::string mes, int i){
    std::cout << "\n\n=============================================================================\n";
    std::cout <<     "=                               Error Message                               =\n";
    std::cout <<     "=                                  Parser                                   =\n";
    std::cout <<     "=============================================================================\n\n";

    std::cout << std::setw(SPACEING) << std::left <<  "\tLocation ";
    std::cout << std::setw(SPACEING) << std::left <<  loc1;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tSub Location ";
    std::cout << std::setw(SPACEING) << std::left <<  loc2;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tExpected ";
    std::cout << std::setw(SPACEING) << std::left <<  mes;
    std::cout << "\n";
    std::cout << std::setw(SPACEING) << std::left <<  "\tAt Index ";
    std::cout << std::setw(SPACEING) << std::left <<  std::to_string(i);
    std::cout << "\n";

    exit(EXIT_FAILURE);
}