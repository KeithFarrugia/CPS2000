#include "../Lexer.h"


/** ==========================================================================================================================
 *  ---------------------- Generate Token 
 *  Generates a token given a final state using the map
 * ===========================================================================================================================
 */
tokenised_t Lexer::generateToken(state_t final_state, std::string lexeme_string) {
    std::unordered_map<state_t, token_t>::const_iterator iterator = token_map.find(final_state);
    if (iterator != token_map.end()) {
        return tokenised_t(iterator->second, lexeme_string);
    } else {
        throw std::runtime_error("Error [Lexer::GenerateToken]: Cannot find token for final state: [" + st_string(final_state) + "]");
    }
}

/** ==========================================================================================================================
 *  ---------------------- Generate Lexeme
 *  Generates a Lexeme given a character
 * ===========================================================================================================================
 */
lexeme_t Lexer::generateLexeme(char c){
    switch (c) {
        case 'A' ... 'Z'            : return lexeme_t::letter;
        case 'a' ... 'z'            : return lexeme_t::letter;

        case '0' ... '9'            : return lexeme_t::digit;

        case ' '                    : return lexeme_t::space;
        case '\n'                   : return lexeme_t::newline;

        case '_'                    : return lexeme_t::underscore;
        case '+'                    : return lexeme_t::plus;
        case '-'                    : return lexeme_t::minus;
        case '='                    : return lexeme_t::equals;
        case '>'                    : return lexeme_t::greater_than;
        case '<'                    : return lexeme_t::less_than;
        case '!'                    : return lexeme_t::exclamation;
        case '*'                    : return lexeme_t::asterix;
        case '/'                    : return lexeme_t::front_slash;
        case '\\'                    : return lexeme_t::back_slash;

        case '('                    : return lexeme_t::open_brackets;
        case ')'                    : return lexeme_t::close_brackets;
        case '['                    : return lexeme_t::open_square;
        case ']'                    : return lexeme_t::close_square;
        case '{'                    : return lexeme_t::open_curly;
        case '}'                    : return lexeme_t::close_curly;

        case ':'                    : return lexeme_t::colon;
        case ';'                    : return lexeme_t::semicolon;
        case ','                    : return lexeme_t::comma;
        case '.'                    : return lexeme_t::dot;
        case '#'                    : return lexeme_t::hashtag;

        default:
            return lexeme_t::unknown;
    }
}