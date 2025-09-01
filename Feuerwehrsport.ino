
// Pin-Konfiguration für das Projekt:
#include "ProjektConfig.h"


/**
 * @brief Initialisiert alle Hardware-Komponenten und wartet auf die Auswahl des Betriebsmodus.
 * 
 * Diese Funktion wird einmalig vor der loop()-Funktion ausgeführt.
 * 
 * Folgende Aufgaben werden durchgeführt:
 * - Konfiguration der Pins für Bahnen, Klappe und Taster
 * - Initialisierung des Timers (5 ms Interrupt)
 * - Initialisierung von Serial und TFT
 * - Warten auf Nutzereingabe:
 *   - Enter-Taste für Serial-Modus
 *   - Taster für TFT-Modus
 */
void setup(void);




/**
 * @brief Hauptprogrammschleife des Rennsystems.
 * 
 * Diese Funktion wird kontinuierlich ausgeführt und:
 * - Setzt alle Statuswerte und Zeiten zurück
 * - Zeigt den aktuellen IO-Status und die Versorgungsspannung an
 * - Startet das Rennen, misst und zeigt Zeiten an
 * - Überträgt Ergebnisse über die serielle Schnittstelle
 */
void loop();



void setup(void) 
{
  char c;
  
  // Bahn-Pin-Konfiguration
  for (int B = 0; B < 8; B++) 
  {
    pinMode(Bahn.pins[B][0], INPUT_PULLUP);  //Bahn pin Config
    pinMode(Bahn.pins[B][1], INPUT_PULLUP);  //Bahn pin Config 
  }

  // Pin-Konfiguration für die Klappe
  pinMode(Bahn.klappe, INPUT_PULLUP);  //Klappe

  // Pin-Konfiguration für den Taster
  pinMode(Bahn.taster, INPUT_PULLUP);  //Taster
  
  // Timer-Interrupt alle 5 ms
  // Verwendet Timer 
  // ISR -> prüft welche Bahn fertig ist und speichert die Zeit.
  TimerConfig();

  // Konfiguration des seriellen Terminals
  ConfigSerial();

  // Konfiguration des TFT-Displays
  ConfigTFT();


  // Warten auf Auswahl von TFT- oder Serial-Modus
  while (1)
  {
    //Auswahl mit Enter für Serial
    if (Serial.available() > 0) 
    {
       c = Serial.read();

      // Enter-Taste erkannt
      if (c == '\r') 
      { // Enter = Carriage Return
        Projekt.IOMode=CMode::Serial;
        tft.fillScreen(BLACK);
        tft.setCursor(0 , 0);
        tft.println("Serial Mode");
        ansi.foreground(2);        // Grün
        ansi.cursorHide();         // Cursor ausblenden
        Serial.println("Serial Mode");
        PrintLogo();
        Serial.println("Drücke Enter um fort zu fahren");
        while(1)
        {
          if(Bestetigung(1)==1) break;
        }
        break;
      }
    }

    // Auswahl mit Taster für TFT
    if(digitalRead(Bahn.taster)==HIGH) 
    {
      if (Bahn.tcount!=0) Bahn.tcount--;
      continue;
    }
    else
    {
      Bahn.tcount++;
      if (Bahn.tcount == 10) 
      {
        Bahn.tcount=0;
        Projekt.IOMode=CMode::TFT;
        tft.fillScreen(BLACK);
        tft.setCursor(0 , 0);
        tft.println("TFT Mode");
        ansi.clearScreen();
        break;
      }
    }
    delay(100);
  }
  delay(1000);
}


void loop(void) 
{

  // Alle Zeiten und Status zurücksetzen
  Bahn = BahnDefault;

  // Zeigt Status aller IO's und die Versorgungsspannung
  show_Bahnsetup();

  // Das Rennen starten, Zeiten messen und anzeigen
  show_mTime();

  // Zeiten via Serial Port an PC übertragen
  show_Serial();

}













// alte funktionen aus Beispiel projekt
// zum test des Touch
/*
void show_tft(void) {
  tft.setCursor(0, 0);
  tft.setTextSize(1);
  tft.print(F("ID=0x"));
  tft.println(ID, HEX);
  tft.println("Screen is " + String(tft.width()) + "x" + String(tft.height()));
  tft.println("");
  tft.setTextSize(2);
  tft.println(name);
  tft.setTextSize(1);
  tft.println("PORTRAIT Values:");
  tft.println("LEFT = " + String(TS_LEFT) + " RT  = " + String(TS_RT));
  tft.println("TOP  = " + String(TS_TOP) + " BOT = " + String(TS_BOT));
  tft.println("\nWiring is: ");
  tft.println("YP=" + String(YP) + " XM=" + String(XM));
  tft.println("YM=" + String(YM) + " XP=" + String(XP));
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.setCursor((tft.width() - 48) / 2, (tft.height() * 2) / 4);
  tft.print("EXIT");
  tft.setTextColor(YELLOW, BLACK);
  tft.setCursor(0, (tft.height() * 6) / 8);
  tft.print("Touch screen for loc");

  while (1) {
    tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
    if (tp.x > 480 && tp.x < 570 && tp.y > 530 && tp.y < 650) break;
    tft.setCursor(0, (tft.height() * 3) / 4);
    tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ");
  }
}
*/