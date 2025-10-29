#include "expression.h"

Expr* newBinaryExpr(Expr* left, Token operator, Expr* right) {
    Expr* expr = malloc(sizeof(Expr));
    expr->type = EXPR_BINARY;
    expr->as.binary.left = left;
    expr->as.binary.operator = operator;
    expr->as.binary.right = right;
    return expr;
}

Expr* newUnaryExpr(Token operator, Expr* right) {
    Expr* expr = malloc(sizeof(Expr));
    expr->type = EXPR_UNARY;
    expr->as.unary.operator = operator;
    expr->as.unary.right = right;
    return expr;
}

Expr* newLiteralExpr(Value value) {
    Expr* expr = malloc(sizeof(Expr));
    expr->type = EXPR_LITERAL;
    expr->as.literal.value = value;
    return expr;
}

Expr* newGroupingExpr(Expr* expression) {
    Expr* expr = malloc(sizeof(Expr));
    expr->type = EXPR_GROUPING;
    expr->as.grouping.expression = expression;
    return expr;
}



void freeExpr(Expr* expr) {
    if (expr == NULL) return;

    switch (expr->type) {
        case EXPR_BINARY:
            freeExpr(expr->as.binary.left);
            freeExpr(expr->as.binary.right);
            break;
        case EXPR_UNARY:
            freeExpr(expr->as.unary.right);
            break;
        case EXPR_LITERAL:
            if (IS_STRING(expr->as.literal.value)) {
                free(AS_STRING(expr->as.literal.value));
            }
            break;
        case EXPR_GROUPING:
            freeExpr(expr->as.grouping.expression);
            break;
    }
}