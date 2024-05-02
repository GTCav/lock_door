#include <lock_door.h>

#define ON TFT_GREEN
#define OFF TFT_RED
#define PRESS 10

#define CLOSE -1
#define CLEAR -2

#define CLOSED 0
#define OPENED 1

#define DOOR_1 48// led
#define DOOR_2 49// led

short setedPassword[3] = {1, 2, 3};

LockDoor::LockDoor(MCUFRIEND_kbv TFT, TouchScreen TS) : 
    tft(TFT), ts(TS), LCD_RESET(A4), LCD_CS(A3), LCD_RS(A2), LCD_WR(A1), LCD_RD(A0), YP(A3), XM(A2), YM(9), XP(8), TS_LEFT(126), TS_RT(937), TS_TOP(901), TS_BOT(89){}

void LockDoor::begin(){
    tft.begin(tft.readID());
    tft.fillScreen(TFT_BLACK);
    door_1.attach(50);
    door_1.write(0);
    pinMode(DOOR_1, OUTPUT);
    digitalWrite(DOOR_1, LOW);
    door_2.attach(51);
    door_2.write(0);
    pinMode(DOOR_2, OUTPUT);
    digitalWrite(DOOR_2, LOW);
}

void LockDoor::clearScreen(uint16_t c){
  tft.fillScreen(c);
}

TSPoint LockDoor::wasTouched(int MINPRESSURE){
  TSPoint p;
  do{
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  }while(p.z<=MINPRESSURE);
  p.x = map(p.x, TS_LEFT, TS_RT, 0, 240);
  p.y = map(p.y, TS_BOT, TS_TOP, 0, 320);
  return p;
}

void LockDoor::startScreen(){
  tft.setCursor(15, 15);
  tft.setTextSize(4);
  tft.println("LOCK DOOR");

  tft.drawFastHLine(0, 59, 240, TFT_WHITE);
  tft.drawFastHLine(0, 60, 240, TFT_WHITE);
  tft.drawFastHLine(0, 61, 240, TFT_WHITE);

  tft.setCursor(12, 65);
  tft.setTextSize(2);
  tft.println("Microcontroladores");
  tft.println();
  tft.setTextSize(2);
  tft.println("Profa.: Fernanda");
  tft.println("Aluno: Gabriel C.");
  tft.println();
  tft.setTextSize(1);
  tft.println("Toque para continuar...");
}



// CONFIGURAÇÕES DO TECLADO
float keySize[2] = {50, 50};
long keyColor = OFF;
float outterDisplaySize[2] = {160, 50};
float innerDisplaySize[2] = {150, 40};

float outterDisplayPos[2] = {40, 20};
float innerDisplayPos[2] = {45, 25};

float numSize = 3;
float numPosAdjust[2] = {9, 12};

float numOne[2] = {40, 80};
float numTwo[2] = {95, 80};
float numThree[2] = {150, 80};
float numFour[2] = {40, 135};
float numFive[2] = {95, 135};
float numSix[2] = {150, 135};
float numSeven[2] = {40, 190};
float numEight[2] = {95, 190};
float numNine[2] = {150, 190};
float numZero[2] = {95, 245};

float closeButton[2] = {40, 245};
float clrButton[2] = {150, 245};

