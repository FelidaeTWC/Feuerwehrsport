# Feuerwehrsport
Dies ist ein Arduino Mega 2560-Projekt.


## Benötigte Bibliotheken (Stand: 09/2025)


| Bibliothek             | Version | Autor / Quelle | GitHub                                                     |
| ---------------------- | ------- | -------------- | ---------------------------------------------------------- |
| `MCUFRIEND_kbv`        | 3.0.0-R | David Prentice | [GitHub](https://github.com/prenticedavid/MCUFRIEND_kbv)   |
| `Adafruit_TouchScreen` | 1.1.5   | Adafruit       | [GitHub](https://github.com/adafruit/Adafruit_TouchScreen) |
| `Timer`                | 1.2.1   | Simon Staub    | [GitHub](https://github.com/sstaub/Timer)                  |
| `Ansi`                 | 0.3.4   | Rob Tillaart   | [GitHub](https://github.com/RobTillaart/Ansi)              |


## Installation

1. Arduino IDE öffnen
2. Bibliotheken über **Sketch → Bibliothek einbinden → Bibliotheken verwalten** suchen und installieren


## Serial Output
Die Zeiten werden über die serielle Schnittstelle wie folgt ausgegeben.
Alle ungenutzten Bahnen zeigen 0.00 an.

```

Rennzeiten:
B1.L:;21.63;B1.R:;22.53;
B2.L:;23.97;B2.R:;25.67;
B3.L:;0.00;B3.R:;0.00;
B4.L:;0.00;B4.R:;0.00;
B5.L:;0.00;B5.R:;0.00;
B6.L:;0.00;B6.R:;0.00;
B7.L:;0.00;B7.R:;0.00;
B8.L:;0.00;B8.R:;0.00;
```



## Pinout Mega2560
![Schaltung-PINOUT.png](/Schaltung-PINOUT.png)

