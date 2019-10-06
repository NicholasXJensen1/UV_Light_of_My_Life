/* Si1145 UV Sensor I2C Display
 mjhughes for allaboutcircuits.com
 Connect the LCD and UV sensor to 5v, Gnd
 Connect LCD & UV SDA to Arduino analog 4
 Connect LCD & UV SCL to Arduino analog 5
 On include lines, use "" for header files in same directory
 or use <> if you installed the libraries
*/


#include <Wire.h>                      // I²C library
#include <LiquidCrystal_I2C.h>         // control the LCD
#include <Adafruit_VEML6070.h>            // read the UV sensor


Adafruit_VEML6070 uv = Adafruit_VEML6070();
const int threshold = 10; // Light emmitted on sunny day
const int RELAY1 = 7; // Relay is in digital pin 7

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()                            // initialization code
{  
  Serial.begin(9600);
  Serial.println("VEML6070 Test");
  uv.begin(VEML6070_1_T);  // pass in the integration time constant
  lcd.init();                           // initialize the lcd 
  lcd.backlight();                      // turn backlight on
  pinMode(RELAY1, OUTPUT);    //Sets relay pin as output
  digitalWrite(RELAY1, HIGH);   //Sets relays to off  from the start
}

void loop(){                             // main program loop

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("UV Light"); lcd.setCursor(0,1); lcd.print("Intensity:");  
  lcd.print(uv.readUV());
  delay(1000);                           // Set an appropriate refresh rate for the application

   Serial.print("UV light level: ");
  Serial.println(uv.readUV());
  delay(1000);

    if (uv.readUV()< threshold){
   digitalWrite(RELAY1, LOW); // TURNS RELAY ON, LIGHT ON
  }
    else{
      digitalWrite(RELAY1, HIGH);
    }
    delay(1000);
}