void LockDoor::drawKeyboard(int key){
  switch (key)
  {
  case 1:
    tft.fillRect(numOne[0], numOne[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numOne[0]-numPosAdjust[0])+(keySize[0])/2, (numOne[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("1");
    break;

  case 2:
    tft.fillRect(numTwo[0], numTwo[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numTwo[0]-numPosAdjust[0])+(keySize[0])/2, (numTwo[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("2");
    break;

  case 3:
    tft.fillRect(numThree[0], numThree[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numThree[0]-numPosAdjust[0])+(keySize[0])/2, (numThree[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("3");
    break;

  case 4:
    tft.fillRect(numFour[0], numFour[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numFour[0]-numPosAdjust[0])+(keySize[0])/2, (numFour[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("4");
    break;

  case 5:
    tft.fillRect(numFive[0], numFive[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numFive[0]-numPosAdjust[0])+(keySize[0])/2, (numFive[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("5");
    break;

  case 6:
    tft.fillRect(numSix[0], numSix[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numSix[0]-numPosAdjust[0])+(keySize[0])/2, (numSix[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("6");
    break;

  case 7:
    tft.fillRect(numSeven[0], numSeven[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numSeven[0]-numPosAdjust[0])+(keySize[0])/2, (numSeven[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("7");
    break;

  case 8:
    tft.fillRect(numEight[0], numEight[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numEight[0]-numPosAdjust[0])+(keySize[0])/2, (numEight[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("8");
    break;

  case 9:
    tft.fillRect(numNine[0], numNine[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numNine[0]-numPosAdjust[0])+(keySize[0])/2, (numNine[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("9");
    break;

  case 0:
    tft.fillRect(numZero[0], numZero[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numZero[0]-numPosAdjust[0])+(keySize[0])/2, (numZero[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("0");
    break;

  case CLOSE:
    tft.fillRect(closeButton[0], closeButton[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((closeButton[0]-numPosAdjust[0])+(keySize[0])/2, (closeButton[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("X");
    break;

  case CLEAR:
    tft.fillRect(clrButton[0], clrButton[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((clrButton[0]-numPosAdjust[0])+(keySize[0])/2, (clrButton[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("C");
    break;

  default:
    tft.fillRect(outterDisplayPos[0], outterDisplayPos[1], outterDisplaySize[0], outterDisplaySize[1], TFT_RED);//visor
    tft.fillRect(innerDisplayPos[0], innerDisplayPos[1], innerDisplaySize[0], innerDisplaySize[1], TFT_BLACK);//visor

    tft.fillRect(numOne[0], numOne[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numOne[0]-numPosAdjust[0])+(keySize[0])/2, (numOne[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("1");

    tft.fillRect(numTwo[0], numTwo[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numTwo[0]-numPosAdjust[0])+(keySize[0])/2, (numTwo[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("2");

    tft.fillRect(numThree[0], numThree[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numThree[0]-numPosAdjust[0])+(keySize[0])/2, (numThree[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("3");

    tft.fillRect(numFour[0], numFour[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numFour[0]-numPosAdjust[0])+(keySize[0])/2, (numFour[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("4");

    tft.fillRect(numFive[0], numFive[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numFive[0]-numPosAdjust[0])+(keySize[0])/2, (numFive[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.print("5");

    tft.fillRect(numSix[0], numSix[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numSix[0]-numPosAdjust[0])+(keySize[0])/2, (numSix[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("6");

    tft.fillRect(numSeven[0], numSeven[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numSeven[0]-numPosAdjust[0])+(keySize[0])/2, (numSeven[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("7");

    tft.fillRect(numEight[0], numEight[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numEight[0]-numPosAdjust[0])+(keySize[0])/2, (numEight[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("8");

    tft.fillRect(numNine[0], numNine[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numNine[0]-numPosAdjust[0])+(keySize[0])/2, (numNine[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("9");

    tft.fillRect(numZero[0], numZero[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((numZero[0]-numPosAdjust[0])+(keySize[0])/2, (numZero[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("0");

    tft.fillRect(clrButton[0], clrButton[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((clrButton[0]-numPosAdjust[0])+(keySize[0])/2, (clrButton[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("C");

    tft.fillRect(closeButton[0], closeButton[1], keySize[0], keySize[1], keyColor);
    tft.setCursor((closeButton[0]-numPosAdjust[0])+(keySize[0])/2, (closeButton[1]-numPosAdjust[1])+(keySize[1])/2);
    tft.setTextSize(numSize);
    tft.print("X");

    break;
  }
}

//CONFIGURAÇÕES DO MENU PRINCIPAL
float buttonSize[2] = {150, 50};
float passwordButtonSize[2] = {50, 50};

float buttonOnePos[2] = {45, 105};
float buttonTwoPos[2] = {45, 160};
float passwordButtonPos[2] = {180, 260};

float centerAdjustX = 33;
float centerAdjustY = 17;

long buttonStatus[2] = {OFF, OFF};
long passwordButtonStatus = OFF;

void LockDoor::doorSelectMenu(){
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(0, 10);
  tft.print("Selecione uma porta:");
  
  tft.fillRect(buttonOnePos[0], buttonOnePos[1], buttonSize[0], buttonSize[1], buttonStatus[0]);
  tft.setCursor(buttonOnePos[0]+centerAdjustX, buttonOnePos[1]+centerAdjustY);
  tft.print("Porta 1");

  tft.fillRect(buttonTwoPos[0], buttonTwoPos[1], buttonSize[0], buttonSize[1], buttonStatus[1]);
  tft.setCursor(buttonTwoPos[0]+centerAdjustX, buttonTwoPos[1]+centerAdjustY);
  tft.print("Porta 2");

  tft.fillRect(passwordButtonPos[0], passwordButtonPos[1], passwordButtonSize[0], passwordButtonSize[1], passwordButtonStatus);
  tft.setCursor(passwordButtonPos[0]+passwordButtonSize[0]/2 -12, passwordButtonPos[1]+passwordButtonSize[1]/2 -4);
  tft.setTextSize(1);
  tft.print("LOCK");
}

bool LockDoor::isLocked(){
  if(passwordButtonStatus == OFF){return true;}else{return false;}
}

bool LockDoor::isPasswordCorrect(short password[3]){
  for(int i=0; i<3; i++){
    if(password[i]!=setedPassword[i]){return false;}
  }
  return true;
}

bool LockDoor::requestPassword(){
  clearScreen(TFT_BLACK);
  drawKeyboard('a');

  short password[3];
  int cont = 1;
  int msg; //-1 -> fecha janela
           //-2 -> limpa display

  do{
    msg = isKeyPressed(wasTouched(PRESS).x, wasTouched(PRESS).y);
    if(msg==CLOSE){return false;}
    else if(msg>=0){showPressedKeyOnDisplay(msg, cont);password[cont-1]=msg;}
    cont++;
    if(msg==CLEAR){cont=1;}
  }while(cont<=3 && msg!=CLOSE);
  if(isPasswordCorrect(password)){return true;}else{return false;}
}

int LockDoor::isKeyPressed(int x, int y){
  int msg;
  if(x >= numOne[0] && x <= (numOne[0]+keySize[0])){// Primeira coluna
    if(y >= numOne[1] && y <= (numOne[1]+keySize[1])){
      //Número 1
      clickAnimation(1);
      msg = 1;
    }
    else if(y >= numFour[1] && y <= (numFour[1]+keySize[1])){
      //Número 4
      clickAnimation(4);
      msg = 4;
    }
    else if(y >= numSeven[1] && y <= (numSeven[1]+keySize[1])){
      //Número 7
      clickAnimation(7);
      msg = 7;
    }
    else if(y >= closeButton[1] && y <= (closeButton[1]+keySize[1])){
      //Fechar
      clickAnimation(CLOSE);
      msg=CLOSE;
    }  
  }

  else if(x >= numTwo[0] && x <= (numTwo[0]+keySize[0])){// Segunda coluna
    if(y >= numTwo[1] && y <= (numTwo[1]+keySize[1])){
      //Número 2
      clickAnimation(2);
      msg = 2;
    }
    else if(y >= numFive[1] && y <= (numFive[1]+keySize[1])){
      //Número 5
      clickAnimation(5);
      msg = 5;
    }
    else if(y >= numEight[1] && y <= (numEight[1]+keySize[1])){
      //Número 8
      clickAnimation(8);
      msg = 8;
    }
    else if(y >= numZero[1] && y <= (numZero[1]+keySize[1])){
      //Número 0
      clickAnimation(0);
      msg = 0;
    } 
  }

  else if(x >= numThree[0] && x <= (numThree[0]+keySize[0])){// Segunda coluna
    if(y >= numThree[1] && y <= (numThree[1]+keySize[1])){
      //Número 3
      clickAnimation(3);
      msg = 3;
    }
    else if(y >= numSix[1] && y <= (numSix[1]+keySize[1])){
      //Número 6
      clickAnimation(6);
      msg = 6;
    }
    else if(y >= numNine[1] && y <= (numNine[1]+keySize[1])){
      //Número 9
      clickAnimation(9);
      msg = 9;
    } 
    else if(y >= clrButton[1] && y <= (clrButton[1]+keySize[1])){
      //Limpar display
      clickAnimation(CLEAR);
      clearDisplay();
      msg=CLEAR;
    }     
  }
  return msg;
}

short doorStatus[2] = {CLOSED, CLOSED};

void LockDoor::detectPressedButton(int x, int y){
  if((x >= passwordButtonPos[0]) && (x <= passwordButtonPos[0]+passwordButtonSize[0])){
    if(y >= passwordButtonPos[1] && y<= (passwordButtonPos[1]+passwordButtonSize[1])){
      if(requestPassword()){
        if(isLocked()){passwordButtonStatus = ON;}else{passwordButtonStatus = OFF;}
        clearScreen(TFT_BLACK);
        doorSelectMenu();
      }
      else{
        tft.fillCircle(120, 160, 50, TFT_ORANGE);
        tft.setTextColor(TFT_BLACK);
        tft.setTextSize(3);
        tft.setCursor(120-9, 160-12);
        tft.print("X");
        delay(2000);
        clearScreen(TFT_BLACK);
        doorSelectMenu();
      }
    }
  }

  if(!isLocked()){
    if ((x >= buttonOnePos[0]) && (x <= (buttonOnePos[0]+buttonSize[0]))){
      if((y >= buttonOnePos[1]) && (y <= (buttonOnePos[1]+buttonSize[1]))){
        if(buttonStatus[0] == OFF){
          buttonStatus[0] = ON;
          doorStatus[0] = OPENED;
        }
        else{
          buttonStatus[0] = OFF;
          doorStatus[0] = CLOSED;
        }
        doorSelectMenu();
        lockControl(door_1, doorStatus[0], 1);
      }

      if((y >= buttonTwoPos[1]) && (y <= (buttonTwoPos[1]+buttonSize[1]))){
        if(buttonStatus[1] == OFF)
        {
          buttonStatus[1] = ON;
          doorStatus[1] = OPENED;
        }
        else{
          buttonStatus[1] = OFF;
          doorStatus[1] = CLOSED;
        }
        doorSelectMenu();
        lockControl(door_2, doorStatus[1], 2);
      }
    }
  }
}

void LockDoor::lockControl(Servo lock, int act, int door){
  if(act==OPENED){
    lock.write(90);
  }
  else if(act==CLOSED){
    lock.write(0);
  }

  if(door==1){
    digitalWrite(DOOR_1, !digitalRead(DOOR_1));
  }
  else if(door==2){
    digitalWrite(DOOR_2, !digitalRead(DOOR_2));
  }
}

void LockDoor::showPressedKeyOnDisplay(int key, int cont){
  switch (cont)
  {
  case 1:
    tft.setCursor(innerDisplayPos[0]+keySize[0]/2-numPosAdjust[0], innerDisplayPos[1]+innerDisplaySize[1]/2-numPosAdjust[1]);
    tft.setTextSize(numSize);
    tft.print(key);
    break;

  case 2:
    tft.setCursor(innerDisplayPos[0]+keySize[0]/2+keySize[0]-numPosAdjust[0], innerDisplayPos[1]+innerDisplaySize[1]/2-numPosAdjust[1]);
    tft.setTextSize(numSize);
    tft.print(key);
    break;
  
  case 3:
    tft.setCursor(innerDisplayPos[0]+keySize[0]/2+2*keySize[0]-numPosAdjust[0], innerDisplayPos[1]+innerDisplaySize[1]/2-numPosAdjust[1]);
    tft.setTextSize(numSize);
    tft.print(key);
    break;

  default:
    break;
  }
}

void LockDoor::clearDisplay(){
  tft.fillRect(outterDisplayPos[0], outterDisplayPos[1], outterDisplaySize[0], outterDisplaySize[1], TFT_RED);//visor
  tft.fillRect(innerDisplayPos[0], innerDisplayPos[1], innerDisplaySize[0], innerDisplaySize[1], TFT_BLACK);//visor
}

void LockDoor::clickAnimation(int key){
  keyColor = ON;
  drawKeyboard(key);
  delay(100);
  keyColor = OFF;
  drawKeyboard(key);
}