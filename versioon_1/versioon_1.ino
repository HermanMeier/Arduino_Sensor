// include the library code:
#include <LiquidCrystal.h>
#include <DHT.h>
#include "Switch.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 9, 8, 7, 5);
#define DHTPIN 3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float hum, temp;

// Buttons
const int button1Pin = 10;
const int button2Pin = 6;
const int button3Pin = 2;
const int button4Pin = 4;

//int button1State=0, button2State=0, button3State=0, button4State=0;
int menuState = -1;
int cursorPos = 0;
int counter = 1;

Switch button1 = Switch(button1Pin, INPUT, HIGH);
Switch button2 = Switch(button2Pin, INPUT, HIGH);
Switch button3 = Switch(button3Pin, INPUT, HIGH);
Switch button4 = Switch(button4Pin, INPUT, HIGH);

long lastRead=0;

byte oKatus[8] = {
  B01110,
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
};
byte celsius[8] = {
  B10000,
  B00000,
  B01110,
  B10000,
  B10000,
  B10000,
  B01110,
};

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  dht.begin();

  //Button setup
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);

  lcd.createChar(0, oKatus);
  lcd.createChar(1, celsius);

  hum = dht.readHumidity();
  temp = dht.readTemperature();
}

void readDHT()  {
  //if (millis()-lastRead>2000) {
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    lcd.setCursor(0,0);
    lcd.print(temp);
    lcd.print(" ");
    lcd.write(byte(1));
    lcd.print(" ");
    lcd.print(hum);
    lcd.print(" %");
    lcd.setCursor(15,0);
  //}
  //lastRead=millis();
}

void initMenu(int menuState) {
  lcd.clear();
  if (menuState == 0)  {
    lcd.setCursor(0,1);
    lcd.print("M");
    lcd.write(byte(0));
    lcd.write(byte(0));
    lcd.print("da pikalt");
    lcd.setCursor(0,0);
    lcd.print(temp);
    lcd.print(" ");
    lcd.write(byte(1));
    lcd.print(" ");
    lcd.print(hum);
    lcd.print(" %");
  }

  else if (menuState == 1) {
    lcd.setCursor(0,0);
    lcd.print(counter);
    lcd.print(" h tagant");
    lcd.setCursor(0,1);
    lcd.print("Alusta");
  }
  lcd.setCursor(15,0);
  lcd.cursor();
}

void loop() {
  //Esimese menüü loomine
  if (menuState == -1)  {
    menuState = 0;
    initMenu(menuState);
  }
  
  button1.poll();
  button2.poll();
  button3.poll();
  button4.poll();
  
  if (menuState == 0)  {
    //Menüüs liikumine kahe esimese nupuga, esimene üles, teine alla
    if (button1.pushed() || button2.pushed()) {
      if (cursorPos==0) {
        cursorPos=1;
        lcd.setCursor(15, cursorPos);
      }
      else  {
        cursorPos=0;
        lcd.setCursor(15, cursorPos);
      }
    }
    /* Seda on siis vaja kui on üle kahe valiku menüüs
    if (button1State == HIGH) {
      if (menuState==0) menuState=1;
      else  menuState=0;
    }
    */
    //Menüüs valimine neljanda nupuga
    if (button4.pushed()) {
      if (cursorPos == 0) {
        readDHT();
      }
      if (cursorPos == 1){
        menuState = 1;
        cursorPos = 0;
        initMenu(menuState); 
      }
    }
  }
  if (menuState == 1) {
    //Menüüs liikumine kahe esimese nupuga, esimene üles, teine alla
    if (button1.pushed() || button2.pushed()) {
      if (cursorPos==0) {
        cursorPos=1;
        lcd.setCursor(15, cursorPos);
      }
      else  {
        cursorPos=0;
        lcd.setCursor(15, cursorPos);
      }
    }
    
    //Menüüs valimine neljanda nupuga
    if (button4.pushed()) {
      if (cursorPos == 0) {
        counter++;
        lcd.setCursor(0,0);
        lcd.print(counter);
        lcd.print(" h tagant");
        lcd.setCursor(15,0);
      }
      /*if (cursorPin == 1) {
        Alusta salvestamist
      }*/
    }
    
    //Menüüs tagasi kolmanda nupuga
    if (button3.pushed()) {
      menuState = 0;
      cursorPos = 0;
      initMenu(menuState);
    }
  }
}

