%{
#include "token.h"
%}
%option noyywrap


%%
[0-9]+        { return static_cast<int>(Token::NUM); }
[a-zA-Z]+     { return static_cast<int>(Token::ID); }
"+"           { return static_cast<int>(Token::PLUS); }
"-"           {return  static_cast<int>(Token::MINUS); }
"*"           { return static_cast<int>(Token::MUL); }
"/"           { return static_cast<int>(Token::DIV); }
"("           { return static_cast<int>(Token::LPAREN); }
")"           { return static_cast<int>(Token::RPAREN); }

<<EOF>>       { return static_cast<int>(Token::END); }
.             { return static_cast<int>(Token::INVALID); }
[ \t\n]       {}

%%
