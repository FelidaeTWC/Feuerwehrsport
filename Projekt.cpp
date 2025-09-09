#include "ProjektConfig.h"


extern SProject Projekt 
{
  CMode::Serial,
  115200
};




Timer timer(MILLIS);  // Timer für die Zeitmessung

volatile bool timerStarted = false;
float Time = 0;
float LoopTime = 0;
float TimeOld = 0;
int   Raceover=16;


/**
 * @brief Initialisierung der Pins und Timerwerte
 */
const Bahnen BahnDefault = 
{
  {
    {30, 31},  // Bahn1
    {32, 33},  // Bahn2
    {34, 35},  // Bahn3
    {36, 37},  // Bahn4
    {38, 39},  // Bahn5
    {40, 41},  // Bahn6
    {42, 43},  // Bahn7
    {44, 45}   // Bahn8
  },
  {
    {0.0, 0.0},  // Timer Bahn1
    {0.0, 0.0},  // Timer Bahn2
    {0.0, 0.0},  // Timer Bahn3
    {0.0, 0.0},  // Timer Bahn4
    {0.0, 0.0},  // Timer Bahn5
    {0.0, 0.0},  // Timer Bahn6
    {0.0, 0.0},  // Timer Bahn7
    {0.0, 0.0}   // Timer Bahn8
  },
  {
    {BahnStatus::Running, BahnStatus::Running},  // Startstatus: alle laufen
    {BahnStatus::Running, BahnStatus::Running},
    {BahnStatus::Running, BahnStatus::Running},
    {BahnStatus::Running, BahnStatus::Running},
    {BahnStatus::Running, BahnStatus::Running},
    {BahnStatus::Running, BahnStatus::Running},
    {BahnStatus::Running, BahnStatus::Running},
    {BahnStatus::Running, BahnStatus::Running}
  },
  22,  // Klappe
  52   // Taster
};

Bahnen Bahn = BahnDefault;

/**
 * @brief startet den Timer und die Messung
 */
void startRace(void);



void Table(int Col, int ColCount, int Row, int RowCount)
{
  if(Projekt.IOMode==CMode::Serial)  SerialTable(Col, ColCount, SerialTableWidth, Row,RowCount);
  if(Projekt.IOMode==CMode::TFT)     tftTable(Col, ColCount, TFTTableWidth, Row,RowCount);
}


void TimerConfig(void)
{
    // Timer für Pin auswerte ISR alle 5ms  überabtastung für gagantiert 1/100s genauigkeit.
  noInterrupts();           // Interrupts ausschalten
  TCCR1A = 0;               // Timer1 Control Register A
  TCCR1B = 0;               // Timer1 Control Register B
  TCNT1  = 0;               // Timer1 Zähler zurücksetzen
  // Vergleichswert berechnen
  // f = 16 MHz / prescaler → dann Compare = f * interval
  // Beispiel: Prescaler 64
  long compare = (16e6 / 64) * (2 / 1000.0) - 1;
  OCR1A = compare;          // Compare Match Register A

  TCCR1B |= (1 << WGM12);   // CTC Mode
  TCCR1B |= (1 << CS11) | (1 << CS10);  // Prescaler 64

  TIMSK1 |= (1 << OCIE1A);  // Compare Match Interrupt aktivieren
  interrupts();                 // interrups für pin auswertung per Timer ISR starten
}


