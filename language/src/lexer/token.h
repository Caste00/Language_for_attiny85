#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>

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
