#ifndef TOKENS_H
#define TOKENS_H
#include <string>

#define MAX_TOKENS 58
typedef enum {
  // --------------------- General Types
  INTEGER,
  FLOATING_POINT,
  IDENTIFIER,
  WHITESPACE,
  COLOUR_LITERAL,

  // --------------------- Equality Operators
  GREATER_THAN,
  GREATER_THAN_EQUAL,
  LESS_THAN,
  LESS_THAN_EQUAL,
  EQUAL_TO,
  NOT_EQUAL,

  // --------------------- Assignment Operators
  EQUAL,

  // --------------------- Mathametical Operators
  MULT,
  DIV,
  ADD,
  SUB,

  // --------------------- Pointer Operator
  POINTER,

  // --------------------- Scope Identifires
  OPEN_PAR,
  CLOSE_PAR,
  OPEN_CURL,
  CLOSE_CURL,
  OPEN_SQUARE,
  CLOSE_SQUARE,

  // --------------------- Other Symbols
  SEMICOLON,
  COLON,
  COMMA,

  // --------------------- Key Words
  FLOAT,
  INT,
  BOOL,
  COLOUR,

  FLOAT_ARRAY,
  INT_ARRAY,
  BOOL_ARRAY,
  COLOUR_ARRAY,

  TRUE,
  FALSE,

  COMMAND, // temporary token until a proper one is chosen
  WIDTH,
  HEIGHT,
  READ,
  RANDOM,
  PRINT,
  DELAY,
  WRITE_BOX,
  WRITE,
  CLEAR,

  AND,
  OR,
  NOT,

  AS,
  LET,
  RETURN,
  IF,
  ELSE,
  FOR,
  WHILE,
  FUN,
  // --------------------- Other
  NULL_TOKEN,

} token_t;

static const std::string tk_string(const token_t token) {
    switch (token) {
        // --------------------- General Types
        case INTEGER            : return "INTEGER";
        case FLOATING_POINT     : return "FLOATING_POINT";
        case IDENTIFIER         : return "IDENTIFIER";
        case WHITESPACE         : return "WHITESPACE";
        case COLOUR_LITERAL     : return "COLOUR_LITERAL";

        // --------------------- Equality Operators
        case GREATER_THAN       : return "GREATER_THAN";
        case GREATER_THAN_EQUAL : return "GREATER_THAN_EQUAL";
        case LESS_THAN          : return "LESS_THAN";
        case LESS_THAN_EQUAL    : return "LESS_THAN_EQUAL";
        case EQUAL_TO           : return "EQUAL_TO";
        case NOT_EQUAL          : return "NOT_EQUAL";

        // --------------------- Assignment Operators
        case EQUAL              : return "EQUAL";

        // --------------------- Mathematical Operators
        case MULT               : return "MULT";
        case DIV                : return "DIV";
        case ADD                : return "ADD";
        case SUB                : return "SUB";

        // --------------------- Pointer Operator
        case POINTER            : return "POINTER";

        // --------------------- Scope Identifiers
        case OPEN_PAR           : return "OPEN_PAR";
        case CLOSE_PAR          : return "CLOSE_PAR";
        case OPEN_CURL          : return "OPEN_CURL";
        case CLOSE_CURL         : return "CLOSE_CURL";
        case OPEN_SQUARE        : return "OPEN_SQUARE";
        case CLOSE_SQUARE       : return "CLOSE_SQUARE";

        // --------------------- Other Symbols
        case SEMICOLON        : return "SEMICOLON";
        case COLON            : return "COLON";
        case COMMA            : return "COMMA";

        // --------------------- Keywords
        case FLOAT            : return "FLOAT";
        case INT              : return "INT";
        case BOOL             : return "BOOL";
        case COLOUR           : return "COLOUR";

        case FLOAT_ARRAY      : return "FLOAT_ARRAY";
        case INT_ARRAY        : return "INT_ARRAY";
        case BOOL_ARRAY       : return "BOOL_ARRAY";
        case COLOUR_ARRAY     : return "COLOUR_ARRAY";

        case TRUE             : return "TRUE";
        case FALSE            : return "FALSE";

        case COMMAND          : return "COMMAND";
        case WIDTH            : return "WIDTH";
        case HEIGHT           : return "HEIGHT";
        case READ             : return "READ";
        case RANDOM           : return "RANDOM";
        case PRINT            : return "PRINT";
        case DELAY            : return "DELAY";
        case WRITE_BOX        : return "WRITE_BOX";
        case WRITE            : return "WRITE";
        case CLEAR            : return "CLEAR";
        case AND              : return "AND";
        case OR               : return "OR";
        case NOT              : return "NOT";
        case AS               : return "AS";
        case LET              : return "LET";
        case RETURN           : return "RETURN";
        case IF               : return "IF";
        case ELSE             : return "ELSE";
        case FOR              : return "FOR";
        case WHILE            : return "WHILE";
        case FUN              : return "FUN";

        // --------------------- Other
        case NULL_TOKEN       : return "NULL_TOKEN";
        default               : return "UNKNOWN_TOKEN";
    }
}

static const std::string tk_string(int token) {
  return tk_string(static_cast<token_t>(token));
}
#endif  // TOKENS_H