#include "Lexer.hpp"
#include <istream>
#include <sstream>
#include <stdexcept>

Lexer::Lexer(std::istream & input) : mStream(input) { }

std::vector<Token> Lexer::Lex() {
    char current;
    while (!mStream.eof()) {
        mStream.get(current);
        if (isdigit(current)) {
            std::stringstream ss;
            while (isdigit(current) && !mStream.eof()) {
                ss << current;
                if (!isdigit(mStream.peek()))
                    break;
                mStream.get(current);
            }
            Token t = Token(TokenType::NUMBER, ss.str());
            mTokens.push_back(t);
        } else if (current == ' ') {
            Token t = Token(TokenType::WHITESPACE, " ");
            mTokens.push_back(t);
        } else if (current == '>') {
            if (mStream.peek() == '=') {
                mStream.get(current);
                Token t = Token(TokenType::GTE, ">=");
                mTokens.push_back(t);
            } else {
                Token t = Token(TokenType::GT, ">");
                mTokens.push_back(t);
            }
        } else if (current == '<') {
            if (mStream.peek() == '=') {
                mStream.get(current);
                Token t = Token(TokenType::LTE, "<=");
                mTokens.push_back(t);
            } else {
                Token t = Token(TokenType::LT, "<");
                mTokens.push_back(t);
            }
        } else if (current == '=') {
            if (mStream.peek() == '=') {
                mStream.get(current);
                Token t = Token(TokenType::EQUAL, "==");
                mTokens.push_back(t);
            } else {
                // Invalid token
            }
        } else if (current == 't') {
            char trueVal[4];
            trueVal[0] = 't';
            long pos = mStream.tellg();
            trueVal[1] = (char)mStream.peek();
            mStream.seekg(pos + 1);
            trueVal[2] = (char)mStream.peek();
            mStream.seekg(pos + 2);
            trueVal[3] = (char)mStream.peek();
            if ((trueVal[0] == 't' || trueVal[0] == 'T')  && trueVal[1] == 'r' && trueVal[2] == 'u' && trueVal[3] == 'e') {
                Token t = Token(TokenType::TRUE, "true");
                mTokens.push_back(t);
                mStream.seekg(pos + 3);
            } else {
                // Could be a variable name, or something else...but not in this language
            }
        } else if (current == 'f') {
            char falseVal[5];
            falseVal[0] = 'f';
            long pos = mStream.tellg();
            falseVal[1] = (char)mStream.peek();
            mStream.seekg(pos + 1);
            falseVal[2] = (char)mStream.peek();
            mStream.seekg(pos + 2);
            falseVal[3] = (char)mStream.peek();
            mStream.seekg(pos + 3);
            falseVal[4] = (char)mStream.peek();
            if ((falseVal[0] == 'f' || falseVal[0] == 'F') && falseVal[1] == 'a' && falseVal[2] == 'l' && falseVal[3] == 's' && falseVal[4] == 'e') {
                Token t = Token(TokenType::FALSE, "false");
                mTokens.push_back(t);
                mStream.seekg(pos + 3);
            } else {
                // Could be a variable name, or something else...but not in this language
            }
        } else if (current == '!') {
            if (mStream.peek() == '=') {
                mStream.get(current);
                Token t = Token(TokenType::NEQ, "!=");
                mTokens.push_back(t);
            } else {
                Token t = Token(TokenType::NOT, "!");
                mTokens.push_back(t);
            }
        } else if (current == '&') {
            if (mStream.peek() == '&') {
                mStream.get(current);
                Token t = Token(TokenType::AND, "&&");
                mTokens.push_back(t);
            } else {
                // Invalid token
            }
        } else if (current == '|') {
            if (mStream.peek() == '|') {
                mStream.get(current);
                Token t = Token(TokenType::OR, "||");
                mTokens.push_back(t);
            } else {
                // Invalid token
            }
        } else if (current == '+') {
            Token t = Token(TokenType::PLUS, "+");
            mTokens.push_back(t);
        } else if (current == '-') {
            Token t = Token(TokenType::MINUS, "-");
            mTokens.push_back(t);
        } else if (current == '*') {
            Token t = Token(TokenType::MULTIPLY, "*");
            mTokens.push_back(t);
        } else if (current == '/') {
            Token t = Token(TokenType::DIVIDE, "/");
            mTokens.push_back(t);
        } else if (current == '%') {
            Token t = Token(TokenType::MOD, "%");
            mTokens.push_back(t);
        } else if (current == '(' || current == ')') {
            switch (current) {
                case '(':
                    mTokens.push_back(Token(TokenType::LPAREN, "("));
                    break;
                case ')':
                    mTokens.push_back(Token(TokenType::RPAREN, ")"));
                    break;
            }
        }
    }
    return mTokens;
}

TokenType Token::getType() const {
    return mType;
}

std::string * Token::getText() {
    return &mText;
}