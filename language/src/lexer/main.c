#include "dynamic_array_and_map.h"
#include "lexer.h"
#include <stdio.h>

int main() {
    TokenArray arr = initTokenArray();

    printf("size: %ld, capacity: %ld\n", arr.size, arr.capacity);
    
    for (int i = 0; i < 12; i++) {
        Token token = newToken(IMPORT, "import", "hey", i);
        pushTokenArray(&arr, token);
    }

    printTokenArray(&arr);
    printf("size: %ld, capacity: %ld\n", arr.size, arr.capacity);

    freeTokenArray(&arr);
    Token  token = newToken(IF, "if", "non so", 3);
    freeToken(&token);

    
    return 0;
}
