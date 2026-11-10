#include <stdio.h>

int main(void) {
    int count = 0;
    int repeat = 0;

    while (count < 100) {
        count++;

        if (count % 3 == 0 || count % 4 == 0) {
            printf("%d ", count);
            repeat++;

            if (repeat == 4) {
                printf("\n");
                repeat = 0;
            }
        }
    }

    printf("\n");
    return 0;
}
