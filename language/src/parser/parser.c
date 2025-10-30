#include "parser.h"
#include "private_parser.h"

#include <stdarg.h>

Parser* newParser(TokenArray tokenArray) {
    Parser* parser = malloc(sizeof(Parser));
    parser->current = 0;
    parser->tokens = tokenArray;
    return parser;
}

void freeParser(Parser* parser) {
    free(parser);
}

Expr* expression(Parser* parser) {
    return equality(parser);
}

Expr* equality(Parser* parser) {
    Expr* expr = comparison(parser);

    while (match(parser, 2, BANG_EQUAL, EQUAL_EQUAL)) {
        Token operator = *previous(parser);
        Expr* right = comparison(parser);
        expr = newBinaryExpr(expr, operator, right);
    }

    return expr;
}

Expr* comparison(Parser* parser) {
    Expr* expr = term(parser);

    while (match(parser, 4, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
        Token operator = *previous(parser);
        Expr* right = term(parser);
        expr = newBinaryExpr(expr, operator, right);
    }

    return expr;
}

Expr* term(Parser* parser) {
    Expr* expr = factor(parser);

    while (match(parser, 2, MINUS, PLUS)) {
        Token operator = *previous(parser);
        Expr* right = factor(parser);
        expr = newBinaryExpr(expr, operator, right);
    }

    return expr;
}

Expr* factor(Parser* parser) {
    Expr* expr = unary(parser);

    while (match(parser, SLASH, STAR)) {
        Token operator = *previous(parser);
        Expr* right = unary(parser);
        expr = newBinaryExpr(expr, operator, right);
    }

    return expr;
}

Expr* unary(Parser* parser) {
    if (match(BANG, MINUS)) {
        Token operator = *previous(parser);
        Expr* right = unary(parser);
        return newUnaryExpr(operator, right);
    }

    return primary(parser);
}

Expr* primary(Parser* parser) {
    if (match(parser, 1, FALSE))        return newLiteralExpr(makeBool(false));
    if (match(parser, 1, TRUE))         return newLiteralExpr(makeBool(true));
    if (match(parser, 1, NIL))          return newLiteralExpr(makeNil());
    if (match(parser, 1, STRING)) {
        Token* token = prevoius(parser);
        return newLiteralExpr(makeString(token->literal));
    }
    if (match(parser, 1, INT)) {
        Token* token = previous(parser);
        int value = atoi(token->literal);
        return newLiteralExpr(makeInt(value));
    }

    if (match(parser, 1, LEFT_PAREN)) {
        Expr* expr = expression(parser);
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return newGroupingExpr(expr);
    }

    // TODO: gestione errori
    return NULL;
}


int match(Parser* parser, int count, ...) {
    va_list args;
    va_start(args, count);

    for(int i = 0; i < count; i++) {
        TokenType type = va_arg(args, TokenType);
        if (check(parser, type)) {
            advance(parser);
            va_end(args);
            return 1;
        }
    }

    va_end(args);
    return 0;
}

int check(Parser* parser, TokenType type) {
    if (isAtEnd(parser))
        return 0;
    return peek(parser)->type == type;
}

Token* advance(Parser* parser) {
    if (!isAtEnd(parser)) 
        parser->current++;
    return previous(parser);
}

Token* peek(Parser* parser) {
    return &parser->tokens.data[parser->current];
}

Token* previous(Parser* parser) {
    return &parser->tokens.data[parser->current - 1];
}

int isAtEnd(Parser* parser) {
    return peek(parser)->type == EOF;
}