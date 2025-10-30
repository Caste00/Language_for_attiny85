#ifndef PARSER_H
#define PARSER_H

#include "../lexer/dynamic_array_and_map.h"
#include "../lexer/token.h"
#include "expression.h"

typedef struct {
    TokenArray tokens;
    int current;
} Parser;

Parser* newParser();

#endif