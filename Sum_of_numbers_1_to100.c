#include <stdio.h>

int main(void) {
    int count = 1;
    int summe = 0;

    while (count <= 100) {
        summe = summe + count;
        count++;
    }

    printf("%d\n", summe);

    return 0;
}
