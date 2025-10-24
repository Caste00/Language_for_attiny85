#include "lexer.h"
#include "token.h"

Token newToken(TokenType type, char* lexeme, char* literal, int line_number) {
    Token token = {type, lexeme, literal, line_number};
    return token;
}

void printToken(Token token) {
    printf("%s %s in line: %d\n",
        token.lexeme ? token.lexeme : "null",
        token.literal ? token.literal : "null",
        token.line_number);
}

void freeToken(Token* token) {
    if (!token)     return;
    free(token->lexeme);
    free(token->literal);
    token->lexeme = NULL;
    token->literal = NULL;
}
