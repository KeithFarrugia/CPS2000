#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_map> 
#include <iomanip>

#include "types/Generic_Types.h"
#include "types/Lexemes.h"
#include "types/States.h"
#include "types/Tokens.h"

/** ==========================================================================================================================
 *  ---------------------- To Upper Case
 *  converts a given string to upper case
 * ===========================================================================================================================
 */
inline std::string toUpperCase(std::string& input) {    
    // Convert each character in the string to uppercase
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::toupper(c); });

    return input;
}

/** ==========================================================================================================================
 *  ---------------------- Next / Peak Char
 * consume the next character and increase the index 
 * or simply read the next character without increasing
 * the index
 * ===========================================================================================================================
 */
inline char nextChar(const std::string& src_program_str, int& src_program_idx) {
    if (src_program_idx < src_program_str.length()) {
        return src_program_str[src_program_idx++];
    } else {
        return EOF; // Return EOF
    }
}

inline char peekChar(const std::string& src_program_str, int src_program_idx) {
    if (src_program_idx < src_program_str.length()) {
        return src_program_str[src_program_idx];
    } else {
        return EOF; // Return EOF
    }
}

/** ==========================================================================================================================
 *  ---------------------- Read File to String
 * Read a file and return a string containing that
 * file's contents
 * ===========================================================================================================================
 */
inline std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}


/** ==========================================================================================================================
 *  ---------------------- Throw Error
 * Throws an error with the given message
 * ===========================================================================================================================
 */
inline void throwErr(const std::string errorMessage){
    std::cerr << errorMessage <<std::endl;
    exit(EXIT_FAILURE);
}

/** ==========================================================================================================================
 *  ---------------------- Print Tokenised List
 * Prints the list of tokens and lexemes
 * ===========================================================================================================================
 */
inline void printTokenisedList(std::vector<tokenised_t> toks){
    std::cout << "\n\n============================ TOKEN LIST ============================\n\n";
    int i = 0;
    for (const auto& t : toks) {
        std::cout  << std::setw(6) << std::left << i++;
        std::cout << std::setw(18) << std::left << tk_string(t.token_type);
        std::cout << " [";
        for (char c : t.lexeme_string) {
            if (c == '\n') {
                std::cout << "\\n"; // print as '\n'
            } else {
                std::cout << c;
            }
        }
        std::cout << "]" << std::endl;
    }
}

/** ==========================================================================================================================
 *  ---------------------- Is token a Type
 * checks if a given token is a type token
 * ===========================================================================================================================
 */
inline bool isToken_a_Type(token_t tok){
    switch(tok){
        case token_t::BOOL:
        case token_t::INT:
        case token_t::FLOAT:
        case token_t::COLOUR:
            return true;
        default:
            return false;
    }
}

/** ==========================================================================================================================
 *  ---------------------- Convert Type to Array
 * converts a normal type to its array equivalent
 * ===========================================================================================================================
 */
inline token_t convert_Type_to_Array(token_t tok){
    switch(tok){
        case token_t::BOOL          : return token_t::BOOL_ARRAY; 
        case token_t::INT           : return token_t::INT_ARRAY;
        case token_t::FLOAT         : return token_t::FLOAT_ARRAY;
        case token_t::COLOUR        : return token_t::COLOUR_ARRAY;
        default                     : return token_t::NULL_TOKEN;
    }
}

/** ==========================================================================================================================
 *  ---------------------- Convert Array to Type
 * converts a given array type to a normal type
 * ===========================================================================================================================
 */
inline token_t convert_Array_to_Type(token_t tok){
    switch(tok){
        case token_t::BOOL_ARRAY    : return token_t::BOOL; 
        case token_t::INT_ARRAY     : return token_t::INT;
        case token_t::FLOAT_ARRAY   : return token_t::FLOAT;
        case token_t::COLOUR_ARRAY  : return token_t::COLOUR;
        default                     : return token_t::NULL_TOKEN;
    }
}

/** ==========================================================================================================================
 *  ---------------------- Is token an Array
 * checks if a given token type is an array type
 * ===========================================================================================================================
 */
inline bool isType_an_Array(token_t tok){
    switch(tok){
        case token_t::BOOL_ARRAY:
        case token_t::INT_ARRAY:
        case token_t::FLOAT_ARRAY:
        case token_t::COLOUR_ARRAY:
            return true;
        default:
            return false;
    }
}

#endif //UTILITY_H
