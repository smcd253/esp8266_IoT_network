#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

char dataIn[8];
bool dispChangeFlag = true;
void setup() {
  Serial.begin(115200); // arduino-esp data line
  
  // INITIALIZE OLED SCREEN
  Wire.begin();  
  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(0,0);              // Set cursor position, start of line 0
  oled.putString("Timer");
  oled.setTextXY(1,0);              // Set cursor position, start of line 1
  oled.putString("Spencer M");
  oled.setTextXY(2,0);              // Set cursor position, start of line 2
  oled.putString("Los Angeles,");
  oled.setTextXY(2,13);             // Set cursor position, line 2 10th character
  oled.putString("CA");
}

void loop() {
  int i=0;

  if (Serial.available()) {
    delay(100); //allows all serial sent to be received together
    while(Serial.available() && i<8) {
      dataIn[i++] = Serial.read();
    }
    dataIn[i++]='\0';
  }

  if(i>0) {
    // time data conversion.
    char sec[2], _min[2], hr[2], day[2];
    strncpy(sec, dataIn, 2);
    strncpy(_min, dataIn + 2, 2);
    strncpy(hr, dataIn + 4, 2);
    strncpy(day, dataIn + 6, 2);

    // clear screen once
    if (dispChangeFlag)
    {
      oled.clearDisplay();
      dispChangeFlag = false;
    }
    
    oled.setTextXY(1,0);
    oled.putString("T: ");
    oled.setTextXY(1,3);
    oled.putString(hr);
    oled.setTextXY(1,5);
    oled.putString(":");
    oled.setTextXY(1,6);
    oled.putString(_min);
    oled.setTextXY(1,8);
    oled.putString(":");
    oled.setTextXY(1,9);
    oled.putString(sec);
    oled.setTextXY(2,0);
    oled.putString("Day: ");
    oled.setTextXY(2,5);
    oled.putString(day);

    // DEBUG
    oled.setTextXY(3,0);
    oled.putString("DATA: ");
    oled.setTextXY(3,6);
    oled.putString(dataIn);
  }
}
