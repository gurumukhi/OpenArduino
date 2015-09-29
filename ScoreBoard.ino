#include <LiquidCrystal.h>

const int RunPlusPin = 6;
const int RunMinusPin = 7;
const int BallsPlusPin = 10;
const int BallsMinusPin = 13;
const int WicketPlusPin = 8;
const int WicketMinusPin = 9;
int RunPlus = 0;   
int RunMinus = 0;   
int RunsCount = 0;
int BallsPlus = 0;   
int BallsMinus = 0;   
int BallsCount = 0;
int OverCount = 0;
int WicketPlus = 0;   
int WicketMinus = 0;   
int WicketCount = 0;
boolean RunPlusFlag;
boolean RunMinusFlag;
boolean BallsPlusFlag;
boolean BallsMinusFlag;
boolean WicketPlusFlag;
boolean WicketMinusFlag;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(115200);
  
  pinMode(RunPlusPin, INPUT);  
  pinMode(RunMinusPin, INPUT);  
  RunPlusFlag = true;   
  RunMinusFlag = true; 
  
  pinMode(BallsPlusPin, INPUT);  
  pinMode(BallsMinusPin, INPUT);  
  BallsPlusFlag = true;   
  BallsMinusFlag = true;
  
  pinMode(WicketPlusPin, INPUT);  
  pinMode(WicketMinusPin, INPUT);  
  WicketPlusFlag = true;   
  WicketMinusFlag = true;   
  lcd.begin(16,2);
}

void loop() {
  RunPlus = digitalRead(RunPlusPin);
  RunMinus = digitalRead(RunMinusPin);  
  WicketPlus = digitalRead(WicketPlusPin);
  WicketMinus = digitalRead(WicketMinusPin);  
  BallsPlus = digitalRead(BallsPlusPin);
  BallsMinus = digitalRead(BallsMinusPin);  
 
  if (RunPlus == HIGH) {  
    if(RunPlusFlag){  
        RunsCount += 1;
        RunPlusFlag = !RunPlusFlag;
  lcd.print("Score: ");
    }
  }
  else {
    RunPlusFlag = !RunPlusFlag;
  }
  if (RunMinus == HIGH) {  
    if(RunMinusFlag && RunsCount > 0){  
        RunsCount -= 1;
        RunPlusFlag = !RunPlusFlag;
    }
  }
  else {
    RunMinusFlag = !RunMinusFlag;
  }

  if (WicketPlus == HIGH) {  
    if(WicketPlusFlag){  
        WicketCount += 1;
        WicketPlusFlag = !WicketPlusFlag;
    }
  }
  else {
    WicketPlusFlag = !WicketPlusFlag;
  }
  if (WicketMinus == HIGH) {  
    if(WicketMinusFlag && WicketCount > 0){  
        WicketCount -= 1;
        WicketPlusFlag = !WicketPlusFlag;
    }
  }
  else {
    WicketMinusFlag = !WicketMinusFlag;
  }

  if (BallsPlus == HIGH) {  
    if(BallsPlusFlag){
        if(BallsCount <6){
          BallsCount += 1;
        }
        else{
          BallsCount = 0;
          OverCount += 1;
        }
        BallsPlusFlag = !BallsPlusFlag;
    }
  }
  else {
    BallsPlusFlag = !BallsPlusFlag;
  }
  if (BallsMinus == HIGH) {  
    if(BallsMinusFlag && (BallsCount > 0 || OverCount > 0)){  
        if(BallsCount > 0){
          BallsCount -= 1;
        }
        else{
          BallsCount = 5;
          OverCount -= 1;
        }
        BallsPlusFlag = !BallsPlusFlag;
    }
  }
  else {
    BallsMinusFlag = !BallsMinusFlag;
  } 
  
  lcd.print("Score: ");
  lcd.print(RunsCount);
  lcd.print("/");
  lcd.print(WicketCount);
  lcd.print(" : ");
  lcd.print(OverCount);  
  lcd.print(".");
  lcd.print(BallsCount);  
  lcd.setCursor(1,2);
  lcd.print("- Ram Vaishnav ");
}
