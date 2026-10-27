#include <stdio.h>

int main()
{
    int pin_correct = 1234;
    int pin = 0;
    int clearance = 0;
    int clearance_correct = 3;

    printf("\nBitte Pin eingeben: ");
    scanf("%d", &pin);

    printf("\nBitte Sicherheitsstufe eingeben: ");
    scanf("%d", &clearance);

    if (pin == pin_correct && clearance == clearance_correct) {

        printf("Zugriff gewährt");

    }
    else if (pin != pin_correct || clearance != clearance_correct) {

        printf("Zugriff verweigert!");
    }

    return 0;
}
