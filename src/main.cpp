#include <Arduino.h>
#include <lock_door.h>

#define MINPRESSURE 10

// DEFINIÇÕES DE PINOS TFT LCD
#define LCD_RESET A4
#define LCD_CS A3
#define LCD_RS A2
#define LCD_WR A1
#define LCD_RD A0

/*____CALIBRAR TFT LCD_____*/
#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_LEFT 126
#define TS_RT   937
#define TS_TOP  901
#define TS_BOT  89
/*______FIM DA CALIBRAÇÃO______*/

MCUFRIEND_kbv tft(LCD_CS, LCD_RS, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //300 É A SENSITIVIDADE
LockDoor lkdoor(tft, ts);

void setup(){
  lkdoor.begin();
  lkdoor.startScreen();
  if((lkdoor.wasTouched(MINPRESSURE).x>=0) && (lkdoor.wasTouched(MINPRESSURE).y>=0)){
    lkdoor.clearScreen(TFT_BLACK);
    lkdoor.doorSelectMenu();
  }
}

void loop(){
  TSPoint p = lkdoor.wasTouched(MINPRESSURE);

  lkdoor.detectPressedButton(p.x, p.y);
}