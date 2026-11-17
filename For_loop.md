# For Loop in C

Lösung und Erklärung zur Programmieraufgabe **„For Loop in C“**: Zahlen eines Intervalls durchlaufen und je nach Wert als englisches Wort, `even` oder `odd` ausgeben.

## Inhalt

- [Aufgabe](#aufgabe)
- [Lösung](#lösung)
- [Erklärung](#erklärung)
- [Kompilieren und Ausführen](#kompilieren-und-ausführen)
- [Die for-Schleife in C](#die-for-schleife-in-c)
- [Häufige Fehler](#häufige-fehler)
- [Weiterführende Dokumente](#weiterführende-dokumente)

---

## Aufgabe

Gegeben sind zwei ganze Zahlen **a** und **b**. Für jede ganze Zahl **n** im geschlossenen Intervall **[a, b]** gilt:

| Bedingung | Ausgabe |
|---|---|
| 1 ≤ n ≤ 9 | englisches Wort in Kleinbuchstaben (`one`, `two`, …, `nine`) |
| n > 9 und n gerade | `even` |
| n > 9 und n ungerade | `odd` |

**Eingabeformat**

```
a
b
```

**Einschränkungen:** 1 ≤ a ≤ b ≤ 10⁶

**Beispiel**

Eingabe:

```
8
11
```

Ausgabe:

```
eight
nine
even
odd
```

---

## Lösung

```c
#include <stdio.h>

int main(void) {
    int a, b;
    scanf("%d %d", &a, &b);

    // Index 0 bleibt leer, damit woerter[1] = "one" passt
    const char *woerter[] = {"", "one", "two", "three", "four",
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
```

> Eine alternative Lösung mit `switch` steht in [switch.md](switch.md).

---

## Erklärung

### 1. Eingabe lesen

```c
scanf("%d %d", &a, &b);
```

Das Leerzeichen im Formatstring steht für beliebigen Leerraum, also auch für einen Zeilenumbruch. Deshalb funktioniert die Eingabe auf zwei Zeilen.

### 2. Die Wörter als Array

```c
const char *woerter[] = {"", "one", "two", ...};
```

Statt neun `if`-Abfragen liegen die Wörter in einem Array von String-Zeigern. Weil Arrays bei Index 0 beginnen, steht dort ein leerer String. So entspricht `woerter[n]` direkt der Zahl `n`.

Warum `const char *` und nicht `char *`? Das erklärt [const-char.md](const-char.md).

### 3. Die Schleife

```c
for (int n = a; n <= b; n++)
```

| Teil | Bedeutung |
|---|---|
| `int n = a` | Der Zähler startet bei `a`. |
| `n <= b` | `<=` statt `<`, weil `b` selbst noch ausgegeben werden soll (geschlossenes Intervall). |
| `n++` | Nach jedem Durchlauf wird `n` um 1 erhöht. |

### 4. Die Fallunterscheidung

- Zuerst wird `1 ≤ n ≤ 9` geprüft. Dann gibt das Programm das passende Wort aus.
- Das `else if` und das `else` greifen nur noch für Zahlen ab 10.
- `n % 2` ist der Rest bei Division durch 2. Ist er `0`, ist die Zahl gerade.

### 5. Ablauf für das Beispiel (a = 8, b = 11)

| n | zutreffende Bedingung | Ausgabe |
|---|---|---|
| 8 | 1 ≤ 8 ≤ 9 | `eight` |
| 9 | 1 ≤ 9 ≤ 9 | `nine` |
| 10 | 10 % 2 == 0 | `even` |
| 11 | 11 % 2 == 1 | `odd` |
| 12 | `12 <= 11` ist falsch | Schleife endet |

---

## Kompilieren und Ausführen

Speichere den Code als `for_loop.c`.

**Kompilieren** (GCC oder Clang):

```bash
gcc -std=c99 -Wall -Wextra -o for_loop for_loop.c
```

`-std=c99` ist nötig, falls dein Compiler standardmäßig einen älteren Standard nutzt, denn die Deklaration `int n` im Schleifenkopf gibt es erst ab C99.

**Ausführen** (Linux, macOS, Git Bash):

```bash
printf "8\n11\n" | ./for_loop
```

**Ausführen** (Windows PowerShell):

```powershell
"8`n11" | .\for_loop.exe
```

---

## Die for-Schleife in C

### Syntax

```c
for (Ausdruck_1; Ausdruck_2; Ausdruck_3) {
    Anweisungen;
}
```

| Ausdruck | Aufgabe | Wann ausgeführt |
|---|---|---|
| `Ausdruck_1` | Initialisierung | genau einmal vor dem Start |
| `Ausdruck_2` | Abbruchbedingung | vor jedem Durchlauf; ist das Ergebnis `0` (falsch), endet die Schleife |
| `Ausdruck_3` | Aktualisierung | nach jedem Durchlauf |

### Ablauf

```
        ┌──────────────────┐
        │  Initialisierung │
        └────────┬─────────┘
                 ▼
        ┌──────────────────┐   falsch
   ┌───►│ Bedingung prüfen ├──────────► Ende
   │    └────────┬─────────┘
   │             │ wahr
   │             ▼
   │    ┌──────────────────┐
   │    │ Schleifenkörper  │
   │    └────────┬─────────┘
   │             ▼
   │    ┌──────────────────┐
   └────┤  Aktualisierung  │
        └──────────────────┘
```

### Besonderheiten in C

**Alle drei Ausdrücke sind optional.** Ohne Bedingung läuft die Schleife endlos:

```c
for (;;) {
    // läuft, bis break oder return erreicht wird
}
```

**Mehrere Variablen mit dem Komma-Operator:**

```c
for (int i = 0, j = 10; i < j; i++, j--) {
    printf("%d %d\n", i, j);
}
```

**`break` und `continue`:**

```c
for (int i = 0; i < 10; i++) {
    if (i == 3) continue;   // Rest dieses Durchlaufs überspringen
    if (i == 7) break;      // Schleife sofort beenden
    printf("%d ", i);
}
// Ausgabe: 0 1 2 4 5 6
```

**Arrays durchlaufen.** C kennt kein „for-each“, man läuft immer über den Index:

```c
int zahlen[] = {4, 8, 15, 16, 23};
int laenge = sizeof(zahlen) / sizeof(zahlen[0]);

for (int i = 0; i < laenge; i++) {
    printf("%d\n", zahlen[i]);
}
```

---

## Häufige Fehler

| Fehler | Folge |
|---|---|
| `n < b` statt `n <= b` | Die letzte Zahl `b` wird nicht ausgegeben. |
| `i <= laenge` beim Array | Zugriff auf `zahlen[laenge]` außerhalb des Arrays, also undefiniertes Verhalten. |
| `for (...);` mit Semikolon | Die Schleife hat einen leeren Körper, der Block danach läuft nur einmal. |
| `woerter[n]` ohne Bereichsprüfung | Für `n > 9` Zugriff außerhalb des Arrays, also undefiniertes Verhalten. |
| Bedingungen in falscher Reihenfolge | Wird zuerst auf gerade/ungerade geprüft, erscheint z. B. für 8 `even` statt `eight`. |

---

## Weiterführende Dokumente

- [const-char.md](const-char.md): Was `const char *` bedeutet und warum es für String-Arrays verwendet wird
- [switch.md](switch.md): Die `switch`-Anweisung in C und eine alternative Lösung dieser Aufgabe
