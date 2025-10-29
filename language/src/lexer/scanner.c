#include "lexer.h"
#include "token.h"
#include "dynamic_array_and_map.h"
#include "../error_handling/error.h"

/* Miglioramenti possibili: 
 * - incapsulare le variabili globali in una struct
*/

char* source;
TokenArray tokens;
int start = 0;
int current = 0;
int line = 1;
KeywordMap keyword;


void initKeywords() {
    keyword = initKeywordMap();

    pushKeywordEntry(&keyword, "and", AND);
    pushKeywordEntry(&keyword, "if", IF);
    pushKeywordEntry(&keyword, "else", ELSE);
    pushKeywordEntry(&keyword, "for", FOR);
    pushKeywordEntry(&keyword, "false", FALSE);
    pushKeywordEntry(&keyword, "true", TRUE);
    pushKeywordEntry(&keyword, "nil", NIL);
    pushKeywordEntry(&keyword, "fun", FUNCTION);
    pushKeywordEntry(&keyword, "print", PRINT);
    pushKeywordEntry(&keyword, "or", OR);
    pushKeywordEntry(&keyword, "return", RETURN);
    pushKeywordEntry(&keyword, "bool", BOOL);
}

void initScanner(const char* src) {
    initKeywords();
    tokens = initTokenArray();
    source = strdup(src);
}

int isAtEnd() {
    return current >= strlen(source);
}

char advance() {
    return source[current++];
}

char peek() {
    if (isAtEnd()) 
        return '\0';
    return source[current];
}

char peekNext() {
    if (current + 1 >= strlen(source))
        return '\0';
    return source[current + 1];
}

int match(char expected) {
    if (isAtEnd() || source[current] != expected) {
        return 0;
    }
    current++;
    return 1;
}

char* substring(const char* src, int start, int end) {
    int length = end - start;
    if (length <= 0) {
        perror("Error: end must be greater than start");
        exit(EXIT_FAILURE);
    }
    char* result = malloc(length + 1);
    if (!result) {
        perror("Error: malloc failed in substring");
        exit(EXIT_FAILURE);
    }
    strncpy(result, src + start, length);
    result[length] = '\0';
    return result;
}

void addToken(TokenType type, char* literal) {
    char* text = substring(source, start, current);
    Token token = newToken(type, text, literal, line);
    pushTokenArray(&tokens, token);
}

void string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') 
            line++;
        advance();
    }

    if (isAtEnd()) {
        printError(line, "unterminated string");
        return;
    }

    advance();

    char* value = substring(source, start + 1, current - 1);
    addToken(STRING, value);
}

int isDigit(char c){
    return c >= '0' && c <= '9';
}

int isAlpha(char c) {
    return  (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_';
}

int isAlphaNumeric(char c) {
    return isDigit(c) || isAlpha(c);
}

void number() {
    while (isDigit(peek())) 
        advance();
    addToken(INT, substring(source, start, current));
}

void identifier() {
    while (isAlphaNumeric(peek())) 
        advance();

    char* text = substring(source, start, current);
    TokenType type = lookupKeyword(&keyword, text);
    addToken(type, NULL);
}

void scanToken() {
    char c = advance();
    switch (c) {
        case '(':   addToken(LEFT_PAREN, NULL); break;
        case ')':   addToken(RIGHT_PAREN, NULL); break;
        case '{':   addToken(LEFT_BRACE, NULL); break;
        case '}':   addToken(RIGHT_BRACE, NULL); break;
        case ',':   addToken(COMMA, NULL); break;
        case '.':   addToken(DOT, NULL); break;
        case '-':   addToken(MINUS, NULL); break;
        case '+':   addToken(PLUS, NULL); break;
        case ';':   addToken(SEMICOLON, NULL); break;
        case '*':   addToken(STAR, NULL); break;
        case '!':   addToken(match('=') ? BANG_EQUAL : BANG, NULL); break;
        case '=':   addToken(match('=') ? EQUAL_EQUAL : EQUAL, NULL); break;
        case '<':   addToken(match('=') ? LESS_EQUAL : LESS, NULL); break;
        case '>':   addToken(match('=') ? GREATER_EQUAL : GREATER, NULL); break;
        case '/': 
                    if (match('/')) {
                        while (peek() != '\n' && !isAtEnd())
                            advance();
                    } else {
                        addToken(SLASH, NULL);
                    }
                        break;
        case ' ':
        case '\r':
        case '\t':  break;
        case '\n':  line++; break;
        case '"':   string(); break;

        default: // gestione errori ancora da implementare, creazione di una funzione apposita
                    if (isDigit(c)) {
                        number();
                    } else if (isAlpha(c)) {
                        identifier();
                    } else {
                        printError(line, "unexpected character");
                        break;
                    }
    }
}

void scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    Token token = newToken(END_OF_FILE, "", NULL, line);
    pushTokenArray(&tokens, token);
}

void freeScanner() {
    free(source);
    freeTokenArray(&tokens);
    freeKeywordMap(&keyword);
}