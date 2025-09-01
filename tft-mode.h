

extern MCUFRIEND_kbv tft;  // hard-wired for UNO shields anyway.

extern uint16_t ID;
extern uint8_t Orientation;

// Assign human-readable names to some common 16-bit color values:
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

/**
 * @brief legt die Spaltenbreite in % einer Tabelle aufdem TFT fest.
 *  in diesem Projekt 4 Spalten. 
 */
extern int TFTTableWidth[]; 


/**
 * @brief  Setzt den Cursor auf dem TFT-Display in einem Tabellenraster.
 * 
 * Diese Funktion berechnet die X- und Y-Position
 * basierend auf einem Tabellenraster der Größe ColCount × RowCount. 
 * Der Cursor wird dann an Position col Row gesetzt.
 * 
 * @param col       Spalte des Tabellenrasters (1..ColCount)
 * @param ColCount  Anzahl der Spalten im Tabellenraster
 * @param ColWidth  ein array das die Spaltenbreite defieniert.
 * @param Row       Zeile des Tabellenrasters (1..RowCount)
 * @param RowCount  Anzahl der Zeilen im Tabellenraster
 */
void tftTable(int Col, int ColCount, const int* ColWidth, int Row, int RowCount);

/**
 * @brief config für Touch und TFT Display
 */
void ConfigTFT(void);


// Touch

#define MINPRESSURE 200
#define MAXPRESSURE 1000
extern char *name;   
extern const int XP, XM, YP, YM;
extern const int TS_LEFT, TS_RT, TS_TOP,TS_BOT;
extern TouchScreen ts;
extern TSPoint tp;
