#ifndef DYNAMIC_ARRAY_AND_MAP_H
#define DYNAMIC_ARRAY_AND_MAP_H

#include <stdlib.h>
#include "lexer.h"

// dynamic array of Token
typedef struct {
    Token* data;
    size_t size;
    size_t capacity;
} TokenArray;

TokenArray initTokenArray();
void pushTokenArray(TokenArray* arr, Token token);
Token popTokenArray(TokenArray* arr);
void freeTokenArray(TokenArray* arr);
void printTokenArray(TokenArray* arr);

// map of string: TokenType
typedef struct {
    char* key;
    TokenType value;
} KeywordEntry;

typedef struct {
    KeywordEntry* entries;
    size_t size;
    size_t capacity;
} KeywordMap;

KeywordEntry newKeywordEntry(char* key, TokenType value);
void freeKeywordEntry(KeywordEntry* node);

KeywordMap initKeywordMap();
void pushKeywordMap(KeywordMap* map, KeywordEntry node);
void pushKeywordEntry(KeywordMap *map, char* key, TokenType value);
TokenType lookupKeyword(KeywordMap* map, char* key);
void freeKeywordMap(KeywordMap* map);
void printKeywordMap(KeywordMap* map);


#endif
