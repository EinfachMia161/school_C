#include <stdio.h>

int main(void) {
    int a, b;
    scanf("%d\n%d", &a, &b);

    // Index 0 bleibt leer, damit woerter[1] = "one" passt
    const char *woerter[] = {"zero", "one", "two", "three", "four",
                             "five", "six", "seven", "eight", "nine"};

    for (int n = a; n <= b; n++) {
        if (n >= 1 && n <= 9) {
            printf("%s\n", woerter[n]);
        } else if (n % 2 == 0) {
            printf("even\n");
        } else {
            printf("odd\n");
        }
    }

    return 0;
}
