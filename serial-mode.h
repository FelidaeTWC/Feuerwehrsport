


/**
 * @brief  Setzt den Cursor mit ANSI Code auf dem Serialen Terminal in einem Tabellenraster.
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
void SerialTable(int Col, int ColCount, const int* ColWidth, int Row, int RowCount);

/**
 * @brief legt die Spaltenbreite in % einer Tabelle auf dem Serialen Terminal fest.
 *  in diesem Projekt 4 Spalten. 
 */
extern int SerialTableWidth[];

/**
 * @brief Konfiguration der Seriellen Schnittstelle  
 */
void ConfigSerial(void);
 