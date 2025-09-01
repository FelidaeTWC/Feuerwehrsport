/**
 * @file ProjektConfig.h
 * @brief Zentrale Konfigurations- und Strukturdaten für das Feuerwehr-Rennsystem.
 *
 * Dieses Header-File definiert alle globalen Strukturen, Enums und
 * Funktionsprototypen, die im Projekt benötigt werden.
 *
 * Enthalten sind:
 * - Definition der Betriebsmodi (Serial, TFT)
 * - Struktur für Projekteinstellungen
 * - Struktur für Bahndaten (Pins, Zeiten, Status)
 * - Globale Timer- und Anzeigefunktionen
 * 
 * @date 2025-08-31
 * @version 1.0
 * @author joachim.jaehn@twc-zone.de
 */

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Timer.h>
#include <ansi.h>

#include "serial-mode.h"
#include "tft-mode.h"


/**
 * @brief Enum für Betriebsmode
 */
enum class CMode : uint8_t 
{
    Serial, /**< Ausgabe und Bedienung über die serielle Schnittstelle */
    TFT     /**< Ausgabe und Bedienung über das TFT-Display */
};


/**
 * @brief Strukt für Projektweite Konfigurationseinstellungen.
 */
struct SProject 
{
  CMode IOMode;  /**< Aktueller Ein-/Ausgabemodus (Serial oder TFT) */
  uint32_t Baud; /**< Baudrate für die serielle Kommunikation */
};

/**
 * @brief Projektweite Konfigurationseinstellungen.
 */
extern SProject Projekt;


/**
 * @brief enum mit Stati einer Bahn
 */
enum class BahnStatus : uint8_t {
    Running,  /**< Bahn läuft gerade */
    Ready,    /**< im Ziel Zeit muss noch gespeichert werden */
    Disp      /**< im Ziel Zeit wurde gespeichert und wird angezeigt*/
};

/**
 * @brief Struktur für alle Bahnen-Pins und Timerwerte.
 * 
 * Pins und Timerwerte sind als 2D-Array [8][2] organisiert:
 *  - 8 Bahnen (0..7)
 *  - 2 Pins pro Bahn (0..1)
 */
struct Bahnen {
    uint8_t pins[8][2];       /**< IO Pins der 8 Bahnen links und rechts  */
    float time[8][2];         /**< Timerwerte der Pins: time[i][0..1] */
    BahnStatus status[8][2];  /**< Status der Bahn */
    uint8_t klappe;           /**< IO Pin für die Klappe */
    uint8_t taster;           /**< IO Pin für den Taster */
    uint32_t tcount;
};

/**
 * @brief  Variable mit Strukt für alle Bahnen-Pins und Timerwerte.
 */
extern Bahnen Bahn;

/**
 * @brief Default werte für das Bahnen Strukt zum zurücksetzen
 */
extern const Bahnen BahnDefault ;

/**
 * @brief Timer Classe zur Zeitmessung in ms
 * Verwendet Timer 0 und die Funktion millis()
 */
extern Timer timer;  // Timer für die Zeitmessung

/**
 * @brief globales flag -> geht auf 1 wenn die Zeitmessung angefangen hat.
 */
extern volatile bool timerStarted;

/**
 * @brief Globale Variable zum zwischenspeicher der Zeit
 */
extern float Time;

/**
 * @brief globale variable -> zeigt die zeit zwischen zwei Timer ISR.
 * wird zum Debuggen verwendet. sollte ~5ms betragen. 
 * wenn nicht gibt es ein Timing problem
 */
extern float LoopTime;

/**
 * @brief Globale Variable zum zwischenspeicher der Zeit zur berechnung von LoopTime
 */
extern float TimeOld;

/**
 * @brief legt aktuell fest nach wieviel fertigen Bahnen das rennen zuende ist.
 * bei erreichen des wertes wird der Timer gestoppt
 */
extern int   Raceover;


/**
 * @brief Classe mit Befehlen zum übertragen von ANSI Code über die Serielle Schnittstelle
 * mit Dieser klasse wird die Serielle Schnittstelle von 
 * einer Zeilenbasierten ausgabe zu einem Live Screen.
 */
extern ANSI ansi; 

/**
 * @brief  Setzt den Cursor auf dem TFT-Display oder Ser Seriellen Schnittstelle in einem Tabellenraster.
 * 
 * Diese Funktion berechnet die X- und Y-Position
 * basierend auf einem Tabellenraster der Größe ColCount × RowCount. 
 * Der Cursor wird dann an Position col Row gesetzt.
 * 
 * @param col       Spalte des Tabellenrasters (1..ColCount)
 * @param ColCount  Anzahl der Spalten im Tabellenraster
 * @param Row       Zeile des Tabellenrasters (1..RowCount)
 * @param RowCount  Anzahl der Zeilen im Tabellenraster
 */
void Table(int Col, int ColCount, int Row, int RowCount);

/**
 * @brief Konfiguration den Hardware Teimer 1 für Timer Interupt all 5ms
 */
void TimerConfig(void);

/**
 * @brief überträgt die Rennzeiten im CSV Vormat aun die Serielle Schnittstelle
 */
void show_Serial(void);

/**
 * @brief zeigt das Setup der Bahnen vor einem Rennen.
 *  Status der Eingänge. Start Klattpe, Dosen, 
 *  zeigt die Eingangsspannung an.
 *  wenn das Rennen vorbereitet ist wir auf show_mTime gewächselt.
 */
void show_Bahnsetup(void);

/**
 * @brief Hier findet das eigendliche Rennen statd.
 *  Wartet auf die Startklappe.
 *  Startet den Timer.
 *  zeigt sie Aktuelle Renn Zeit an.
 *  zeigt die Zeiten der Fertigen Bahnen an.
 */
void show_mTime(void);

/**
 * @brief Prüft ob der Tester oder die Enter Taste gedückt wurde.
 *  Diese Funktion wird in einer Schaleife aufgerufen.
 *  im Serial Mode wir geprüft ob die Entertaste gedrückt wurde
 *  im TFT Mode wird ein Zähler hogezählt wenn der Taster gedrückt ist.
 *  beim erreichen von T gild der Taster als gedrückt. (Entprellung )
 * @param T für die Taster Entprellung. Wert ist davon abhänig wie oft 
 *  die Schleife aufgerufen wurde und wie schnell der Taster reagieren soll. 
 * @return 0 nicht wurde gedrückt 1 Enter oder Taster wurden gedrückt.
 */
int  Bestetigung(uint32_t T);


/**
 * @brief gibt ein Logo auf der Serielle schnittstelle aus.
 */
void PrintLogo(void);


/**
 * @brief Gibt einen Wert auf dem aktuell aktiven Ausgabegerät aus.
 * 
 * Dieses Template gibt den übergebenen Wert auf der seriellen Schnittstelle
 * oder auf einem TFT-Display aus, abhängig vom aktuellen I/O-Modus des Projekts.
 * 
 * @tparam T Der Datentyp des auszugebenden Werts. Muss von Serial::print und/oder tft::print unterstützt werden.
 * @param value Der Wert, der ausgegeben werden soll.
 * 
 * @note Unterstützte Ausgabemodi:
 * - Serial: Ausgabe über die serielle Schnittstelle.
 * - TFT: Ausgabe auf dem TFT-Display.
 */
template<typename T>
void ScreenPrint(const T& value) {
  if (Projekt.IOMode == CMode::Serial)
    Serial.print(value);
  else if (Projekt.IOMode == CMode::TFT)
    tft.print(value);
}
