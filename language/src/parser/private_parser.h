#ifndef PRIVATE_PARSER_H
#define PRIVATE_PARSER_H

#include "expression.h"
#include "../lexer/token.h"
#include "value.h"

Expr* expression();
Expr* equality();
Expr* comparison(Parser* parser);
Expr* term(Parser* parser);
Expr* factor(Parser* parser);
Expr* unary(Parser* parser);

int match(Parser* parser ,int count, ...);
int check(Parser* parser, TokenType type);
Token* advance(Parser* parser);
Token* peek(Parser* parser);
Token* previous(Parser* parser);
int isAtEnd(Parser* parser);

#endif