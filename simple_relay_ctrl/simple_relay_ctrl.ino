//GroBro.cpp

//#include <dht.h>
//#include <time.h>
//#include <TimeLib.h>
#include <Wire.h>
//#include <DS1307RTC.h>
#include <LiquidCrystal.h>

//dht DHT;
#define DHT11_PIN 11 // pin location of DHT11 hum/temp sensor
// pin variables
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //These are the pins used on this shield
// relay output pins
int drip = 3;
int agitator = 2;
int humidifier = 1;
int fans = 0;


/*-----( Declare LCD Shield Button Constants )-----*/
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

/*-----( Declare LCD Shield Button Variables )-----*/
int lcd_key       = 0;
int adc_key_in    = 0;
int adc_key_prev  = 0;

// other constancts
#define disp_size 16

// selecter variables
int fn_sel = 5;
int prev_fn_sel = 5;
int disp_sel = 5;

void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT); // drip pump
  //pinMode(7, OUTPUT); // agitator pump
  //pinMode(6, OUTPUT); // humidifier/fan
  //pinMode(5, OUTPUT); // circulation fans

  digitalWrite(13, HIGH); // turn off output 13

  // ---------------- LCD ------------------
  lcd.begin(16, 2);              // start the lcd object
  lcd.setCursor(0,0);
  //lcd.print("GroBro"); 
  lcd.setCursor(10,1);
  //lcd.print("A="); // For display of A0 Analog values from button push
  //setTime(hours, minutes, seconds, days, months, years);
}

void loop() // main loop
{
  fn_sel = check_buttons();
  
  switch (fn_sel)
  {
    case 0:
      disp_sel = 0;
      digitalWrite(13, LOW);
      prev_fn_sel = fn_sel;
      fn_sel = 5;
      break;
    case 1:
      disp_sel = 1;
      digitalWrite(13, HIGH);
      prev_fn_sel = fn_sel;
      fn_sel = 5;
      break;
    case 5: //default
      break;
  }

  switch (disp_sel)
  {
    case 0:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Relay ENABLED");
      lcd.setCursor(0,1);
      lcd.print("Press");
      disp_sel = 5;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Relay DISABLED");
      lcd.setCursor(0,1);
      lcd.print("Press");
      disp_sel = 5;
      break;
    case 5: //default
      lcd.setCursor(0,1);
      lcd.print("No Press");
      break;
  }
  

  
  // wait 5ms
  delay(5);            
}

int check_buttons()
{
    lcd_key = read_LCD_buttons();  // read the buttons

  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
  case btnRIGHT: // 0
    {
      //return 0;
      break;
    }
  case btnLEFT: // 1
    {
      return 1;
      break;
    }
  case btnUP: // 2
    {
      return 0; // usable - replace right
      break;
    }
  case btnDOWN:// 3
    {
      //return 0; // usable - replace right
      break;
    }
  case btnSELECT: // 4
    {
      return 0; // usable - replace right
      break;
    }
  case btnNONE:// 5
    {
      return 5;
      break;
    }
  }/* --(end switch )-- */
}


int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor 
  delay(50); //switch debounce delay. Increase this delay if incorrect switch selections are returned.
  int k = (analogRead(0) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
  if (5 < abs(k)) return btnNONE;  // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close

  if (adc_key_in < 50)
  {
    adc_key_prev = lcd_key;
    return btnSELECT; // new button select
  }
  else if (adc_key_in < 195){
    }  //return btnUP;
  else if (adc_key_in < 250)
  {
    adc_key_prev = lcd_key;
    return btnUP; // new button up 
  }
  else if (adc_key_in < 555)
  {
    adc_key_prev = lcd_key;
    return btnDOWN; // new button down
  }
  else if (adc_key_in < 790)
  {
    adc_key_prev = lcd_key;
    return btnLEFT; // new button left
  }
  else if (adc_key_in > 1000)
  {
    return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  }
  return btnNONE;  // when all others fail, return this...
}

