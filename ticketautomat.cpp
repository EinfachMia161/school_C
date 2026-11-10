#include <stdio.h>

int main()
{
    int age = 0;
    int time = 0;

    printf("\nBitte Alter eingeben: ");
    if (scanf("%d", &age) != 1 || age < 0) {
        printf("Ungueltiges Alter.\n");
        return 1;
    }

    printf("\nBitte Uhrzeit eingeben (aktuelle volle Stunde): ");
    if (scanf("%d", &time) != 1 || time < 0 || time > 23) {
        printf("Ungueltige Uhrzeit.\n");
        return 1;
    }

    if (age < 6) {
        printf("Die Fahrt ist kostenlos.\n");
        return 0;   // kostenlos -> Rabatt ist hier egal
    }
    else if (age >= 6 && age <= 17) {
        printf("Bitte ziehen Sie ein Kinderticket.\n");
    }
    else if (age >= 18 && age <= 64) {
        printf("Bitte ziehen Sie ein Erwachsenenticket.\n");
    }
    else {
        printf("Bitte ziehen Sie ein Seniorenticket.\n");
    }

    if (time >= 9 && time <= 16) {
        printf("Sie erhalten den Nebenzeit-Rabatt.\n");
    }

    return 0;
}
