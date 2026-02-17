#pragma once
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>
#include "token.h"
#include "outputstates.h"

struct Action {
    enum class Type { Shift, Reduce, Accept, Error } type_;
    size_t                                           value_;
};

struct Production {
    NonTerminal              lhs_;
    std::vector<std::string> rhs_;
};

class SyntaxAnalyzer {
public:
    virtual void parse(const std::vector<Token>& tokens) = 0;
    virtual ~SyntaxAnalyzer() = default;
};


class SLRparser : public SyntaxAnalyzer {
    private:
        std::vector<Production>                                             grammar_;
        std::unordered_map<size_t, std::unordered_map<Token, Action>>       action_;
        std::unordered_map<size_t, std::unordered_map<NonTerminal, size_t>> goto_;
        std::stack<size_t>                                                  state_stack_;

    private: // for output
        std::vector<std::string> symbol_stack_;
        Visualizer               visualizer_;

    public:
        SLRparser(std::vector<Production>&& p,
                  std::unordered_map<size_t, std::unordered_map<Token, Action>>&& a,
                  std::unordered_map<size_t, std::unordered_map<NonTerminal, size_t>>&& g);
        void parse(const std::vector<Token>& tokens) override;
};

