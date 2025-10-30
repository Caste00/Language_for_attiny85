#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../lexer/token.h"
#include "value.h"
#include <stdlib.h>

typedef enum {
    EXPR_BINARY,
    EXPR_UNARY,
    EXPR_LITERAL,
    EXPR_GROUPING,
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


Expr* newBinaryExpr(Expr* left, Token operator, Expr* right);
Expr* newUnaryExpr(Token operator, Expr* right);
Expr* newLiteralExpr(Value value);
Expr* newGroupingExpr(Expr* expression);
void freeExpr(Expr* expr);

#endif
