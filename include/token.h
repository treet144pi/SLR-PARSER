#pragma once

enum class Token {
    ID,
    NUM,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    END,
    INVALID,
};

enum class NonTerminal {
    E,
    T,
    F
};
