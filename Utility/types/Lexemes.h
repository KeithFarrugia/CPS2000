#ifndef LEXEMES_H
#define LEXEMES_H
#include <string>

#define MAX_LEXEMES 26

typedef enum           {
    letter,
    digit,
    space,
    newline,
    underscore,

    plus,
    minus,
    equals,
    greater_than,
    less_than,
    exclamation,
    asterix,

    front_slash,
    back_slash,

    open_brackets,
    close_brackets,
    open_square,
    close_square,
    open_curly,
    close_curly,

    colon,
    semicolon,
    comma,
    dot,
    hashtag,

    unknown
}lexeme_t;

static const std::string lex_string(const lexeme_t lexeme) {
    switch (lexeme) {
        case letter             : return "letter";
        case digit              : return "digit";
        case space              : return "space";
        case newline            : return "newline";
        case underscore         : return "underscore";
        case plus               : return "plus";
        case minus              : return "minus";
        case equals             : return "equals";
        case greater_than       : return "greater_than";
        case less_than          : return "less_than";
        case exclamation        : return "exclamation";
        case asterix            : return "asterix";
        case front_slash        : return "front_slash";
        case back_slash         : return "back_slash";
        case open_brackets      : return "open_brackets";
        case close_brackets     : return "close_brackets";
        case open_square        : return "open_square";
        case close_square       : return "close_square";
        case open_curly         : return "open_curly";
        case close_curly        : return "close_curly";
        case colon              : return "colon";
        case semicolon          : return "semicolon";
        case comma              : return "comma";
        case dot                : return "dot";
        case hashtag            : return "hashtag";
        case unknown            : return "unknown";
        default                 : return "UNKNOWN_LEXEME";
    }
}

static const std::string lex_string(int state) {
    return lex_string(static_cast<lexeme_t>(state));
}
#endif // LEXEMES_H