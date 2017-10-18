//Arduino Uno receiver Code
#include <LiquidCrystal.h> 

// pin variables
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //These are the pins used on this shield

char str[4];
bool dispFlag = false;
void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);              // start the lcd object
}

void loop() {
  int i=0;

  if (Serial.available()) {
    delay(100); //allows all serial sent to be received together
    while(Serial.available() && i<4) {
      str[i++] = Serial.read();
    }
    str[i++]='\0';
    dispFlag = true;
  }

  if(i>0) {
    lcd.setCursor(0,0);
    lcd.print(str);
  }
}
