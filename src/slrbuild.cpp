#include "parser.h"

SLRparser buildSLR()
{
    //  grammar arithmetic language
    std::vector<Production> grammar = {
        { NonTerminal::E, {"E", "+", "T"} },
        { NonTerminal::E, {"E", "-", "T"} },
        { NonTerminal::E, {"T"} },
        { NonTerminal::T, {"T", "*", "F"} },
        { NonTerminal::T, {"T", "/", "F"} },
        { NonTerminal::T, {"F"} },
        { NonTerminal::F, {"(", "E", ")"} },
        { NonTerminal::F, {"ID"} },
        { NonTerminal::F, {"NUM"} }
    };

    //  action
    std::unordered_map<size_t, std::unordered_map<Token, Action>> action;

    // state 0
    action[0][Token::ID]     = {Action::Type::Shift, 5};
    action[0][Token::NUM]    = {Action::Type::Shift, 5};
    action[0][Token::LPAREN] = {Action::Type::Shift, 4};
    // state 1
    action[1][Token::PLUS]   = {Action::Type::Shift, 6};
    action[1][Token::MINUS]  = {Action::Type::Shift, 7};
    action[1][Token::END]    = {Action::Type::Accept, 0};
    // state 2 (E → T•)
    action[2][Token::PLUS]   = {Action::Type::Reduce, 2};
    action[2][Token::MINUS]  = {Action::Type::Reduce, 2};
    action[2][Token::MUL]    = {Action::Type::Shift, 8};
    action[2][Token::DIV]    = {Action::Type::Shift, 9};
    action[2][Token::RPAREN] = {Action::Type::Reduce, 2};
    action[2][Token::END]    = {Action::Type::Reduce, 2};

    // state 3 (T → F•)
    action[3][Token::PLUS]   = {Action::Type::Reduce, 5};
    action[3][Token::MINUS]  = {Action::Type::Reduce, 5};
    action[3][Token::MUL]    = {Action::Type::Reduce, 5};
    action[3][Token::DIV]    = {Action::Type::Reduce, 5};
    action[3][Token::RPAREN] = {Action::Type::Reduce, 5};
    action[3][Token::END]    = {Action::Type::Reduce, 5};

    // state 4 ('(')
    action[4][Token::ID]     = {Action::Type::Shift, 5};
    action[4][Token::NUM]    = {Action::Type::Shift, 5};
    action[4][Token::LPAREN] = {Action::Type::Shift, 4};

    // state 5 (F → ID• or F → NUM•)
    action[5][Token::PLUS]   = {Action::Type::Reduce, 7};
    action[5][Token::MINUS]  = {Action::Type::Reduce, 7};
    action[5][Token::MUL]    = {Action::Type::Reduce, 7};
    action[5][Token::DIV]    = {Action::Type::Reduce, 7};
    action[5][Token::RPAREN] = {Action::Type::Reduce, 7};
    action[5][Token::END]    = {Action::Type::Reduce, 7};

    // state 6 ('+')
    action[6][Token::ID]     = {Action::Type::Shift, 5};
    action[6][Token::NUM]    = {Action::Type::Shift, 5};
    action[6][Token::LPAREN] = {Action::Type::Shift, 4};

    // state 7 ('-')
    action[7][Token::ID]     = {Action::Type::Shift, 5};
    action[7][Token::NUM]    = {Action::Type::Shift, 5};
    action[7][Token::LPAREN] = {Action::Type::Shift, 4};

    // state 8 ('*')
    action[8][Token::ID]     = {Action::Type::Shift, 5};
    action[8][Token::NUM]    = {Action::Type::Shift, 5};
    action[8][Token::LPAREN] = {Action::Type::Shift, 4};

    // state 9 ('/')
    action[9][Token::ID]     = {Action::Type::Shift, 5};
    action[9][Token::NUM]    = {Action::Type::Shift, 5};
    action[9][Token::LPAREN] = {Action::Type::Shift, 4};

    // state 10 (F → (E•))
    action[10][Token::PLUS]  = {Action::Type::Shift, 6};
    action[10][Token::MINUS] = {Action::Type::Shift, 7};
    action[10][Token::RPAREN]= {Action::Type::Shift, 15};

    // state 11 (E → E + T•)
    action[11][Token::PLUS]   = {Action::Type::Reduce, 0};
    action[11][Token::MINUS]  = {Action::Type::Reduce, 0};
    action[11][Token::MUL]    = {Action::Type::Shift, 8};
    action[11][Token::DIV]    = {Action::Type::Shift, 9};
    action[11][Token::RPAREN] = {Action::Type::Reduce, 0};
    action[11][Token::END]    = {Action::Type::Reduce, 0};

    // state 12 (E → E - T•)
    action[12][Token::PLUS]   = {Action::Type::Reduce, 1};
    action[12][Token::MINUS]  = {Action::Type::Reduce, 1};
    action[12][Token::MUL]    = {Action::Type::Shift, 8};
    action[12][Token::DIV]    = {Action::Type::Shift, 9};
    action[12][Token::RPAREN] = {Action::Type::Reduce, 1};
    action[12][Token::END]    = {Action::Type::Reduce, 1};

    // state 13 (T → T * F•)
    action[13][Token::PLUS]   = {Action::Type::Reduce, 3};
    action[13][Token::MINUS]  = {Action::Type::Reduce, 3};
    action[13][Token::MUL]    = {Action::Type::Reduce, 3};
    action[13][Token::DIV]    = {Action::Type::Reduce, 3};
    action[13][Token::RPAREN] = {Action::Type::Reduce, 3};
    action[13][Token::END]    = {Action::Type::Reduce, 3};

    // state 14 (T → T / F•)
    action[14][Token::PLUS]   = {Action::Type::Reduce, 4};
    action[14][Token::MINUS]  = {Action::Type::Reduce, 4};
    action[14][Token::MUL]    = {Action::Type::Reduce, 4};
    action[14][Token::DIV]    = {Action::Type::Reduce, 4};
    action[14][Token::RPAREN] = {Action::Type::Reduce, 4};
    action[14][Token::END]    = {Action::Type::Reduce, 4};

    // state 15 (F → (E)•)
    action[15][Token::PLUS]   = {Action::Type::Reduce, 6};
    action[15][Token::MINUS]  = {Action::Type::Reduce, 6};
    action[15][Token::MUL]    = {Action::Type::Reduce, 6};
    action[15][Token::DIV]    = {Action::Type::Reduce, 6};
    action[15][Token::RPAREN] = {Action::Type::Reduce, 6};
    action[15][Token::END]    = {Action::Type::Reduce, 6};

    //  goto
    std::unordered_map<size_t, std::unordered_map<NonTerminal, size_t>> go_to;

    go_to[0][NonTerminal::E] = 1;
    go_to[0][NonTerminal::T] = 2;
    go_to[0][NonTerminal::F] = 3;

    go_to[4][NonTerminal::E] = 10;
    go_to[4][NonTerminal::T] = 2;
    go_to[4][NonTerminal::F] = 3;

    go_to[6][NonTerminal::T] = 11;
    go_to[6][NonTerminal::F] = 3;

    go_to[7][NonTerminal::T] = 12;
    go_to[7][NonTerminal::F] = 3;

    go_to[8][NonTerminal::F] = 13;
    go_to[9][NonTerminal::F] = 14;


    //out SLR table
    return SLRparser(std::move(grammar),std::move(action),std::move(go_to));
}
