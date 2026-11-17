User legt num fest

während num > 0 

remainder entspricht dem Rest von num / 2 (num % 2)

reversedbinary entspricht reversedbinary * 2 + remainder


#include <stdio.h>

int main() {
    int num, reversedBinary = 0, remainder;

    printf("Geben Sie eine positive ganze Zahl ein: ");
    scanf("%d", &num);

    while (num > 0) {
        remainder = num % 2;
        reversedBinary = reversedBinary * 2 + remainder;
        num /= 2;
    }

    printf("Umgekehrte binäre Darstellung: %d\n", reversedBinary);

    return 0;
}
