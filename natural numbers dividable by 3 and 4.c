#include <stdio.h>

int main(void) {
    int count = 0;

    while (count < 100) {
        count++;

        if (count % 3 == 0 || count % 4 == 0) {
            printf("%d\n", count);
        }
    }

    return 0;
}