void show_Bahnsetup(void) 
{
  
  char c;

  tft.fillScreen(BLACK);
  tft.setTextSize(2);

  // Tabelle mit 4 spallten und 12 Zeilen
  // Zeile 1 und 2 Überschrift
  ansi.clearScreen();
  ansi.foreground(2);        // Grün
  ansi.cursorHide();         // Cursor ausblenden

  Table(1, 4,  1, 12);
  ScreenPrint("Bahn Setup");
  Table(1, 4,  2, 12);

  if(Projekt.IOMode == CMode::Serial)
  {
    tft.setTextSize(4);
    tft.setCursor(0, 0);
    tft.print("Bahn Setup");
  }
  // Zeile 11 Klappe + Versorgungsspannung
  tft.setTextSize(2);

  // Zeile 3 bis 10 Bahnen 1.1 bis 8.2


  for (int B = 0; B < 8; B++) {
    Table(1, 4, 3 + B, 12);
    ScreenPrint("B");
    ScreenPrint(B + 1);
    ScreenPrint(".L:");

    Table(3, 4, 3 + B, 12);
    ScreenPrint("B");
    ScreenPrint(B + 1);
    ScreenPrint(".R:");
  }

  Table(1, 4,  11, 12);
  ScreenPrint("K:");

  Table(3, 4, 11, 12);
  ScreenPrint("U:");

  Table(1, 4,  12, 12);

  if(Projekt.IOMode==CMode::Serial) ScreenPrint("Drücke Enter um das Rennen zu starten");
  if(Projekt.IOMode==CMode::TFT)    ScreenPrint("Taster -> Start rennen");

  // schleife anzeige des Pin Satus und der Spannung

  while (1) {

    for (int B = 0; B < 8; B++) {
      Table(2, 4, 3 + B, 12);
      ScreenPrint(digitalRead(Bahn.pins[B][0]));

      Table(4, 4,  3 + B, 12);
      ScreenPrint(digitalRead(Bahn.pins[B][1]));

    }

    // Zeile 11 -> Klappe + Spannung
    Table(4, 4,  11, 12);
    ScreenPrint(analogRead(A8) * 83.0 / 3069.0);
    //ScreenPrint(Bahn.tcount);
    
    Table(2, 4, 11, 12);
    ScreenPrint(digitalRead(Bahn.klappe));
    //ScreenPrint(digitalRead(Bahn.taster));

    // warten auf Touch tip um weiter zu nächsten Skreen zu gehen.

    
    if(Bestetigung(10)==0) continue; 
    else break;
  }

}



void show_mTime(void) 
{
  char c;
  tft.fillScreen(BLACK);
  if(Projekt.IOMode==CMode::Serial)
  {
    tft.setTextSize(4);
    tft.setCursor(0 , 0);
    tft.println("Rennen");
  }


  // Bahn Timer 
  ansi.clearScreen();
  ansi.foreground(2);        // Grün
  ansi.cursorHide();         // Cursor ausblenden

  tft.setTextSize(2);
  Table(1, 4,  1, 12);
  ScreenPrint("Timer:");

  // Beschriftung


  // Zeile 3 bis 10 Bahnen 1.1 bis 8.2
  tft.setTextSize(2);
  for (int B = 0; B < 8; B++) {
    Table(1, 4, 3 + B, 12);
    ScreenPrint("B");
    ScreenPrint(B + 1);
    ScreenPrint(".L:");

    Table(3, 4, 3 + B, 12);
    ScreenPrint("B");
    ScreenPrint(B + 1);
    ScreenPrint(".R:");
  }


  // Warten auf Start des rennen
  while (1) 
  {
    if (digitalRead(Bahn.klappe) == LOW) continue;
    else break;

    //if (Bestetigung(1) == 0) continue;
    //else break;
  }

  // Rennen Starten
  startRace();

  // Display alle Bahnen auf Run setzen 
  for (int B = 0; B < 8; B++) 
  {
    Table(2, 4, 3 + B, 12);
    ScreenPrint("Run");

    Table(4, 4, 3 + B, 12);
    ScreenPrint("Run");
  }


  while (1) 
  {

    //  Timer anzeigen
    Table(2, 4,  1, 12);
    ScreenPrint(Time/1000.0);

    Table(4, 4, 1, 12);
    ScreenPrint(LoopTime);


    // Bahnstatus anzeigen

    for (int B = 0; B < 8; B++) 
    {
      if (Bahn.status[B][0] == BahnStatus::Ready) // wenn Bahn Links fertig
      {
        Table(2, 4, 3+B, 12);
        ScreenPrint(Bahn.time[B][0]); // Bahn Zeit ausgeben.
        Bahn.status[B][0] = BahnStatus::Disp; 

        if(Bahn.status[B][1] == BahnStatus::Disp ) // wenn bahn Rechts Soch voher Fertig -> Bahn Links ist die lagsamere 
        {
          ScreenPrint(" *");  // * zeigt die labsamere Seite der Bahn
        } 
      }

      if (Bahn.status[B][1] == BahnStatus::Ready)  // wenn Bahn Rechts fertig
      {
        Table(4, 4, 3+B, 12);
        ScreenPrint(Bahn.time[B][1]); // Bahn Zeit ausgeben.
        Bahn.status[B][1] = BahnStatus::Disp;

        if(Bahn.status[B][0] == BahnStatus::Disp  ) // wenn bahn Links schon voher Fertig -> Bahn Rechts ist die lagsamere 
        {
          ScreenPrint(" *"); // * zeigt die labsamere Seite der Bahn
        }       
      }

    }

    if(Bestetigung(30)==0) continue;
    else
    {
      timer.stop();
      timerStarted = false;
      for (int B = 0; B < 8; B++) 
      {
        if (Bahn.status[B][0] == BahnStatus::Running)
        {
          Table(2, 4,  3+B, 12);
          ScreenPrint("inf");
        } 
        if (Bahn.status[B][1] == BahnStatus::Running)
        {
          Table(4, 4, 3+B, 12);
          ScreenPrint("inf");
        } 
      }
      break;
    }
  }
}


