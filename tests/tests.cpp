#include "parser.h"
#include <iostream>
#include "slrbuild.h"
void runner(const std::vector<Token>& tokens,const std::string& name)
{
    std::cout << "\n ===TEST: " << name << " =================)\n";
    SLRparser parser = buildSLR();
    parser.parse(tokens);
}

int main()
{
    runner({Token::ID, Token::END}, "ID");

    runner({Token::ID, Token::PLUS, Token::ID, Token::END},
            "ID + ID");

    runner({Token::ID, Token::PLUS, Token::ID, Token::MUL,
             Token::ID, Token::END},
            "ID + ID * ID");

    runner({Token::LPAREN, Token::ID, Token::PLUS, Token::ID,
             Token::RPAREN, Token::MUL, Token::ID, Token::END},
            "(ID + ID) * ID");

    runner({Token::PLUS, Token::ID, Token::END},
            "+ID");

    runner({Token::ID, Token::PLUS, Token::END},
            "ID+");

    runner({Token::LPAREN, Token::RPAREN, Token::END},
            "()");

    runner({Token::ID, Token::PLUS, Token::MUL,
             Token::ID, Token::END},
            "ID+*ID");
    runner({Token::NUM, Token::PLUS, Token::ID,Token::END},
            "NUM+ID");
    return 0;
}
