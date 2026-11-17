#include <stdio.h>

int main(void) {
    int hoehe = 5;

    for (int zeile = 1; zeile <= hoehe; zeile++) {
        // Leerzeichen vor den Sternen
        for (int s = 0; s < hoehe - zeile; s++) {
            printf(" ");
        }
        // Sterne: 1, 3, 5, 7, 9
        for (int s = 0; s < 2 * zeile - 1; s++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
