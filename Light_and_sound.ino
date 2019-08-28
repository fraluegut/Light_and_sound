
/**************************************************************************
Javier Luengo
21/03/2019
Sheffield
U.K.
 **************************************************************************/
//BME280

#include "Seeed_BME280.h"
#include <Wire.h>

// Light
#include <BH1750.h>


//OLED
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#ifdef ADAFRUIT_HALLOWING
  #define TFT_CS        39 // Hallowing display control pins: chip select
  #define TFT_RST       37 // Display reset
  #define TFT_DC        38 // Display data/command select
  #define TFT_BACKLIGHT  7 // Display backlight pin
#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif


// For 1.44" and 1.8" TFT with ST7735 (including HalloWing) use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

BME280 bme280;
BH1750 lightMeter(0x23);

void setup(void) {
  Serial.begin(9600);
  Serial.print("Initializing...");
  
  // OR use this initializer (uncomment) if using a 1.44" TFT:
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab

  Wire.begin();
  
  if(!bme280.init()){
    Serial.println("Device error!");
  }
  
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2)) {
    Serial.println(F("BH1750 Advanced begin"));
  }
  else {
    Serial.println(F("Error initialising BH1750"));
    
  Serial.println(F("Initialized"));
}
}

void loop() {
float pressure;
float lux = lightMeter.readLightLevel();

  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("Light &");
  tft.println("Sound:");
  tft.println("");
  
  tft.setTextSize(1);  
  tft.print("Temp: ");
  tft.setTextColor(ST77XX_GREEN);
  tft.print(bme280.getTemperature());
  tft.setTextColor(ST77XX_WHITE);
  tft.println(" C");
  tft.println("");

  tft.print("Hum: ");
  tft.setTextColor(ST77XX_GREEN);
  tft.print(bme280.getHumidity());
  tft.setTextColor(ST77XX_WHITE);
  tft.println("%");
  tft.println("");

  tft.print("Light: ");
  tft.setTextColor(ST77XX_GREEN);
  tft.print(lux);
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Lx");
  tft.println("");

  tft.print("Preasure: ");
  tft.setTextColor(ST77XX_GREEN);
  tft.print(pressure = bme280.getPressure());
  tft.setTextColor(ST77XX_WHITE);
  tft.println("%");
  tft.println("");

  //get and print temperatures
  Serial.print("Temp: ");
  Serial.print(bme280.getTemperature());
  Serial.println("C");//The unit for  Celsius because original arduino don't support special symbols
  
  //get and print atmospheric pressure data
  Serial.print("Pressure: ");
  Serial.print(pressure = bme280.getPressure());
  Serial.println("Pa");

  //get and print altitude data
  Serial.print("Altitude: ");
  Serial.print(bme280.calcAltitude(pressure));
  Serial.println("m");

  //get and print humidity data
  Serial.print("Humidity: ");
  Serial.print(bme280.getHumidity());
  Serial.println("%");

  Serial.print("Lux: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}
