#include "slrbuild.h"
#include "token.h"
#include <iostream>
#include <vector>


extern int yylex();
int main()
{
    std::vector<Token> tokens;
    while (true) {
        int t = yylex();
        Token tok = static_cast<Token>(t);
        tokens.push_back(tok);
        if (tok == Token::END) break;
    }

    SLRparser parser = buildSLR();
    parser.parse(tokens);
    return 0;
}
