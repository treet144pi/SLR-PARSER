#include "parser.h"
#include <iostream>

std::string tokenString(Token t)
{
    switch (t)
    {
        case Token::ID:    return "ID";
        case Token::NUM:   return "NUM";
        case Token::PLUS:  return "+";
        case Token::MUL:   return "*";
        case Token::MINUS: return "-";
        case Token::DIV:   return "/";
        case Token::LPAREN:return "(";
        case Token::RPAREN:return ")";
        case Token::END:   return "$";
        default:           return "U"; // unknown
    }
}

std::string nonTerminalString(NonTerminal nt)
{
    switch (nt)
    {
        case NonTerminal::E: return "E";
        case NonTerminal::T: return "T";
        case NonTerminal::F: return "F";
        default:             return "U"; // unknown
    }
}

std::string stackString(const std::vector<std::string>& v) {
    std::string res = "$";
    for (auto& s : v) res += s;
    return res;
}

std::string inputString(const std::vector<Token>& tokens, size_t pos) {
    std::string res;
    for (size_t i = pos; i < tokens.size(); ++i) res += tokenString(tokens[i]);
    return res;
}

std::string actionString(const Action& a, const Production* p = nullptr) {
    switch (a.type_)
    {
        case Action::Type::Shift:
            return "Shift";
        case Action::Type::Reduce:
            return "Reduce " + nonTerminalString(p->lhs_);
        case Action::Type::Accept:
            return "Accept";
        default:
            return "Error";
    }
}


SLRparser::SLRparser(
    std::vector<Production>&& p,std::unordered_map<size_t, std::unordered_map<Token, Action>>&& a,
    std::unordered_map<size_t, std::unordered_map<NonTerminal, size_t>>&& g)
    : grammar_(std::move(p)),action_(std::move(a)),goto_(std::move(g))
{}

void SLRparser::parse(const std::vector<Token>& tokens)
{
    state_stack_ = {};
    symbol_stack_.clear();

    visualizer_.printHead();

    state_stack_.push(0); // start
    size_t   pos = 0;

    while (true)
    {
        size_t state = state_stack_.top();

        if (!action_.count(state) || !action_[state].count(tokens[pos]))
        {
            std::cerr << "SYNTAX ERROR" << '\n';
            return;
        }

        Action a = action_[state][tokens[pos]];

        auto action_string = (a.type_ == Action::Type::Reduce) ?
            actionString(a, &grammar_[a.value_])
            :actionString(a);

        visualizer_.printState(stackString(symbol_stack_), inputString(tokens, pos),
                               action_string);



        switch (a.type_)
        {
            case Action::Type::Shift:
            {
                state_stack_.push(a.value_);
                symbol_stack_.push_back(tokenString(tokens[pos]));
                pos++;
                break;
            }

            case Action::Type::Reduce:
            {
                const auto& p = grammar_[a.value_];

                for (size_t i = 0, len = p.rhs_.size(); i < len; ++i)
                {
                    symbol_stack_.pop_back();
                    state_stack_.pop();
                }

                symbol_stack_.push_back(nonTerminalString(p.lhs_));
                size_t next_state = goto_[state_stack_.top()][p.lhs_];
                state_stack_.push(next_state);
                break;
            }

            case Action::Type::Accept:
            {
                return;
            }

            default:
            {
                std::cerr << "SYNTAX ERROR" << '\n';
                return;
            }
        }


    }

}