int Bestetigung(uint32_t T)
{
  switch (Projekt.IOMode)
  {
    case CMode::Serial:
      if (Serial.available() > 0) 
      {
        char c = Serial.read();

        if (c == '\r') 
        { // Enter = Carriage Return
          return 1;
        }
      }
      break;

    case CMode::TFT:  
      // Auswahl mit Taster für TFT
      if(digitalRead(Bahn.taster)==HIGH) 
      {
        if(Bahn.tcount!=0) Bahn.tcount--;
      }
      else Bahn.tcount++;

      if (Bahn.tcount == T)
      { 
        Bahn.tcount = 0;
        return 1;
      }
      break;     
  }
  return 0;
}


void show_Serial(void) 
{
  char c;
  if(Projekt.IOMode==CMode::Serial)
  {
    tft.setTextSize(4);
    tft.setCursor(0 , 0);
    tft.println("Auswertung");
  }
  tft.setTextSize(2);
  tftTable(1,2,TFTTableWidth,12,12);
  tft.println("Auswertung wird gsendet");

  ansi.clearScreen();
  ansi.foreground(2);        // Grün
  ansi.cursorHide();         // Cursor ausblenden
  Serial.println("");
  Serial.println("Rennzeiten:");
  for (int B = 0; B < 8; B++) 
  { 
    Serial.print("B");
    Serial.print(B+1);
    Serial.print(".L:;");
    Serial.print(Bahn.time[B][0]);
    Serial.print(";");
    Serial.print("B");
    Serial.print(B+1);
    Serial.print(".R:;");
    Serial.print(Bahn.time[B][1]);
    Serial.println(";");

  }
  Bahn.tcount = 0;
  while(1)
  { 
    if(Bestetigung(30)==1) break;
    delay(100);
  }
}




// Interrupt ISR
void TimeMessure(void) 
{
  Time = (float)timer.read()*1.0129;
  LoopTime = Time - TimeOld;
  TimeOld = Time;
  
  for (int B = 0; B < 8; B++) 
  { 
    if (Bahn.status[B][0] == BahnStatus::Running && digitalRead(Bahn.pins[B][0])==LOW) 
    {
      Bahn.time[B][0]   = Time/1000.0;
      Bahn.status[B][0] = BahnStatus::Ready;
      Raceover--;
    }
    if (Bahn.status[B][1] == BahnStatus::Running && digitalRead(Bahn.pins[B][1])==LOW) 
    {
      Bahn.time[B][1]   = Time/1000.0;
      Bahn.status[B][1] = BahnStatus::Ready;
      Raceover--;
    }
  }
  
  if(Raceover == 0)
  {
    timer.stop();
    timerStarted = false;
  }

}

// ISR
ISR(TIMER1_COMPA_vect) {
    if (timerStarted) 
    {
      TimeMessure();       // deine Funktion
    }
}

// Startfunktion
void startRace() 
{
  timer.start();            // Zeitmessung starten
  timerStarted = true;
  TimeMessure();            // einmal direkt beim Start aufrufen

}

