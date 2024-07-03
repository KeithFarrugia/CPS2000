#include "../Lexer.h"

bool Lexer::validateColour(std::string lexeme_string){
    for (size_t i = 1; i < lexeme_string.length(); ++i) {
        char c = lexeme_string[i];
        // Check if the character is a valid hexadecimal digit (0-9, A-F, a-f)
        if (!isxdigit(c)) {
            return false;
        }
    }

    return true;
}

 token_t Lexer::validateCommand(std::string lexeme_string){
    if      (   lexeme_string == "__width"      )   { return token_t::WIDTH;        }
    else if (   lexeme_string == "__height"     )   { return token_t::HEIGHT;       }
    else if (   lexeme_string == "__read"       )   { return token_t::READ;         }
    else if (   lexeme_string == "__random_int" )   { return token_t::RANDOM;       }
    else if (   lexeme_string == "__print"      )   { return token_t::PRINT;        }
    else if (   lexeme_string == "__delay"      )   { return token_t::DELAY;        }
    else if (   lexeme_string == "__write_box"  )   { return token_t::WRITE_BOX;    }
    else if (   lexeme_string == "__write"      )   { return token_t::WRITE;        }
    else if (   lexeme_string == "__clear"      )   { return token_t::CLEAR;        }

    return token_t::COMMAND;
 }

token_t Lexer::validateKeyword(std::string lexeme_string){
    if      (   lexeme_string == "float"        )   { return token_t::FLOAT;    }
    else if (   lexeme_string == "int"          )   { return token_t::INT;      }
    else if (   lexeme_string == "bool"         )   { return token_t::BOOL;     }
    else if (   lexeme_string == "colour"       )   { return token_t::COLOUR;   }

    else if (   lexeme_string == "true"         )   { return token_t::TRUE;     }
    else if (   lexeme_string == "false"        )   { return token_t::FALSE;    }

    else if (   lexeme_string == "let"          )   { return token_t::LET;      }
    else if (   lexeme_string == "not"          )   { return token_t::NOT;      }
    else if (   lexeme_string == "and"          )   { return token_t::AND;      }
    else if (   lexeme_string == "or"           )   { return token_t::OR;       }
    else if (   lexeme_string == "as"           )   { return token_t::AS;       }
    else if (   lexeme_string == "return"       )   { return token_t::RETURN;   }
    else if (   lexeme_string == "if"           )   { return token_t::IF;       }
    else if (   lexeme_string == "else"         )   { return token_t::ELSE;     }
    else if (   lexeme_string == "for"          )   { return token_t::FOR;      }
    else if (   lexeme_string == "while"        )   { return token_t::WHILE;    }
    else if (   lexeme_string == "fun"          )   { return token_t::FUN;      }


    return IDENTIFIER;
}