#include <stdio.h>

int main(void) {
    int groesse = 8;

    for (int zeile = 0; zeile < groesse; zeile++) {
        for (int spalte = 0; spalte < groesse; spalte++) {
            if ((zeile + spalte) % 2 == 0) {
                printf("X ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }

    return 0;
}
