
// Display mit touch


#include "ProjektConfig.h"


MCUFRIEND_kbv tft;  // hard-wired for UNO shields anyway.

uint16_t ID;
uint8_t Orientation = 1;  //PORTRAIT  1= Querformat


char *name = "Please Calibrate.";            //edit name of shield
const int XP = 6, XM = A2, YP = A1, YM = 7;  //240x320 ID=0x9341
const int TS_LEFT = 185, TS_RT = 940, TS_TOP = 972, TS_BOT = 215;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;


int TFTTableWidth[] = {20, 30, 20, 30}; // 4 Spalten, in % von Displaybreite

void ConfigTFT(void)
{
  tft.reset();
  ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(Orientation);
  tft.fillScreen(BLACK);
  tft.setTextColor(YELLOW, BLACK);
  tft.setCursor(0 , 0);
  tft.setTextSize(2);
  tft.println("Druecke:\n");
  tft.println("Taster -> TFT    Mode");
  tft.println("Enter  -> Serial Mode");
  tft.println(" ");
  tft.println(Projekt.Baud);
}



void tftTable(int Col, int ColCount, const int* ColWidth, int Row, int RowCount)
{
  if (Col > ColCount || Col < 1) return;
  if (Row > RowCount || Row < 1) return;

  int RowPos = tft.height() * (Row - 1) / RowCount;
  int ColPos = 0;
  for (int i = 0; i < Col - 1; i++) {
    ColPos += tft.width() * ColWidth[i] / 100;
  }
  tft.setCursor(ColPos,RowPos);
}