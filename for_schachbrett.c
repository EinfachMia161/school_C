#include <stdio.h>

int main(void) {
    int feld = 1;   // 1 = "X", 0 = leer

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (feld == 1) {
                printf("X ");
                feld--;
            } else {
                printf("  ");
                feld++;
            }
        }
        printf("\n");

        // nächste Zeile mit dem anderen Feld beginnen
        if (feld == 1) {
            feld--;
        } else {
            feld++;
        }
    }

    return 0;
}
