#include <Boards.h>
#include <Firmata.h>

/* 
  The circuit:
 * LCD RS pin to digital pin 2
 * LCD Enable pin to digital pin 3
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// include the library code:
#include <LiquidCrystal.h>
#include <SPI.h>
#include <EEPROM.h>
#include <boards.h>
#include <RBL_nRF8001.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


byte p20[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};
byte p40[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};
byte p60[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};
byte p80[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
};
byte p100[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  //TODO : disabling this will make the bluetooth connection fail. The device does not show up.
 //TODO : When we enable this then the LCD shows garbled messages. 
  ble_set_pins(3, 2);

  ble_begin();
  
  //Create Serial Object
  Serial.begin(9600);
  
  //TODO: Does not do anything, the LCD shows garbled text.  
  //something to do with the 3 and 2 pins ?
  lcd.print("Hello Worldsome");
  
  //Make progress characters
  lcd.createChar(0, p20);
  lcd.createChar(1, p40);
  lcd.createChar(2, p60);
  lcd.createChar(3, p80);
  lcd.createChar(4, p100);
}

void loop() {
  //TODO : enabling any write operation here makes the BLE shield not show up
  // in the simple chat application. 
 //lcd.setCursor(0,1);
 //lcd.print("                ");   
 
 /*for (int i = 0; i<16; i++)
 {
   
   for (int j=0; j<5; j++)
   {
      lcd.setCursor(i, 1);   
      lcd.write(j);
      delay(100);
    } 
 }*/

  if (ble_available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (ble_available() > 0) {
      // display each character to the LCD
      lcd.write(ble_read());
    }
  }
  
  ble_do_events();
}




