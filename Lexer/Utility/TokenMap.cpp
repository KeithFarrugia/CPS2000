#include "../Lexer.h"
/** ==========================================================================================================================
 *  ---------------------- Map Token
 * Function takes a final state and a token and maps them together through a map
 * ===========================================================================================================================
 */
void Lexer::mapToken(state_t final_state, token_t token) {
    token_map[final_state] = token;
}

/** ==========================================================================================================================
 *  ---------------------- INIT Token Map
 * Map all tokens to a final state 28
 * ===========================================================================================================================
 */

void Lexer::initTokenMap(){

    //          FINAL STATE             ,           TOKEN
    
    mapToken(   state_t::ST_INT         ,           token_t::INTEGER                );
    mapToken(   state_t::ST_FLT_2       ,           token_t::FLOATING_POINT         );
    mapToken(   state_t::ST_IDEN        ,           token_t::IDENTIFIER             );
    mapToken(   state_t::ST_WS          ,           token_t::WHITESPACE             );

    mapToken(   state_t::ST_GT          ,           token_t::GREATER_THAN           );
    mapToken(   state_t::ST_GTE         ,           token_t::GREATER_THAN_EQUAL     );
    mapToken(   state_t::ST_LT          ,           token_t::LESS_THAN              );
    mapToken(   state_t::ST_LTE         ,           token_t::LESS_THAN_EQUAL        );
    mapToken(   state_t::ST_EQLT        ,           token_t::EQUAL_TO               );
    mapToken(   state_t::ST_NOT_E       ,           token_t::NOT_EQUAL              );
    mapToken(   state_t::ST_NOT         ,           token_t::NOT                    );
    
    mapToken(   state_t::ST_EQL         ,           token_t::EQUAL                  );
    mapToken(   state_t::ST_MULT        ,           token_t::MULT                   );
    mapToken(   state_t::ST_DIV         ,           token_t::DIV                    );
    mapToken(   state_t::ST_ADD         ,           token_t::ADD                    );
    mapToken(   state_t::ST_SUB         ,           token_t::SUB                    );

    mapToken(   state_t::ST_PTR         ,           token_t::POINTER                );

    mapToken(   state_t::ST_OP_PAR      ,           token_t::OPEN_PAR               );
    mapToken(   state_t::ST_CL_PAR      ,           token_t::CLOSE_PAR              );
    mapToken(   state_t::ST_OP_SQ       ,           token_t::OPEN_SQUARE            );
    mapToken(   state_t::ST_CL_SQ       ,           token_t::CLOSE_SQUARE           );
    mapToken(   state_t::ST_OP_CR       ,           token_t::OPEN_CURL              );
    mapToken(   state_t::ST_CL_CR       ,           token_t::CLOSE_CURL             );

    mapToken(   state_t::ST_SEM         ,           token_t::SEMICOLON              );
    mapToken(   state_t::ST_COL         ,           token_t::COLON                  );
    mapToken(   state_t::ST_COM         ,           token_t::COMMA                  );
    mapToken(   state_t::ST_COLOUR_7    ,           token_t::COLOUR_LITERAL         );
    mapToken(   state_t::ST_COMMAND_3   ,           token_t::COMMAND                );


    mapToken(   state_t::ST_LINE_COM_1  ,           token_t::WHITESPACE             );
    mapToken(   state_t::ST_LINE_COM_2  ,           token_t::WHITESPACE             );
    mapToken(   state_t::ST_BLOCK_COM_3 ,           token_t::WHITESPACE             );
}