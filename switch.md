# Die `switch`-Anweisung in C

`switch` wählt anhand eines **ganzzahligen Werts** einen von mehreren Codeblöcken aus. Es ist eine übersichtliche Alternative zu langen `if`-/`else if`-Ketten, die immer dieselbe Variable mit festen Werten vergleichen.

## Inhalt

- [Syntax](#syntax)
- [Einfaches Beispiel](#einfaches-beispiel)
- [Ablauf](#ablauf)
- [Regeln für `case`](#regeln-für-case)
- [`break` und Fall-through](#break-und-fall-through)
- [`default`](#default)
- [Variablen in einem `case`](#variablen-in-einem-case)
- [`switch` in einer Schleife: Achtung bei `break`](#switch-in-einer-schleife-achtung-bei-break)
- [Alternative Lösung der Aufgabe mit `switch`](#alternative-lösung-der-aufgabe-mit-switch)
- [`switch` oder `if`?](#switch-oder-if)
- [Häufige Fehler](#häufige-fehler)

---

## Syntax

```c
switch (Ausdruck) {
    case Konstante_1:
        Anweisungen;
        break;
    case Konstante_2:
        Anweisungen;
        break;
    default:
        Anweisungen;
        break;
}
```

---

## Einfaches Beispiel

```c
#include <stdio.h>

int main(void) {
    int tag = 3;

    switch (tag) {
        case 1:
            printf("Montag\n");
            break;
        case 2:
            printf("Dienstag\n");
            break;
        case 3:
            printf("Mittwoch\n");
            break;
        default:
            printf("Unbekannter Tag\n");
            break;
    }

    return 0;
}
```

Ausgabe:

```
Mittwoch
```

---

## Ablauf

1. Der Ausdruck in `switch (...)` wird **einmal** ausgewertet.
2. Das Programm **springt** zum `case` mit dem passenden Wert.
3. Ab dort laufen die Anweisungen der Reihe nach, **bis ein `break`** oder das Ende des `switch` erreicht ist.
4. Passt kein `case`, springt das Programm zu `default`. Gibt es kein `default`, passiert nichts.

Ein `case` ist also nur eine **Sprungmarke**, kein abgeschlossener Block. Das ist wichtig für das Verständnis von Fall-through.

---

## Regeln für `case`

| Regel | Beispiel |
|---|---|
| Der `switch`-Ausdruck muss **ganzzahlig** sein (`int`, `char`, `long`, `enum`, …). | `switch (n)` ✅ |
| `float`/`double` sind **nicht** erlaubt. | `switch (3.5)` ❌ |
| Strings sind **nicht** erlaubt. | `switch ("abc")` ❌, dafür `strcmp` mit `if` verwenden |
| `case`-Werte müssen **konstante Ausdrücke** sein. | `case 5:` ✅, `case 'a':` ✅, `case 2 * 3:` ✅ |
| Variablen als `case`-Wert sind **nicht** erlaubt. | `case x:` ❌ |
| Jeder `case`-Wert darf nur **einmal** vorkommen. | zweimal `case 1:` ❌ |
| Bereiche wie `1...9` gibt es im Standard-C **nicht**. | Das ist eine GCC-Erweiterung, also nicht portabel. |

`char` funktioniert, weil Zeichen in C ganze Zahlen sind:

```c
char op = '+';

switch (op) {
    case '+': printf("Addition\n");       break;
    case '-': printf("Subtraktion\n");    break;
    case '*': printf("Multiplikation\n"); break;
    case '/': printf("Division\n");       break;
    default:  printf("Unbekannt\n");      break;
}
```

---

## `break` und Fall-through

Ohne `break` läuft das Programm **in den nächsten `case` weiter**. Das nennt man **Fall-through**.

### Unbeabsichtigt (häufiger Fehler)

```c
int x = 1;

switch (x) {
    case 1:
        printf("eins\n");
    case 2:
        printf("zwei\n");
    case 3:
        printf("drei\n");
}
```

Ausgabe:

```
eins
zwei
drei
```

### Beabsichtigt: mehrere Werte, gleicher Code

```c
int monat = 4;

switch (monat) {
    case 12:
    case 1:
    case 2:
        printf("Winter\n");
        break;
    case 3:
    case 4:
    case 5:
        printf("Frühling\n");
        break;
    case 6:
    case 7:
    case 8:
        printf("Sommer\n");
        break;
    case 9:
    case 10:
    case 11:
        printf("Herbst\n");
        break;
    default:
        printf("Ungültiger Monat\n");
        break;
}
```

Ausgabe: `Frühling`

Wenn Fall-through **mit** Code dazwischen gewollt ist, schreib einen Kommentar dazu, damit Leser (und Compiler-Warnungen wie `-Wimplicit-fallthrough`) wissen, dass es Absicht ist:

```c
case 1:
    vorbereiten();
    /* fall through */
case 2:
    ausfuehren();
    break;
```

---

## `default`

- `default` greift, wenn **kein** `case` passt.
- Es ist optional, aber meistens sinnvoll, z. B. für ungültige Eingaben.
- Es darf an beliebiger Stelle stehen, üblich ist das Ende.
- Ein `break` nach dem letzten Zweig ist technisch nicht nötig. Viele schreiben es trotzdem, damit später ergänzte Zweige nicht versehentlich durchfallen.

---

## Variablen in einem `case`

Vor **C23** darf laut Standard direkt nach einer `case`-Marke **keine Deklaration** stehen. Ältere Compiler melden einen Fehler. Neuere GCC-Versionen akzeptieren es stillschweigend und warnen erst mit `-pedantic`. Portabel ist es also nicht:

```c
switch (n) {
    case 1:
        int y = 5;      // vor C23 nicht erlaubt
        printf("%d\n", y);
        break;
}
```

Lösung: den Zweig in **geschweifte Klammern** setzen. Dann ist die Variable außerdem nur in diesem Zweig gültig.

```c
switch (n) {
    case 1: {
        int y = 5;      // OK
        printf("%d\n", y);
        break;
    }
}
```

---

## `switch` in einer Schleife: Achtung bei `break`

Ein `break` innerhalb eines `switch` beendet **nur den `switch`**, nicht die umgebende Schleife.

```c
for (int i = 0; i < 5; i++) {
    switch (i) {
        case 2:
            break;          // verlässt nur den switch, die Schleife läuft weiter
        default:
            printf("%d ", i);
            break;
    }
}
// Ausgabe: 0 1 3 4
```

| Ziel | Anweisung im `switch` |
|---|---|
| nur den `switch` verlassen | `break;` |
| zum nächsten Schleifendurchlauf springen | `continue;` (bezieht sich auf die Schleife) |
| die ganze Schleife beenden | Flag-Variable setzen und in der Bedingung prüfen, oder `return` bzw. `goto` |

---

## Alternative Lösung der Aufgabe mit `switch`

Die Aufgabe aus [for_schleifen.md](for_schleifen.md#aufgabe-1-zahlen-in-worten): Für jede Zahl `n` in `[a, b]` soll für 1–9 das englische Wort ausgegeben werden, sonst `even` oder `odd`.

```c
#include <stdio.h>

int main(void) {
    int a, b;
    scanf("%d %d", &a, &b);

    for (int n = a; n <= b; n++) {
        switch (n) {
            case 1: printf("one\n");   break;
            case 2: printf("two\n");   break;
            case 3: printf("three\n"); break;
            case 4: printf("four\n");  break;
            case 5: printf("five\n");  break;
            case 6: printf("six\n");   break;
            case 7: printf("seven\n"); break;
            case 8: printf("eight\n"); break;
            case 9: printf("nine\n");  break;
            default:
                if (n % 2 == 0) {
                    printf("even\n");
                } else {
                    printf("odd\n");
                }
                break;
        }
    }

    return 0;
}
```

### Erklärung

- Für jedes `n` springt der `switch` direkt zum passenden `case`.
- Die Zahlen 1 bis 9 haben jeweils einen eigenen `case` mit `break`.
- Alle anderen Zahlen landen in `default`. Dort entscheidet `n % 2`, ob `even` oder `odd` ausgegeben wird.
- Die `break`-Anweisungen verlassen nur den `switch`. Die `for`-Schleife läuft danach normal mit dem nächsten `n` weiter.
- `default` würde auch Zahlen kleiner als 1 erfassen. Laut Aufgabe gilt aber `a ≥ 1`, daher kommt das nicht vor.

### Vergleich mit der Array-Lösung

| | Array mit `const char *` | `switch` |
|---|---|---|
| Codelänge | kürzer | länger (ein `case` pro Zahl) |
| Lesbarkeit | kompakt, aber Index-Trick nötig | sehr direkt, jeder Fall sichtbar |
| Erweiterbarkeit | neues Wort ins Array eintragen | neuen `case` schreiben |
| Gefahr | Zugriff außerhalb des Arrays, wenn die Bereichsprüfung fehlt | vergessenes `break` |

Beide Lösungen sind korrekt. Die Array-Variante steht in [for_schleifen.md](for_schleifen.md#lösung-aufgabe-1), `const char *` wird in [const-char.md](const-char.md) erklärt.

---

## `switch` oder `if`?

| Situation | Besser |
|---|---|
| Eine Variable wird mit vielen **festen Werten** verglichen | `switch` |
| **Bereiche** (`n > 9`, `x < 0.5`) | `if` |
| **Kommazahlen** oder **Strings** | `if` |
| Bedingungen mit **mehreren Variablen** (`a > b && c == 0`) | `if` |
| Mehrere Werte führen zum **gleichen** Code | `switch` mit Fall-through |

---

## Häufige Fehler

| Fehler | Folge |
|---|---|
| `break` vergessen | Code der folgenden `case`-Zweige läuft ungewollt mit. |
| `case x:` mit Variable | Compiler-Fehler, nur Konstanten sind erlaubt. |
| `switch` mit String oder `double` | Compiler-Fehler. |
| Deklaration direkt nach `case` (vor C23) | Nicht standardkonform, ältere Compiler melden einen Fehler. Block `{ }` verwenden. |
| `break` soll die Schleife beenden | Beendet nur den `switch`, die Schleife läuft weiter. |
| `case 1, 2:` | Ist nicht die gewünschte Mehrfachauswahl. Stattdessen `case 1: case 2:` schreiben. |

← Zurück zu [for_schleifen.md](for_schleifen.md)
