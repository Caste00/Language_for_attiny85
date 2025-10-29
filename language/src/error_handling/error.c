#include "error.h"

void printError(int line, const char* msg) {
    fprintf("Error at line: %d: %s\n", line, msg);
}