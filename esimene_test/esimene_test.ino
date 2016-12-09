// include the library code:
#include <LiquidCrystal.h>
#include <DHT.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 9, 8, 7, 5);
#define DHTPIN 3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float hum, temp;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  lcd.clear();
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print(hum);
  delay(5000);
}

