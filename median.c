#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 128
#define VALUE_COUNT 3

static int parse_double(const char *input, double *out)
{
    char *end;
    double value = strtod(input, &end);

    if (end == input) {
        return 0;
    }

    while (*end == ' ' || *end == '\t') {
        end++;
    }

    if ((*end != '\n' && *end != '\0') || !isfinite(value)) {
        return 0;
    }

    *out = value;
    return 1;
}

static double read_double(const char *prompt)
{
    char buffer[INPUT_BUFFER_SIZE];
    double value;

    for (;;) {
        fputs(prompt, stdout);
        fflush(stdout);

        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            fputs("\nEingabe beendet.\n", stderr);
            exit(EXIT_FAILURE);
        }

        if (parse_double(buffer, &value)) {
            return value;
        }

        fputs("Ungueltige Eingabe. Bitte eine Zahl eingeben.\n", stderr);
    }
}

/* Median ohne Sortierung: max(min(a, b), min(max(a, b), c)) */
static double median_of_three(double a, double b, double c)
{
    double lo = a < b ? a : b;
    double hi = a < b ? b : a;
    double mid = hi < c ? hi : c;

    return lo > mid ? lo : mid;
}

int main(void)
{
    static const char *const prompts[VALUE_COUNT] = {
        "Bitte erste Zahl eingeben: ",
        "Bitte zweite Zahl eingeben: ",
        "Bitte dritte Zahl eingeben: ",
    };
    double values[VALUE_COUNT];

    for (size_t i = 0; i < VALUE_COUNT; i++) {
        values[i] = read_double(prompts[i]);
    }

    printf("\nMedian von %g, %g und %g: %g\n",
           values[0], values[1], values[2],
           median_of_three(values[0], values[1], values[2]));

    return EXIT_SUCCESS;
}
