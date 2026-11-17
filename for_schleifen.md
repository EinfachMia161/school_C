# For-Schleifen in C

Lösungen und Erklärungen zu drei Übungsaufgaben mit `for`-Schleifen in C:

1. **Zahlen in Worten:** Zahlen eines Intervalls als englisches Wort, `even` oder `odd` ausgeben
2. **Pyramide:** eine Stern-Pyramide mit verschachtelten Schleifen zeichnen
3. **Schachbrett:** ein 8×8-Muster aus `X` und Leerzeichen erzeugen

## Inhalt

- [Die for-Schleife in C](#die-for-schleife-in-c)
- [Aufgabe 1: Zahlen in Worten](#aufgabe-1-zahlen-in-worten)
- [Aufgabe 2: Pyramide](#aufgabe-2-pyramide)
- [Aufgabe 3: Schachbrett](#aufgabe-3-schachbrett)
- [Kompilieren und Ausführen](#kompilieren-und-ausführen)
- [Häufige Fehler](#häufige-fehler)
- [Weiterführende Dokumente](#weiterführende-dokumente)

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

**Variable im Schleifenkopf.** `for (int i = 0; ...)` gibt es erst ab C99. Die Variable existiert dann nur innerhalb der Schleife.

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

**Verschachtelte Schleifen.** Eine Schleife im Körper einer anderen läuft bei **jedem** Durchlauf der äußeren komplett durch. Typisch für alles mit Zeilen und Spalten, wie in Aufgabe 2 und 3:

```c
for (int zeile = 0; zeile < 3; zeile++) {        // äußere Schleife: Zeilen
    for (int spalte = 0; spalte < 4; spalte++) { // innere Schleife: Spalten
        printf("*");
    }
    printf("\n");                                // nach jeder Zeile umbrechen
}
```

```
****
****
****
```

---

## Aufgabe 1: Zahlen in Worten

Quelle: [HackerRank – For Loop in C](https://www.hackerrank.com/challenges/for-loop-in-c/problem)

### Aufgabenstellung

Gegeben sind zwei ganze Zahlen **a** und **b**. Für jede ganze Zahl **n** im geschlossenen Intervall **[a, b]** gilt:

| Bedingung | Ausgabe |
|---|---|
| 1 ≤ n ≤ 9 | englisches Wort in Kleinbuchstaben (`one`, `two`, …, `nine`) |
| n > 9 und n gerade | `even` |
| n > 9 und n ungerade | `odd` |

**Eingabeformat:** `a` in der ersten Zeile, `b` in der zweiten.
**Einschränkungen:** 1 ≤ a ≤ b ≤ 10⁶

| Eingabe | Ausgabe |
|---|---|
| `8`<br>`11` | `eight`<br>`nine`<br>`even`<br>`odd` |

### Lösung (Aufgabe 1)

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

> Eine alternative Lösung mit `switch` steht in [switch.md](switch.md#alternative-lösung-der-aufgabe-mit-switch).

### Erklärung

**Eingabe lesen:** Das Leerzeichen in `scanf("%d %d", ...)` steht für beliebigen Leerraum, also auch für einen Zeilenumbruch. Deshalb funktioniert die Eingabe auf zwei Zeilen.

**Die Wörter als Array:** Statt neun `if`-Abfragen liegen die Wörter in einem Array von String-Zeigern. Weil Arrays bei Index 0 beginnen, steht dort ein leerer String. So entspricht `woerter[n]` direkt der Zahl `n`. Warum `const char *` und nicht `char *`, erklärt [const-char.md](const-char.md).

**Die Schleife `for (int n = a; n <= b; n++)`:**

| Teil | Bedeutung |
|---|---|
| `int n = a` | Der Zähler startet bei `a`. |
| `n <= b` | `<=` statt `<`, weil `b` selbst noch ausgegeben werden soll (geschlossenes Intervall). |
| `n++` | Nach jedem Durchlauf wird `n` um 1 erhöht. |

**Die Fallunterscheidung:** Zuerst wird `1 ≤ n ≤ 9` geprüft. Das `else if` und das `else` greifen nur noch für Zahlen ab 10. `n % 2` ist der Rest bei Division durch 2. Ist er `0`, ist die Zahl gerade.

**Ablauf für das Beispiel (a = 8, b = 11):**

| n | zutreffende Bedingung | Ausgabe |
|---|---|---|
| 8 | 1 ≤ 8 ≤ 9 | `eight` |
| 9 | 1 ≤ 9 ≤ 9 | `nine` |
| 10 | 10 % 2 == 0 | `even` |
| 11 | 11 % 2 == 1 | `odd` |
| 12 | `12 <= 11` ist falsch | Schleife endet |

---

## Aufgabe 2: Pyramide

### Aufgabenstellung

Erzeuge folgende Bildschirmausgabe mit Hilfe von for-Schleifen:

```
    *
   ***
  *****
 *******
*********
```

### Lösung (Aufgabe 2)

```c
#include <stdio.h>

int main(void) {
    int hoehe = 5;

    for (int zeile = 1; zeile <= hoehe; zeile++) {
        // Leerzeichen vor den Sternen
        for (int s = 0; s < hoehe - zeile; s++) {
            printf(" ");
        }
        // Sterne: 1, 3, 5, 7, 9
        for (int s = 0; s < 2 * zeile - 1; s++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
```

### Erklärung

Jede Zeile besteht aus zwei Teilen: **Leerzeichen** zum Einrücken, dann **Sterne**. Die Anzahl beider hängt von der Zeilennummer ab:

| Zeile | Leerzeichen `hoehe - zeile` | Sterne `2 * zeile - 1` | Ausgabe |
|:---:|:---:|:---:|---|
| 1 | 4 | 1 | `····*` |
| 2 | 3 | 3 | `···***` |
| 3 | 2 | 5 | `··*****` |
| 4 | 1 | 7 | `·*******` |
| 5 | 0 | 9 | `*********` |

(`·` steht hier für ein Leerzeichen.)

- Die **äußere Schleife** läuft über die Zeilen 1 bis 5.
- Die **erste innere Schleife** gibt die Leerzeichen aus. Ihre Anzahl sinkt pro Zeile um 1.
- Die **zweite innere Schleife** gibt die Sterne aus. Ihre Anzahl steigt pro Zeile um 2, also ungerade Zahlen: `2 * zeile - 1`.
- `printf("\n")` beendet die Zeile.

Weil die Höhe in einer Variablen steht, zeichnet `hoehe = 10` sofort eine größere Pyramide.

---

## Aufgabe 3: Schachbrett

### Aufgabenstellung

Erstelle ein Schachbrett mit einer Größe von 8×8, wobei jede Zelle entweder mit einem `X` oder einem Leerzeichen gefüllt ist:

```
X   X   X   X
  X   X   X   X
X   X   X   X
  X   X   X   X
X   X   X   X
  X   X   X   X
X   X   X   X
  X   X   X   X
```

### Lösung (Aufgabe 3)

```c
#include <stdio.h>

int main(void) {
    int groesse = 8;

    for (int zeile = 0; zeile < groesse; zeile++) {
        for (int spalte = 0; spalte < groesse; spalte++) {
            if ((zeile + spalte) % 2 == 0) {
                printf("X ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }

    return 0;
}
```

### Erklärung

Der Trick ist die Summe aus Zeile und Spalte. Auf einem Schachbrett wechselt die Farbe bei jedem Schritt nach rechts **und** bei jedem Schritt nach unten. Genau das tut auch `(zeile + spalte) % 2`:

| | Spalte 0 | Spalte 1 | Spalte 2 | Spalte 3 | … |
|---|:---:|:---:|:---:|:---:|:---:|
| **Zeile 0** | 0 → `X` | 1 → leer | 2 → `X` | 3 → leer | … |
| **Zeile 1** | 1 → leer | 2 → `X` | 3 → leer | 4 → `X` | … |
| **Zeile 2** | 2 → `X` | 3 → leer | 4 → `X` | 5 → leer | … |

- Ist die Summe **gerade**, kommt ein `X` in die Zelle, sonst bleibt sie leer.
- Die **äußere Schleife** läuft über die 8 Zeilen, die **innere** über die 8 Spalten. Insgesamt werden 8 × 8 = 64 Zellen ausgegeben.
- Jede Zelle ist **zwei Zeichen breit** (`"X "` oder `"  "`). Weil Zeichen in der Konsole etwa doppelt so hoch wie breit sind, sehen die Zellen so annähernd quadratisch aus. Mit `"X"` und `" "` wird das Brett schmaler.

---

## Kompilieren und Ausführen

| Aufgabe | Datei |
|---|---|
| 1 (Array) | [`for_loop.c`](for_loop.c) |
| 1 (switch) | [`for_loop_switch.c`](for_loop_switch.c) |
| 2 | [`for_pyramide.c`](for_pyramide.c) |
| 3 | [`for_schachbrett.c`](for_schachbrett.c) |

**Kompilieren** (GCC oder Clang):

```bash
gcc -std=c99 -Wall -Wextra for_loop.c -o for_loop
```

`-std=c99` ist nötig, falls dein Compiler standardmäßig einen älteren Standard nutzt, denn die Deklaration `int n` im Schleifenkopf gibt es erst ab C99. `-Wall -Wextra` schaltet hilfreiche Warnungen ein.

**Ausführen** mit Eingabe für Aufgabe 1 (Linux, macOS, Git Bash):

```bash
printf "8\n11\n" | ./for_loop
```

**Ausführen** mit Eingabe für Aufgabe 1 (Windows PowerShell):

```powershell
"8`n11" | .\for_loop.exe
```

Aufgabe 2 und 3 brauchen keine Eingabe, z. B. `./pyramide` bzw. `.\pyramide.exe`.

---

## Häufige Fehler

| Fehler | Folge |
|---|---|
| `n < b` statt `n <= b` | Die letzte Zahl `b` wird nicht ausgegeben. |
| `i <= laenge` beim Array | Zugriff auf `zahlen[laenge]` außerhalb des Arrays, also undefiniertes Verhalten. |
| `for (...);` mit Semikolon | Die Schleife hat einen leeren Körper, der Block danach läuft nur einmal. |
| `woerter[n]` ohne Bereichsprüfung | Für `n > 9` Zugriff außerhalb des Arrays, also undefiniertes Verhalten. |
| Bedingungen in falscher Reihenfolge | Wird zuerst auf gerade/ungerade geprüft, erscheint z. B. für 8 `even` statt `eight`. |
| `printf("\n")` in der inneren Schleife | Jedes Zeichen landet in einer eigenen Zeile. |
| `printf("\n")` vergessen | Alles erscheint in einer einzigen langen Zeile. |
| Dieselbe Zählvariable innen und außen | Die innere Schleife verändert den Zähler der äußeren, die Ausgabe wird falsch oder die Schleife endet nie. |

---

## Weiterführende Dokumente

- [const-char.md](const-char.md): Was `const char *` bedeutet und warum es für String-Arrays verwendet wird
- [switch.md](switch.md): Die `switch`-Anweisung in C und eine alternative Lösung zu Aufgabe 1

← Zurück zur [README](README.md)
