## Die for-Schleife

Mit einer **for-Schleife** führst du denselben Code mehrmals aus, entweder **für jedes Element einer Sammlung** oder **eine bestimmte Anzahl von Malen**.

### Variante 1: Über eine Sammlung laufen (z. B. Python)

```python
fruechte = ["Apfel", "Banane", "Kirsche"]

for frucht in fruechte:
    print(frucht)
```

Ausgabe:
```
Apfel
Banane
Kirsche
```

Die Variable `frucht` nimmt bei jedem Durchlauf das nächste Element an. Wenn die Liste durchlaufen ist, endet die Schleife.

### Variante 2: Mit Zähler (z. B. JavaScript, Java, C)

```javascript
for (let i = 0; i < 5; i++) {
    console.log(i);
}
```

Die Klammer hat drei Teile:

1. **Start:** `let i = 0`. Der Zähler beginnt bei 0.
2. **Bedingung:** `i < 5`. Solange sie wahr ist, läuft die Schleife weiter.
3. **Schritt:** `i++`. Nach jedem Durchlauf wird `i` um 1 erhöht.

Ausgabe: `0 1 2 3 4`

### Ablauf

1. Startwert setzen
2. Bedingung prüfen. Ist sie falsch, ist die Schleife zu Ende.
3. Den Code im Schleifenkörper ausführen
4. Den Zähler verändern
5. Zurück zu Schritt 2

**Merksatz:** Die for-Schleife nimmst du, wenn du **vorher weißt, wie oft** oder **über was** du wiederholen willst. Hängt das Ende von einer Bedingung ab, die sich erst während der Ausführung ergibt, passt eine **while-Schleife** meist besser.
