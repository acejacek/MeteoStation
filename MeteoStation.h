// Uncomment to enable printing out nice debug messages.
#define METEO_DEBUG

// Setup debug printing macros.
#ifdef METEO_DEBUG
  #define DEBUG(...) { Serial.print(__VA_ARGS__); }
  #define DEBUG_LN(...) { Serial.println(__VA_ARGS__); }
#else
  #define DEBUG(...) {}
  #define DEBUG_LN(...) {}
#endif

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <LiquidCrystal.h>
#include <math.h>
#include "DHT.h"

