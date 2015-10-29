#ifndef EXTENDEDCALC_LEXER_HPP
#define EXTENDEDCALC_LEXER_HPP

#include <string>
#include <vector>
#include <stdexcept>

enum TokenType {
    LETTER,     // [a-z][A-Z]
    NUMBER,     // [-MAX INT, +MAX INT]
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MOD,
    LT,         // <
    GT,         // >
    EQUAL,      // ==
    LTE,        // <=
    GTE,        // >=
    NEQ,        // !=
    NOT,        // !
    AND,        // &&
    OR,         // ||
    TRUE,       // boolean value true
    FALSE,      // boolean value false
    WHITESPACE, // Whitespace
    LPAREN,     // (
    RPAREN,     // )
    NONE        // A token with no type
};

static const char * TOKEN_TYPE_VALUES[] = {
    "Letter", "Number", "Plus", "Minus", "Multiply", "Divide", "Mod", "LT", "GT", "Equal", "LTE", "GTE", "NEQ", "Not", "And", "Or", "True", "False", "Whitespace", "LPAREN", "RPAREN"
};

// A token consists of the type
// and its value
class Token {
    public:
        Token() : mType(NONE), mText("") {}
        Token(TokenType type, std::string text) : mType(type), mText(text) {}
        TokenType getType() const;
        std::string * getText();
    private:
        TokenType mType;
        std::string mText;
};

class Lexer {
    public:
        Lexer(std::istream & input);
        std::vector<Token> Lex();
    private:
        std::vector<Token> mTokens;
        std::istream & mStream;
};

class LexerException {
    public:
        LexerException(std::string msg) : mWhat(msg) {}
        LexerException(std::string msg, int loc) : mWhat(msg), mLocation(loc) {}

        std::string & what() {
            return mWhat;
        }

        int location() {
            return mLocation;
        }
    private:
        std::string mWhat;
        int mLocation;
};

#endif //EXTENDEDCALC_LEXER_HPP
