#include "lexer.h"
#include "dynamic_array_and_map.h"

TokenArray initTokenArray() {
    TokenArray arr;
    size_t initial_capacity = 4;

    arr.data = malloc (sizeof(Token) * initial_capacity);
    if (!arr.data) {
        perror("Error: malloc failed in initTokenArray");
        exit(EXIT_FAILURE); 
    }
    arr.size = 0;
    arr.capacity = initial_capacity;

    return arr;
}

void pushTokenArray(TokenArray* arr, Token token) {
    if (arr->capacity == arr->size) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(Token));
        if (!arr->data) {
            perror("Error: realloc failed in pushTokenArray");
            exit(EXIT_FAILURE);
        }
    }
    arr->data[arr->size++] = token;
}

Token popTokenArray(TokenArray* arr) {
    if (arr->size == 0)
        exit(EXIT_FAILURE); 
    return arr->data[--arr->size];
}

void freeTokenArray(TokenArray* arr) {
    if (!arr || !arr->data) return;

    for (size_t i = 0; i < arr->size; i++) {
        freeToken(&arr->data[i]);
    }

    free(arr->data);
    arr->data = NULL;
    arr->size = arr->capacity = 0;
}

void printTokenArray(TokenArray* arr) {
    for (size_t i = 0; i < arr->size; i++) {
        printToken(arr->data[i]);
    }
}
