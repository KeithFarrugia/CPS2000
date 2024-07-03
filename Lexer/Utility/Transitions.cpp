#include "../Lexer.h"
/** ==========================================================================================================================
 *  ---------------------- Initialization of Transitions
 * ===========================================================================================================================
 */




void Lexer::initTransitions(){
    dfsa.Generate_Transition_Table();

    //                      Current State               ,           Lexeme                      ,           Next State

// INTEGER/FLOAT ---------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::digit             ,           state_t::ST_INT         );
    dfsa.addTransition(     state_t::ST_INT             ,           lexeme_t::digit             ,           state_t::ST_INT         );
    
    dfsa.addTransition(     state_t::ST_INT             ,           lexeme_t::dot               ,           state_t::ST_FLT_1       );
    dfsa.addTransition(     state_t::ST_FLT_1           ,           lexeme_t::digit             ,           state_t::ST_FLT_2       );
    dfsa.addTransition(     state_t::ST_FLT_2           ,           lexeme_t::digit             ,           state_t::ST_FLT_2       );
    
    // SYNTAX ERROR HANDLING
    dfsa.addTransition(     state_t::ST_INT             ,           lexeme_t::letter            ,           state_t::ST_SYNTAX_ERROR);
    dfsa.addTransition(     state_t::ST_INT             ,           lexeme_t::underscore        ,           state_t::ST_SYNTAX_ERROR);
    dfsa.addTransition(     state_t::ST_FLT_1           ,           lexeme_t::letter            ,           state_t::ST_SYNTAX_ERROR);
    dfsa.addTransition(     state_t::ST_FLT_1           ,           lexeme_t::underscore        ,           state_t::ST_SYNTAX_ERROR);
    dfsa.addTransition(     state_t::ST_FLT_2           ,           lexeme_t::letter            ,           state_t::ST_SYNTAX_ERROR);
    dfsa.addTransition(     state_t::ST_FLT_2           ,           lexeme_t::underscore        ,           state_t::ST_SYNTAX_ERROR);


// IDENTIFIER ------------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::letter            ,           state_t::ST_IDEN        );

    dfsa.addTransition(     state_t::ST_IDEN            ,           lexeme_t::letter            ,           state_t::ST_IDEN        );
    dfsa.addTransition(     state_t::ST_IDEN            ,           lexeme_t::underscore        ,           state_t::ST_IDEN        );
    dfsa.addTransition(     state_t::ST_IDEN            ,           lexeme_t::digit             ,           state_t::ST_IDEN        );
    

// WHITESPACE ------------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::space             ,           state_t::ST_WS          );
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::newline           ,           state_t::ST_WS          );

    dfsa.addTransition(     state_t::ST_WS              ,           lexeme_t::space             ,           state_t::ST_WS          );
    dfsa.addTransition(     state_t::ST_WS              ,           lexeme_t::newline           ,           state_t::ST_WS          );


// COMPARISON ------------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::greater_than      ,           state_t::ST_GT          );
    dfsa.addTransition(     state_t::ST_GT              ,           lexeme_t::equals            ,           state_t::ST_GTE         );

    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::less_than         ,           state_t::ST_LT          );
    dfsa.addTransition(     state_t::ST_LT              ,           lexeme_t::equals            ,           state_t::ST_LTE         );


    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::equals            ,           state_t::ST_EQL         );
    dfsa.addTransition(     state_t::ST_EQL             ,           lexeme_t::equals            ,           state_t::ST_EQLT        );

    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::exclamation       ,           state_t::ST_NOT         );
    dfsa.addTransition(     state_t::ST_NOT             ,           lexeme_t::equals            ,           state_t::ST_NOT_E       );


// OPERATORS -------------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::asterix           ,           state_t::ST_MULT        );
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::front_slash       ,           state_t::ST_DIV         );
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::plus              ,           state_t::ST_ADD         );
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::minus             ,           state_t::ST_SUB         );

    dfsa.addTransition(     state_t::ST_SUB             ,           lexeme_t::greater_than      ,           state_t::ST_PTR         );


// SCOPE SPECIFIERS ------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::open_brackets     ,           state_t::ST_OP_PAR      );
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::close_brackets    ,           state_t::ST_CL_PAR      );

    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::open_square       ,           state_t::ST_OP_SQ       );
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::close_square      ,           state_t::ST_CL_SQ       );

    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::open_curly        ,           state_t::ST_OP_CR       );
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::close_curly       ,           state_t::ST_CL_CR       );


// SYMBOLS ---------------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::semicolon         ,           state_t::ST_SEM         );
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::colon             ,           state_t::ST_COL         );
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::comma             ,           state_t::ST_COM         );


