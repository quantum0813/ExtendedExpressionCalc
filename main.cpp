#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Type.hpp"
#include "AST.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

using namespace std;

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    Lexer l = Lexer(ss);
    vector<Token> tokens;
    try {
        tokens = l.Lex();
    } catch (LexerException & ex) {
        std::cout << ex.what() << std::endl;
    }

    Parser p = Parser(tokens);
    Expression * expr = p.Parse();

    EvaluateVisitor * visitor = new EvaluateVisitor();

    expr->accept(visitor);
    cout << endl;

    return 0;
}