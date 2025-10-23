#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    IMPORT,
    PRINT,
    IF,
    ELSE,
    FOR,
    INT,
    STRING,
    BOOL,
    NIL,
    FUNCTION,
    RETURN,
    LEFT_PAREN, 
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE, 
    COMMA,
    DOT,
    MINUS, 
    PLUS,
    SEMICOLON, 
    SLASH,
    STAR,
    BANG, 
    BANG_EQUAL, 
    EQUAL,
    EQUAL_EQUAL, 
    GREATER,
    GREATER_EQUAL, 
    LESS,
    LESS_EQUAL, 
    AND,
    OR,
    TRUE,
    FALSE,
    END_OF_FILE
} TokenType;

typedef struct {
    TokenType type;
    char* lexeme;
    char* literal;
    int line_number;
} Token;

Token newToken(TokenType type, char* lexeme, char* literal, int line_number);
void printToken(Token token);
void freeToken(Token* token);

#endif
