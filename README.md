# school_C

Kleine C-Programme, die ich im Programmierunterricht in der Schule geschrieben habe. Jedes Programm ist eine eigenständige Übung zu einem Grundthema: Schleifen, Bedingungen, Benutzereingaben und Eingabeprüfung.

## Inhalt

### Schleifen

| Datei | Was das Programm macht | Thema |
|---|---|---|
| [`zaehlen_1_to_100.c`](zaehlen_1_to_100.c) | Gibt die Zahlen 1 bis 100 aus, jede in einer eigenen Zeile. | `while`-Schleife, Zähler |
| [`Sum_of_numbers_1_to100.c`](Sum_of_numbers_1_to100.c) | Addiert alle Zahlen von 1 bis 100 und gibt die Summe aus (5050). | Aufsummieren in einer Schleife |
| [`natural numbers dividable by 3 and 4.c`](natural%20numbers%20dividable%20by%203%20and%204.c) | Gibt alle Zahlen von 1 bis 100 aus, die durch 3 **oder** 4 teilbar sind. | Modulo-Operator `%`, logisches ODER |
| [`4_numbers_next_to_each_other.c`](4_numbers_next_to_each_other.c) | Wie oben, aber immer 4 Zahlen nebeneinander in einer Zeile. | Zweiter Zähler für den Zeilenumbruch |

### for-Schleifen

Ausführliche Erklärung mit allen Aufgabenstellungen: [`for_schleifen.md`](for_schleifen.md)

| Datei | Was das Programm macht | Thema |
|---|---|---|
| [`for_loop.c`](for_loop.c) | Liest zwei Zahlen a und b ein und gibt für jede Zahl dazwischen das englische Wort (1–9) oder `even`/`odd` aus. Aufgabe von [HackerRank](https://www.hackerrank.com/challenges/for-loop-in-c/problem). | `for`-Schleife, Array mit `const char *` |
| [`for_loop_switch.c`](for_loop_switch.c) | Dieselbe Aufgabe, aber mit `switch` statt Array. | `switch`, `case`, `default`, `break` |
| [`for_pyramide.c`](for_pyramide.c) | Zeichnet eine Pyramide aus Sternen (1, 3, 5, 7, 9 Sterne pro Zeile). | Verschachtelte `for`-Schleifen |
| [`for_schachbrett.c`](for_schachbrett.c) | Gibt ein 8×8-Schachbrett aus `X` und Leerzeichen aus. | Verschachtelte Schleifen, `(zeile + spalte) % 2` |

### Bedingungen und Benutzereingaben

| Datei | Was das Programm macht | Thema |
|---|---|---|
| [`Zugriffsabfrage.cpp`](Zugriffsabfrage.cpp) | Fragt PIN und Sicherheitsstufe ab. Nur bei PIN `1234` **und** Stufe `3` wird der Zugriff gewährt. | `scanf`, `if`/`else`, `&&` und `\|\|` |
| [`ticketautomat.cpp`](ticketautomat.cpp) | Ticketautomat: Je nach Alter gibt es ein kostenloses, Kinder-, Erwachsenen- oder Seniorenticket. Zwischen 9 und 16 Uhr gibt es zusätzlich einen Nebenzeit-Rabatt. Ungültige Eingaben werden abgefangen. | `if`/`else if`-Ketten, Wertebereiche prüfen |

### Median von drei Zahlen

Zwei Lösungen für dieselbe Aufgabe: Der Benutzer gibt drei Zahlen ein, das Programm gibt den Median (die mittlere Zahl) aus.

| Datei | Lösungsweg |
|---|---|
| [`median_if_else.cpp`](median_if_else.cpp) | Einsteigerversion: Liest die Zahlen mit `scanf` ein und fragt bei falscher Eingabe erneut. Der Median wird mit `if`/`else` bestimmt (die Zahl, die zwischen den beiden anderen liegt). |
| [`median.cpp`](median.cpp) | Fortgeschrittene Version: Eigene Funktionen, Einlesen mit `fgets` + `strtod`, Eingabeprüfung in einer Hilfsfunktion und Median ohne Sortieren über `max(min(a, b), min(max(a, b), c))`. |

## Erklärungen

| Dokument | Inhalt |
|---|---|
| [`for_schleifen.md`](for_schleifen.md) | Aufbau und Ablauf der `for`-Schleife, verschachtelte Schleifen und die drei Aufgaben Schritt für Schritt erklärt |
| [`const-char.md`](const-char.md) | Was `const char *` bedeutet, die vier Varianten von `const` und Zeigern, Arrays von Strings |
| [`switch.md`](switch.md) | Die `switch`-Anweisung: `case`, `break`, Fall-through, `default` und typische Fehler |

## Kompilieren und Ausführen

Alle Programme sind in C geschrieben, auch die Dateien mit der Endung `.cpp`. Man braucht einen C-Compiler, zum Beispiel `gcc`:

```bash
gcc zaehlen_1_to_100.c -o zaehlen
./zaehlen
```

Für die `.cpp`-Dateien `gcc` mit `-x c` anweisen, sie als C zu behandeln:

```bash
gcc -x c ticketautomat.cpp -o ticketautomat
./ticketautomat
```

`median.cpp` nutzt `math.h`, deshalb unter Linux `-lm` anhängen:

```bash
gcc -x c median.cpp -o median -lm
```

Dateinamen mit Leerzeichen in Anführungszeichen setzen:

```bash
gcc "natural numbers dividable by 3 and 4.c" -o teilbar
```

`for_loop.c` erwartet zwei Zahlen als Eingabe. Zum Testen kann man sie direkt übergeben:

```bash
gcc for_loop.c -o for_loop
printf "8\n11\n" | ./for_loop
```

## Gelernte Grundlagen

- Ausgabe mit `printf` und Einlesen mit `scanf` / `fgets`
- `while`-Schleifen und Zählvariablen
- `for`-Schleifen und verschachtelte Schleifen
- Bedingungen mit `if`, `else if`, `else`
- Mehrfachauswahl mit `switch`
- Logische Operatoren `&&` (UND) und `||` (ODER)
- Modulo-Operator `%` für Teilbarkeit und gerade/ungerade
- Arrays von Strings mit `const char *`
- Ungültige Benutzereingaben abfangen
- Eigene Funktionen schreiben (`median.cpp`)
