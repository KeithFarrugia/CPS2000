#ifndef STATES_H
#define STATES_H
#include <string>

#define MAX_STATES 45
typedef enum {
    ST_START,
    ST_ERROR,
    ST_SYNTAX_ERROR, // used in the stack to have an endpoint
    
    // --------------------- INTEGER/FLOAT STATES
    ST_INT,
    ST_FLT_1,
    ST_FLT_2,

    // --------------------- IDENTTIFIER STATES
    ST_IDEN,
    
    // --------------------- WHITESPACE STATES
    ST_WS,

    // --------------------- COMPERISON OPERATOR STATES
    ST_GT,
    ST_GTE,
    ST_LT,
    ST_LTE,
    ST_EQLT,
    ST_NOT,
    ST_NOT_E,
    
    // --------------------- MATHAMETICAL OPERATOR STATES
    ST_EQL,
    ST_MULT,
    ST_DIV,
    ST_ADD,
    ST_SUB,

    // ---------------------  POINTER STATES
    ST_PTR,
    
    // --------------------- SCOPE STATES
    ST_OP_PAR,
    ST_CL_PAR,
    ST_OP_SQ,
    ST_CL_SQ,
    ST_OP_CR,
    ST_CL_CR,

    // ---------------------  OTHER SYMBOLS STATES
    ST_SEM,
    ST_COL,
    ST_COM,

    // --------------------- COLOUR LITTERAL STATES
    ST_COLOUR_1,
    ST_COLOUR_2,
    ST_COLOUR_3,
    ST_COLOUR_4,
    ST_COLOUR_5,
    ST_COLOUR_6,
    ST_COLOUR_7,

    // --------------------- COMMANDS STATES
    ST_COMMAND_1,
    ST_COMMAND_2,
    ST_COMMAND_3,
    
    // --------------------- COMMENT STATES
    ST_BLOCK_COM_1,
    ST_BLOCK_COM_2,
    ST_BLOCK_COM_3,

    ST_LINE_COM_1,
    ST_LINE_COM_2,


}state_t;


static const std::string st_string(const state_t state) {
    switch (state) {
        case ST_START               : return "START";
        case ST_ERROR               : return "ERROR";
        case ST_SYNTAX_ERROR        : return "ST_SYNTAX_ERROR";

        // ---------------------  INTEGER/FLOAT STATES
        case ST_INT                 : return "ST_INT";
        case ST_FLT_1               : return "ST_FLT_1";
        case ST_FLT_2               : return "ST_FLT_2";

        // --------------------- IDENTTIFIER STATES
        case ST_IDEN                : return "ST_IDEN";

        // --------------------- WHITESPACE STATES
        case ST_WS                  : return "ST_WS";
    
        // --------------------- WHITESPACE STATES
        case ST_GT                  : return "ST_GT";

        // --------------------- COMPERISON OPERATOR STATES
        case ST_GTE                 : return "ST_GTE";
        case ST_LT                  : return "ST_LT";
        case ST_LTE                 : return "ST_LTE";
        case ST_EQLT                : return "ST_EQLT";
        case ST_NOT                 : return "ST_NOT";
        case ST_NOT_E               : return "ST_NOT_E";

        // --------------------- MATHAMETICAL OPERATOR STATES
        case ST_EQL                 : return "ST_EQL";
        case ST_MULT                : return "ST_MULT";
        case ST_DIV                 : return "ST_DIV";
        case ST_ADD                 : return "ST_ADD";
        case ST_SUB                 : return "ST_SUB";

        // ---------------------  POINTER STATES
        case ST_PTR                 : return "ST_PTR";

        // --------------------- SCOPE STATES
        case ST_OP_PAR              : return "ST_OP_PAR";
        case ST_CL_PAR              : return "ST_CL_PAR";
        case ST_OP_SQ               : return "ST_OP_SQ";
        case ST_CL_SQ               : return "ST_CL_SQ";
        case ST_OP_CR               : return "ST_OP_CR";
        case ST_CL_CR               : return "ST_CL_CR";

        // ---------------------  OTHER SYMBOLS STATES
        case ST_SEM                 : return "ST_SEM";
        case ST_COL                 : return "ST_COL";
        case ST_COM                 : return "ST_COM";

        // --------------------- COLOUR LITTERAL STATES
        case ST_COLOUR_1            : return "ST_COLOUR_1";
        case ST_COLOUR_2            : return "ST_COLOUR_2";
        case ST_COLOUR_3            : return "ST_COLOUR_3";
        case ST_COLOUR_4            : return "ST_COLOUR_4";
        case ST_COLOUR_5            : return "ST_COLOUR_5";
        case ST_COLOUR_6            : return "ST_COLOUR_6";
        case ST_COLOUR_7            : return "ST_COLOUR_7";

        // --------------------- COMMAND STATES
        case ST_COMMAND_1           : return "ST_COMMAND_1";
        case ST_COMMAND_2           : return "ST_COMMAND_2";
        case ST_COMMAND_3           : return "ST_COMMAND_3";

        // --------------------- COMMENT STATES
        case ST_BLOCK_COM_1         : return "ST_BLOCK_COM_1";
        case ST_BLOCK_COM_2         : return "ST_BLOCK_COM_2";
        case ST_BLOCK_COM_3         : return "ST_BLOCK_COM_3";

        
        case ST_LINE_COM_1          : return "ST_LINE_COM_1";
        case ST_LINE_COM_2          : return "ST_LINE_COM_2";

        // --------------------- OTHER
        default                     : return "UNKNOWN_STATE";
    }
}
static const std::string st_string(int state) {
    return st_string(static_cast<state_t>(state));
}
#endif // STATES_H