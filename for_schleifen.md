## Die for-Schleife in C

### Syntax

```c
for (Initialisierung; Bedingung; Schritt) {
    // Anweisungen
}
```

### Einfaches Beispiel

```c
#include <stdio.h>

int main(void) {
    for (int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }
    return 0;
}
```

Ausgabe:
```
0
1
2
3
4
```

### Die drei Teile im Kopf

| Teil | Beispiel | Wann ausgeführt |
|---|---|---|
| **Initialisierung** | `int i = 0` | genau **einmal** vor dem Start |
| **Bedingung** | `i < 5` | **vor jedem** Durchlauf; ist sie `0` (falsch), endet die Schleife |
| **Schritt** | `i++` | **nach jedem** Durchlauf |

Ablauf: Initialisierung → Bedingung prüfen → Körper ausführen → Schritt → Bedingung prüfen → …

### Typische Anwendung: Array durchlaufen

```c
int zahlen[] = {4, 8, 15, 16, 23};
int laenge = sizeof(zahlen) / sizeof(zahlen[0]);   // = 5
int summe = 0;

for (int i = 0; i < laenge; i++) {
    summe += zahlen[i];
}
printf("Summe: %d\n", summe);   // Summe: 66
```

In C gibt es kein „for-each“ wie in Python. Du läufst immer über den **Index**.

### C-Besonderheiten

**1. Variable im Schleifenkopf (ab C99)**
`for (int i = 0; ...)` funktioniert erst ab C99. Bei sehr alten Compilern (C89) musst du `i` vorher deklarieren:
```c
int i;
for (i = 0; i < 5; i++) { ... }
```
Wird `i` im Kopf deklariert, existiert die Variable nur innerhalb der Schleife.

**2. Alle Teile sind optional**
```c
for (;;) {
    // Endlosschleife, verlassen z. B. mit break
}
```

**3. Mehrere Variablen mit dem Komma-Operator**
```c
for (int i = 0, j = 10; i < j; i++, j--) {
    printf("%d %d\n", i, j);
}
```

**4. `break` und `continue`**
```c
for (int i = 0; i < 10; i++) {
    if (i == 3) continue;   // überspringt den Rest dieses Durchlaufs
    if (i == 7) break;      // beendet die Schleife sofort
    printf("%d ", i);
}
// Ausgabe: 0 1 2 4 5 6
```

### Häufige Fehler

```c
for (int i = 0; i <= 5; i++)   // <= statt <: greift bei einem Array der Größe 5 auf zahlen[5] zu → undefiniertes Verhalten!
for (int i = 0; i < 5; i++);   // Semikolon am Ende: die Schleife hat einen leeren Körper, der Block danach läuft nur einmal
```

**Merksatz:** Ein Array der Größe `n` hat die Indizes `0` bis `n-1`. Deshalb lautet die Bedingung fast immer `i < n`.
