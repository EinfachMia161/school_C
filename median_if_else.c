#include <stdio.h>

int main()
{
    double a = 0;
    double b = 0;
    double c = 0;
    double median = 0;
    char rest;

    // Erste Zahl einlesen
    printf("\nBitte erste Zahl eingeben: ");

    while (1)
    {
        // Pruefen ob eine Zahl eingegeben wurde
        if (scanf("%lf%c", &a, &rest) != 2 || rest != '\n')
        {
            printf("\nUngueltige Eingabe!");
            printf("\nBitte erste Zahl erneut eingeben: ");

            while (getchar() != '\n');

            continue;
        }

        break;
    }

    // Zweite Zahl einlesen
    printf("\nBitte zweite Zahl eingeben: ");

    while (1)
    {
        if (scanf("%lf%c", &b, &rest) != 2 || rest != '\n')
        {
            printf("\nUngueltige Eingabe!");
            printf("\nBitte zweite Zahl erneut eingeben: ");

            while (getchar() != '\n');

            continue;
        }

        break;
    }

    // Dritte Zahl einlesen
    printf("\nBitte dritte Zahl eingeben: ");

    while (1)
    {
        if (scanf("%lf%c", &c, &rest) != 2 || rest != '\n')
        {
            printf("\nUngueltige Eingabe!");
            printf("\nBitte dritte Zahl erneut eingeben: ");

            while (getchar() != '\n');

            continue;
        }

        break;
    }

    // Median bestimmen
    // Die Zahl in der Mitte ist groesser oder gleich der einen
    // und kleiner oder gleich der anderen Zahl
    if ((a >= b && a <= c) || (a <= b && a >= c))
    {
        median = a;
    }
    else if ((b >= a && b <= c) || (b <= a && b >= c))
    {
        median = b;
    }
    else
    {
        median = c;
    }

    // Median ausgeben
    printf("\nMedian: %g\n", median);

    return 0;
}
