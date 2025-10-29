#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef enum {
    VAL_INT,
    VAL_BOOL,
    VAL_STRING,
    VAL_NIL
} ValueType;

typedef struct {
    ValueType type;
    union {
        int integer;
        bool boolean;
        char* string;       // va allocata dinamicamente
    } as;
} Value;

// helper macro per accedere in modo sicuro
#define IS_INT(v)   ((v).type == VAL_INT)
#define IS_BOOL(v)   ((v).type == VAL_BOOL)
#define IS_STRING(v) ((v).type == VAL_STRING)
#define IS_NIL(v)    ((v).type == VAL_NIL)

#define AS_INT(v)    ((v).as.integer)
#define AS_BOOL(v)   ((v).as.boolean)
#define AS_STRING(v) ((v).as.string)

// funzioni di costruzione:
static inline Value makeInt(int i) {
    Value v;
    v.type = VAL_INT;
    v.as.integer = i;
    return v;
}

static inline Value makeBool(bool b) {
    Value v;
    v.type = VAL_BOOL;
    v.as.boolean = b;
    return v;
}

static inline Value makeString(const char* s) {
    Value v;
    v.type = VAL_STRING;
    v.as.string = strdup(s);
    return v;
}

static inline Value makeNil(void) {
    Value v;
    v.type = VAL_NIL;
    return v;
}

#endif

/*
ExprLiteral lit;
lit.value = makeInt(42);

ExprLiteral lit2;
lit2.value = makeString("ciao");
*/
