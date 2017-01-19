#include "MeteoStation.h"

#define DHTPIN 9     // what digital pin we're connected to
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

//degree symbol
byte degreeChar[8] = {
  B00110,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

//thermometer1 symbol
byte thermo1Char[8] = {
  B00100,
  B01010,
  B01010,
  B01110,
  B11111,
  B11111,
  B01110,
};

//thermometer2 symbol
byte thermo2Char[8] = {
  B01110,
  B01010,
  B01010,
  B01110,
  B01110,
  B01110,
  B00100,
};

void setup() { 

#ifdef METEO_DEBUG
  Serial.begin(9600);
#endif

  DEBUG_LN("MeteoStation Test");

  dht.begin();
  
  if(!bmp.begin())
  {
    DEBUG("Ooops, no BMP085 detected ...");
    while(1);
  }
     
  //initiate LCD display
  lcd.begin(16, 2);
  
  //create user-defined characters for LCD display
  lcd.createChar(0, degreeChar);
  lcd.createChar(1, thermo1Char);
  lcd.createChar(2, thermo2Char);

  //switch off the led on board
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  delay(2000);

  sensors_event_t event;
  bmp.getEvent(&event);

  float temperature = dht.readTemperature();
  DEBUG("temp: "); DEBUG_LN(temperature);
  
  float humidity = dht.readHumidity();
  DEBUG("hum: "); DEBUG_LN(humidity);
 
  lcd.setCursor(0, 0);
  lcd.write(word(1));
  lcd.print(" " + String(round(temperature)));
  lcd.write(word(0));
  lcd.print("C    " + String(round(humidity)) + "%");

  float pressure = event.pressure;
  DEBUG("pressure: "); DEBUG_LN(pressure);

  lcd.setCursor(0, 1);
  lcd.print("    " + String(round(pressure)) + " hPa");
}
