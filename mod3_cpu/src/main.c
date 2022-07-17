#include <stdlib.h>
#include <stdio.h>
#include <valgrind/valgrind.h>

void funcion(char *str, int i) {
    VALGRIND_PRINTF_BACKTRACE("%s: %d\n", str, i);
}

int main(int argc, char* argv[]) {
    puts("Hello world!!");
    return 0;
}
