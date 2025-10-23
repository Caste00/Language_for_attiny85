#include "dynamic_array_and_map.h"
#include <stdlib.h>

// KeywordEntry
KeywordEntry newKeywordEntry(char* key, TokenType value) {
    KeywordEntry entry;
    entry.key = strdup(key);
    entry.value = value;

    return entry;
}

void freeKeywordEntry(KeywordEntry* entry) {
    if (!entry)   return;
    free(entry->key);
    entry->key = NULL;
}

// KeywordMap
KeywordMap initKeywordMap() {
    KeywordMap map;
    size_t initial_capacity = 4;

    map.entries = malloc (sizeof(KeywordEntry) * initial_capacity);
    if (!map.entries) {
        perror("Error: malloc failed in initKeywordMap");
        exit(EXIT_FAILURE);
    }
    map.size = 0;
    map.capacity = initial_capacity;

    return map;
}


void pushKeywordMap(KeywordMap* map, KeywordEntry node) {
    if (map->capacity == map->size) {
        map->capacity *= 2;
        map->entries = realloc(map->entries, map->capacity * sizeof(KeywordEntry));
        if (!map->entries) {
            perror("Error: realloc failed in pushKeywordMap");
            exit(EXIT_FAILURE);
        }
    }
    map->entries[map->size++] = node;
}

void pushKeywordEntry(KeywordMap* map, char* key, TokenType value) {
    KeywordEntry entry = newKeywordEntry(key, value);
    pushKeywordMap(map, entry);
}

// qui si può ottimizzare la ricerca, per ora uso un bublesort
TokenType lookupKeyword(KeywordMap* map, char* key) {
    if (!map) {
        printf("empty map\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(key, map->entries[i].key) == 0) {
            return map->entries[i].value;
        }
    }
    return IDENTIFIER;
}

void freeKeywordMap(KeywordMap* map) {
    for (size_t i = 0; i < map->size; i++) {
        free(map->entries[i].key);
    }
    free(map->entries);
    map->entries = NULL;
    map->size = 0;
    map->capacity = 0;
}

void printKeywordMap(KeywordMap* map) {
    for (size_t i = 0; i < map->size; i++) {
        printf("%s\t", map->entries[i].key);
    }
    printf("\n");
}
