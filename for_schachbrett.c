#include <stdio.h>

int main(void) {
    // Das Brett besteht aus zwei Zeilen, die sich 4-mal wiederholen.
    // Jedes String-Literal ist ein Feld: "X " = voll, "  " = leer.
    for (int i = 0; i < 4; i++) {
        printf("X " "  " "X " "  " "X " "  " "X " "  " "\n");
        printf("  " "X " "  " "X " "  " "X " "  " "X " "\n");
    }
    return 0;
}