// COLOUR LITTERAL -------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::hashtag           ,           state_t::ST_COLOUR_1    );

    dfsa.addTransition(     state_t::ST_COLOUR_1        ,           lexeme_t::letter            ,           state_t::ST_COLOUR_2    );
    dfsa.addTransition(     state_t::ST_COLOUR_1        ,           lexeme_t::digit             ,           state_t::ST_COLOUR_2    );

    dfsa.addTransition(     state_t::ST_COLOUR_2        ,           lexeme_t::letter            ,           state_t::ST_COLOUR_3    );
    dfsa.addTransition(     state_t::ST_COLOUR_2        ,           lexeme_t::digit             ,           state_t::ST_COLOUR_3    );

    dfsa.addTransition(     state_t::ST_COLOUR_3        ,           lexeme_t::letter            ,           state_t::ST_COLOUR_4    );
    dfsa.addTransition(     state_t::ST_COLOUR_3        ,           lexeme_t::digit             ,           state_t::ST_COLOUR_4    );

    dfsa.addTransition(     state_t::ST_COLOUR_4        ,           lexeme_t::letter            ,           state_t::ST_COLOUR_5    );
    dfsa.addTransition(     state_t::ST_COLOUR_4        ,           lexeme_t::digit             ,           state_t::ST_COLOUR_5    );

    dfsa.addTransition(     state_t::ST_COLOUR_5        ,           lexeme_t::letter            ,           state_t::ST_COLOUR_6    );
    dfsa.addTransition(     state_t::ST_COLOUR_5        ,           lexeme_t::digit             ,           state_t::ST_COLOUR_6    );

    dfsa.addTransition(     state_t::ST_COLOUR_6        ,           lexeme_t::letter            ,           state_t::ST_COLOUR_7    );
    dfsa.addTransition(     state_t::ST_COLOUR_6        ,           lexeme_t::digit             ,           state_t::ST_COLOUR_7    );
    
    // SYNTAX ERROR HANDLING
    dfsa.addTransition(     state_t::ST_COLOUR_7        ,           lexeme_t::letter            ,           state_t::ST_SYNTAX_ERROR);
    dfsa.addTransition(     state_t::ST_COLOUR_7        ,           lexeme_t::digit             ,           state_t::ST_SYNTAX_ERROR);
    dfsa.addTransition(     state_t::ST_COLOUR_7        ,           lexeme_t::underscore        ,           state_t::ST_SYNTAX_ERROR);


// COMMAND ---------------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_START           ,           lexeme_t::underscore        ,           state_t::ST_COMMAND_1   );
    dfsa.addTransition(     state_t::ST_COMMAND_1       ,           lexeme_t::underscore        ,           state_t::ST_COMMAND_2   );

    dfsa.addTransition(     state_t::ST_COMMAND_2       ,           lexeme_t::letter            ,           state_t::ST_COMMAND_3   );
    dfsa.addTransition(     state_t::ST_COMMAND_3       ,           lexeme_t::letter            ,           state_t::ST_COMMAND_3   );
    dfsa.addTransition(     state_t::ST_COMMAND_3       ,           lexeme_t::underscore        ,           state_t::ST_COMMAND_3   ); 

    // SYNTAX ERROR HANDLING
    dfsa.addTransition(     state_t::ST_COMMAND_3       ,           lexeme_t::digit             ,           state_t::ST_SYNTAX_ERROR);


// LINE COMMENT ----------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_DIV             ,           lexeme_t::front_slash       ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::front_slash       ,           state_t::ST_LINE_COM_1  );

    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::letter            ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::digit             ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::space             ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::underscore        ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::plus              ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::minus             ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::equals            ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::greater_than      ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::less_than         ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::exclamation       ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::asterix           ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::front_slash       ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::back_slash        ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::open_brackets     ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::close_brackets    ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::open_square       ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::close_square      ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::open_curly        ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::close_curly       ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::colon             ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::semicolon         ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::comma             ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::dot               ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::hashtag           ,           state_t::ST_LINE_COM_1  );
    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::unknown           ,           state_t::ST_LINE_COM_1  );

    dfsa.addTransition(     state_t::ST_LINE_COM_1      ,           lexeme_t::newline           ,           state_t::ST_LINE_COM_2  );

// Block COMMENT ----------------------------------------------------------------------------------------------------------------------
    dfsa.addTransition(     state_t::ST_DIV             ,           lexeme_t::asterix           ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::front_slash       ,           state_t::ST_BLOCK_COM_1 );

    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::letter            ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::digit             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::space             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::newline           ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::underscore        ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::plus              ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::minus             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::equals            ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::greater_than      ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::less_than         ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::exclamation       ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::front_slash       ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::back_slash        ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::open_brackets     ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::close_brackets    ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::open_square       ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::close_square      ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::open_curly        ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::close_curly       ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::colon             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::semicolon         ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::comma             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::dot               ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::hashtag           ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::unknown           ,           state_t::ST_BLOCK_COM_1 );

    
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::letter            ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::digit             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::space             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::newline           ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::underscore        ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::plus              ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::minus             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::equals            ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::greater_than      ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::less_than         ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::exclamation       ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::back_slash        ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::open_brackets     ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::close_brackets    ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::open_square       ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::close_square      ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::open_curly        ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::close_curly       ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::colon             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::semicolon         ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::comma             ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::dot               ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::hashtag           ,           state_t::ST_BLOCK_COM_1 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::unknown           ,           state_t::ST_BLOCK_COM_1 );

    dfsa.addTransition(     state_t::ST_BLOCK_COM_1     ,           lexeme_t::asterix           ,           state_t::ST_BLOCK_COM_2 );
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::asterix           ,           state_t::ST_BLOCK_COM_2 );

    
    dfsa.addTransition(     state_t::ST_BLOCK_COM_2     ,           lexeme_t::front_slash       ,           state_t::ST_BLOCK_COM_3 );


}