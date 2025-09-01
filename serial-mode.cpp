
#include "ProjektConfig.h" 


ANSI ansi(&Serial);

/**
 * @brief definiert einen Typische Terminal Screen 80x24
 *  wird zur berechnung der Tamellen breite und läcnge benötigt.
 */
struct Terminal 
{
  uint8_t width;
  uint8_t height;
};
Terminal Screen {80, 24};


int SerialTableWidth[] = {10, 40, 10, 40}; // 4 Spalten, in % von Displaybreite


void SerialTable(int Col, int ColCount, const int* ColWidth, int Row, int RowCount)
{
  if (Col > ColCount || Col < 1) return;
  if (Row > RowCount || Row < 1) return;

  int RowPos = Screen.height * (Row - 1) / RowCount;
  int ColPos = 0;
  for (int i = 0; i < Col - 1; i++) {
    ColPos += Screen.width * ColWidth[i] / 100;
  }
  ansi.gotoXY(ColPos+1,RowPos+1);
}

void ConfigSerial(void)
{

  Serial.begin(Projekt.Baud);


}

void PrintLogo(void)
{

  ansi.clearScreen();
  ansi.gotoXY(1, 1);
  ansi.bold();
  ansi.foreground(2);        // Grün
  Serial.println("Live Monitor");


  Serial.println("                   _____");
  Serial.println("                 .'.---.'.");
  Serial.println("                //   ,   \\\\");
  Serial.println("               ||   `|    ||");
  Serial.println("               ||    |    ||");
  Serial.println("               ||   -'-   ||");
  Serial.println("          .-\"`'-.,_     _,.-'`\"-.");
  Serial.println("         / .'--,___`\"\"\"`___,--'. \\");
  Serial.println("         |  /:////_'---'_\\\\\\\\:\\  |");
  Serial.println("          \\|:|// `_     _` \\\\|:|/");
  Serial.println("           '-/| (6/     \\6) |\\-'");
  Serial.println("             \\\\     | |     //");
  Serial.println("              `|   (._.)   |`");
  Serial.println("               |    _ _    |");
  Serial.println("               \\   '---'   /");
  Serial.println("                '--.___.--'");
  Serial.println(" ____                              ");
  Serial.println("/ _(_)                               ");
  Serial.println("| |_ _ _ __ ___ _ __ ___   __ _ _ __  ");
  Serial.println("|  _| | '__/ _ \\ '_ ` _ \\ / _` | '_ \\ ");
  Serial.println("| | | | | |  __/ | | | | | (_| | | | |");
  Serial.println("|_| |_|_|  \\___|_| |_| |_|\\__,_|_| |_|");
  Serial.println("                                      ");
  Serial.println();

/*
  Serial.println("MMMMMMMMMMMMMMMMMWWMMMMMWWWWMWNXOxxollllclooxkOXNMMMMMMMMMWMMMMMMMMMMMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMMMMMMWWMMMMWNKkdlcccccllc:.'cllllcccccldOXWMMWWMMMMMMMMMMMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMMMMMMMWMWKxlc:;cdk00xd0WM0':KNMMWWNX0kdlc:clkKWMMMMMMMMMMMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMMMMMMN0d::clldkxk0kxkoOMMO':KNMMMXxooONMWXk;,::d0WMMMMMMMMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMMMWXx:;ckOkdloxxkxkXWkxNWO':KNWWXd:;:xNMMMXoxXkc;:xXMMMMMMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMWKo;:xXWKdkKd::ckWWMMNXNM0':KNW0;....oKKKK0ldKKK0d;,oKWMMWWMMMMMMMMM");
  Serial.println("MMMMMMMMMMWXo,:kOxOkx0WNd'',,cONMWMMM0':KNK;......'',''..'.'c0Xk:,dXWMWMMMMMMMMM");
  Serial.println("MMMMMMMMMNk;;xKXdck0XMN0:.....,OWMMWM0':0XO'......cOOOkloxxkOXWWNx;;kWWMMMMMMMMM");
  Serial.println("MMMMMMMMXl'l0NOodkKKko;.''.....lXWMMM0':0XO'......dWWWKlxWMMMMMMMWXl'lXWMMMMMMMM");
  Serial.println("MMMMMMW0;,kNK0kodd:'.,cxKx'.....cKMMM0':0NO'......,llc;.;XMMMMMMMMWNx,:KMMMMMMMM");
  Serial.println("MMMMMW0;,OWMWNk,..,okKXXO;.'.....:0WM0':0NO'......,c:cc;xNWMMMMMMMMMWO,;0MWWMMMM");
  Serial.println("MMMMM0;,lxXWOdKOo;,;,;:;'.oKd.....,OW0':0NO'......dWW0lxOkNMMMMMMMMMMWO,;KMMMMMM");
  Serial.println("MMMMX:'xdcxKxcxNN0Okl,:xOkxo:......cK0':0XO'......oWWKc::dWMMMMMMMWMMMWk'cXMMMMM");
  Serial.println("MMMWd.dXkkOdokOod0WWWO;;:,.......:kXW0':0NO'......;0WWKxONMMMMMMMMMMMMMWo.xWMMMM");
  Serial.println("MMMK;,0WOxNNXNWXXWWMXc.....:d:. ,0MWMO':0NO'..':...,kNWMMMMMMMMMWMMMMMMMK,;KMMMM");
  Serial.println("MMMx.lOOko0MMMWWMWWMK;..;o:oKo. '0WWM0':0XO'..:Kx'...dNWMMMMMMMMMMMMMMMMWo.xMMMM");
  Serial.println("MWNl'xkloONWWWWMMMMMK; .lNKdc,...c0K0d.:0NO'..:KWO,...oXMMMMMMMMMMMMMMMMMk.oWMMM");
  Serial.println("WMX:,0WXOkOKNWWWWWWW0;..lXWWXOo'..'cxl.:0XO'..:KWWO;...lXWWWMMWWWWMMMWWWWO':NMMM");
  Serial.println("WWX;.:ccclccccclcccc:'..,cccccc,..';c;.':c:...,cccc;....;llcccccccccccccc;.:XMMM");
  Serial.println("WWX:.x0000000000000000OdlodO000000000d.;kO00000000000OkxkO000000000000000d.:XMMM");
  Serial.println("MWNc'OMMMMMMMMMMMMMMMWOl::oKWWMMMMMMMO':KNWMMMMMMMWWNxllo0WMMMMMMMMMMMMMMk'lWMMM");
  Serial.println("MMWx.oWMMMMMMMMMMMMMMWOc:::coOXWMMWWM0':0NMMMMMMMWN0l;;;c0WMMMMMMMMMMMMMWo.xMMMM");
  Serial.println("MMMK,;KMMMMMMNkoooooooc.......,oKWWMM0':KNMWMMMMNx;....;xXWMMMMMMMMMMMMMK;,KMMMM");
  Serial.println("MMMWd.dWMMMMWK:..,::;;:::,......;0WMMO':KNMMMMMXo......dMMMMMMMMMMMMMMMWd.dWMMMM");
  Serial.println("MMMMX:,0WWMMMWX0xxXMWWWWWXl......,kWW0':KNMMWWKc.......dMMMMMMMMMMMMMMWO,:XMWMMM");
  Serial.println("MMMMW0,;KWMMMMMWNOkXWMWWWMNo......'xW0':KNMWW0;........dMMMMMMMMMMMMMW0;;0MMMMMM");
  Serial.println("MMMMMWO,;KMMMMMMMW0xKWWWXko,........dk':0NMWO,.........dMMMMMMMMMMMMM0;,OWWMMMMM");
  Serial.println("MMMMWWWO;;OWMMMMMWNOollc'..''''''''',:.:0NWx'......cl..dMMMMMMMMMMMWO,;0WMMMMMMM");
  Serial.println("MMMMMMMMK:,dXWWNkc;,......',,,,,,,,,,'.:0Ko.......cXd..oK00KNN0OOOOo,cKMMMMMMMMM");
  Serial.println("MMMMMMMMMNx,;ONd........,,..    ...... :0Oo'.....,OWx..:;..':lokkc.'xNMWMMMMMMMM");
  Serial.println("MMMMMMMMMMWKc,c,.;cllc,..,::loll:,.....:0XWd......;xc..''..'':ddc,lKWMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMW0l',oO00Okc..'o000KKOxodo.:KNMx........cxkOx,lKOo,'l0WWWMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMMMWKo;,cx0K0d'..ckOkkkkxxl.:0XMx...;l...'xNWNkoo:;o0WMMMMMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMMMMMMNOl:;:lkd:coxOOOkkkkl.:0XK:...oXx...'lxl::lONWWWMMMMMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMMMMMMMMWNOdc:;:cloodkOOkko.:Ox,...oKXO:...,co0NWMMMMMMMMMMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMMMMMMMMMMMMWN0xoc:;;,;:::;..'....':ccclok0XWMMMMMMMMMMMMMMMMMMMMMMMM");
  Serial.println("MMMMMMMMMMMMMMMMMMMMMMMMMMMWWNXOkdoc::;::::cldkOKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
*/
}