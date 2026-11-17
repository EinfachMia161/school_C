# `const char *` in C

Dieses Dokument erklärt die Zeile aus der [Lösung zu Aufgabe 1](for_schleifen.md#lösung-aufgabe-1):

```c
const char *woerter[] = {"", "one", "two", "three", "four",
                         "five", "six", "seven", "eight", "nine"};
```

## Inhalt

- [Strings in C](#strings-in-c)
- [Was `const` bedeutet](#was-const-bedeutet)
- [Die vier Varianten von const und Zeiger](#die-vier-varianten-von-const-und-zeiger)
- [Lesetrick: von rechts nach links](#lesetrick-von-rechts-nach-links)
- [Warum `const char *` für String-Literale](#warum-const-char--für-string-literale)
- [Arrays von Strings](#arrays-von-strings)
- [`const` bei Funktionsparametern](#const-bei-funktionsparametern)
- [Und `const const char`?](#und-const-const-char)
- [Zusammenfassung](#zusammenfassung)

---

## Strings in C

C hat keinen eigenen String-Typ. Ein String ist eine Folge von `char`-Werten, die mit dem Nullzeichen `'\0'` endet.

```c
"one"   // liegt im Speicher als:  'o' 'n' 'e' '\0'
```

Ein **String-Literal** wie `"one"` wird vom Compiler in einem festen Speicherbereich abgelegt, der oft schreibgeschützt ist. Im Code verwendet man meistens einen **Zeiger** auf das erste Zeichen:

```c
const char *wort = "one";
//  wort ──► 'o' 'n' 'e' '\0'
```

---

## Was `const` bedeutet

`const` heißt: **Dieser Wert darf über diesen Namen nicht verändert werden.** Der Compiler meldet einen Fehler, wenn du es trotzdem versuchst.

```c
const int x = 5;
x = 6;              // Fehler: x ist const
```

Bei Zeigern gibt es zwei Dinge, die konstant sein können:

1. **die Daten**, auf die der Zeiger zeigt
2. **der Zeiger selbst**, also wohin er zeigt

Wo `const` steht, entscheidet, welches von beiden gemeint ist.

---

## Die vier Varianten von const und Zeiger

| Deklaration | Zeichen ändern (`*p = 'X'`) | Zeiger umbiegen (`p = andere`) |
|---|:---:|:---:|
| `char *p` | ✅ | ✅ |
| `const char *p` | ❌ | ✅ |
| `char * const p` | ✅ | ❌ |
| `const char * const p` | ❌ | ❌ |

`char const *p` ist identisch mit `const char *p`. Entscheidend ist nur, ob `const` **links oder rechts vom `*`** steht.

### Beispiele

```c
char puffer[] = "abc";
char anderer[] = "xyz";

// 1) Zeiger auf konstante Zeichen
const char *p1 = puffer;
p1[0] = 'X';        // Fehler: Zeichen sind über p1 schreibgeschützt
p1 = anderer;       // OK: p1 darf woanders hinzeigen

// 2) Konstanter Zeiger auf veränderbare Zeichen
char * const p2 = puffer;
p2[0] = 'X';        // OK: Zeichen dürfen geändert werden
p2 = anderer;       // Fehler: p2 selbst ist konstant

// 3) Beides konstant
const char * const p3 = puffer;
p3[0] = 'X';        // Fehler
p3 = anderer;       // Fehler
```

Hinweis zu 1): `puffer` selbst ist nicht `const`. Über den Namen `puffer` dürfen die Zeichen weiterhin geändert werden, nur über `p1` nicht.

---

## Lesetrick: von rechts nach links

Lies die Deklaration vom Variablennamen aus **nach links**:

```
const char *p              →  p ist ein Zeiger auf char, der const ist
char * const p             →  p ist ein const Zeiger auf char
const char * const p       →  p ist ein const Zeiger auf const char
const char *woerter[]      →  woerter ist ein Array von Zeigern auf const char
```

---

## Warum `const char *` für String-Literale

Ein String-Literal zu verändern ist in C **undefiniertes Verhalten**. Meistens stürzt das Programm ab, weil das Literal in schreibgeschütztem Speicher liegt.

```c
char *s = "hallo";   // erlaubt der Compiler (meist ohne Warnung)
s[0] = 'H';          // undefiniertes Verhalten, oft Absturz
```

```c
const char *s = "hallo";
s[0] = 'H';          // Compiler-Fehler, der Fehler fällt sofort auf
```

Mit `const char *` findet also der **Compiler** den Fehler, nicht erst das laufende Programm.

> In C hat ein String-Literal formal den Typ `char[N]` und nicht `const char[N]`. Deshalb erlaubt C `char *s = "..."`. In C++ ist das nicht erlaubt. Mit GCC zeigt die Option `-Wwrite-strings` hier eine Warnung an.

### Wenn du den String ändern willst

Dann brauchst du ein **eigenes Array**. Das Literal wird beim Anlegen hineinkopiert:

```c
char s[] = "hallo";  // Array mit 6 Zeichen, eine veränderbare Kopie
s[0] = 'H';          // OK
```

| | `const char *s = "hallo";` | `char s[] = "hallo";` |
|---|---|---|
| Was ist `s`? | Zeiger auf das Literal | eigenes Array (Kopie) |
| Inhalt änderbar? | nein | ja |
| `sizeof(s)` | Größe eines Zeigers (z. B. 8) | 6 (5 Zeichen + `'\0'`) |
| `s` umbiegbar? | ja | nein (Arrays sind nicht zuweisbar) |

---

## Arrays von Strings

### Variante 1: Array von Zeigern (wie in der Lösung)

```c
const char *woerter[] = {"", "one", "two", "three"};
```

```
woerter[0] ──► '\0'
woerter[1] ──► 'o' 'n' 'e' '\0'
woerter[2] ──► 't' 'w' 'o' '\0'
woerter[3] ──► 't' 'h' 'r' 'e' 'e' '\0'
```

- Jedes Element ist ein Zeiger. Die Strings dürfen unterschiedlich lang sein.
- Die Strings selbst sind schreibgeschützt.
- Anzahl der Elemente: `sizeof(woerter) / sizeof(woerter[0])`.

Soll auch das Array selbst unveränderlich sein, also kein `woerter[1] = "eins";` möglich, schreibst du:

```c
const char * const woerter[] = {"", "one", "two", "three"};
```

### Variante 2: Zweidimensionales char-Array

```c
char woerter[][6] = {"", "one", "two", "three"};
```

```
woerter[0]:  '\0' '\0' '\0' '\0' '\0' '\0'
woerter[1]:  'o'  'n'  'e'  '\0' '\0' '\0'
woerter[2]:  't'  'w'  'o'  '\0' '\0' '\0'
woerter[3]:  't'  'h'  'r'  'e'  'e'  '\0'
```

Nicht belegte Stellen werden automatisch mit `'\0'` aufgefüllt.

- Jede Zeile ist gleich lang, nämlich der längste String plus `'\0'`. Das kostet Platz.
- Die Zeichen sind veränderbar: `woerter[1][0] = 'O';` ist erlaubt.

Für feste Texte wie in der Aufgabe ist **Variante 1 mit `const char *`** die übliche Wahl.

---

## `const` bei Funktionsparametern

`const` dient auch als **Versprechen** an den Aufrufer: Die Funktion verändert den übergebenen String nicht.

```c
#include <stdio.h>

void ausgeben(const char *text) {
    printf("%s\n", text);
    // text[0] = 'X';   // wäre ein Compiler-Fehler
}

int main(void) {
    char name[] = "Anna";
    ausgeben(name);         // OK: char * wird automatisch zu const char *
    ausgeben("Literal");    // OK
    return 0;
}
```

Die Standardbibliothek macht es genauso:

```c
size_t strlen(const char *s);
int    strcmp(const char *s1, const char *s2);
char  *strcpy(char *ziel, const char *quelle);   // nur die Quelle ist const
```

Die Umwandlung von `char *` nach `const char *` passiert automatisch, weil Rechte dabei nur eingeschränkt werden. Andersherum warnt der Compiler, weil der Schreibschutz verloren ginge.

---

## Und `const const char`?

```c
const const char *p;   // doppeltes const
```

Ab **C99** ist das erlaubt. Ein mehrfach angegebener Qualifizierer wirkt wie ein einzelner, das Ergebnis ist also dasselbe wie `const char *p`. In **C89** ist es laut Standard nicht erlaubt. GCC warnt in beiden Fällen (`duplicate 'const'`). Es hat keinen Nutzen, deshalb schreibt man es nicht so.

Gemeint ist meist eine dieser beiden Formen:

```c
const char *p;          // Zeichen konstant
const char * const p;   // Zeichen UND Zeiger konstant
```

---

## Zusammenfassung

- Ein String in C ist ein `char`-Array mit `'\0'` am Ende, meist angesprochen über einen `char`-Zeiger.
- `const` **links** vom `*` schützt die **Daten**, `const` **rechts** vom `*` schützt den **Zeiger**.
- String-Literale darf man nicht verändern. Deshalb gehören sie in `const char *`.
- Für eine veränderbare Kopie nimmst du `char s[] = "...";`.
- `const char *woerter[]` ist ein Array von Zeigern auf unveränderliche Strings, ideal für feste Wortlisten.

← Zurück zu [for_schleifen.md](for_schleifen.md)
