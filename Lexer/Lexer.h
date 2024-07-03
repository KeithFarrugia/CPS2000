#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <vector>
#include <memory>
#include "DFSA/DFSA.h"
#include <unordered_map> 
#include "../Utility/Utility.h"
#include "../Utility/types/States.h"
#include "../Utility/types/Tokens.h"
#include "../Utility/types/Lexemes.h"
#include "../Utility/types/Generic_Types.h"



class Lexer {
public:    
    
    // -------------------- Functions
    Lexer();
    void displayTable();

    std::vector<tokenised_t> GenerateTokens(const std::string& src_program_str, const bool is_debug);


private:

    // -------------------- INIT DFSA
    DFSA dfsa;
    
    void initDFSA();

    void initTransitions();

    // -------------------- INIT TOKEN MAP
    std::unordered_map<state_t, token_t> token_map;
    void mapToken(state_t final_state, token_t token);
    void initTokenMap();

    // -------------------- GENERATE
    lexeme_t generateLexeme(char c);
    tokenised_t generateToken(state_t final_state, std::string lexeme_string);


    token_t validateKeyword(std::string lexeme_string);    
    bool validateColour(std::string lexeme_string);
    token_t validateCommand(std::string lexeme_string);

    // -------------------- NEXT TOKEN
    tokenised_t nextToken(std::string src_program_str, int& src_program_idx, const bool is_debug);
};

#endif // LEXER_H