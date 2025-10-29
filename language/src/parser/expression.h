#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../lexer/Token.h"
#include "value.h"

typedef Enum {
    EXPR_BYNARY,
    EXPR_UNARY,
    EXPR_LITERAL,
    EXPR_GROUPING
} ExprType;

typedef struct Expr Expr;

typedef struct {
    Expr* left;
    Token operator;
    Expr* right;
} ExprBinary;

typedef struct {
    Token operator;
    Expr* right;
} ExprUnary;

typedef struct {
    Value value;         // va creata la struct Value che è int, string, bool ...
} ExprLiteral;

typedef struct {
    Expr* expression;
} ExprGrouping;

struct Expr {
    ExprType type;
    union {
        ExprBinary binary;
        ExprUnary unary;
        ExprLiteral literal;
        ExprGrouping grouping;
    } as;
};


// serviranno funzioni per creare e deallocare ogni nodo come ExprBinary


#endif
