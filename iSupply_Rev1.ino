/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
  as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8

#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF


#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

 Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */
 Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);  

float voltage = 3.86674;
float Current = 2.93457;
float Power = 5.032347;
float Batt_Mon = 3.86674;

void setup(void) 
{
  Serial.begin(115200);

  display.begin();
  uint16_t time = millis();
  
  display.fillScreen(BLACK);
  time = millis() - time; 




  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
   ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
  delay(500);
  tftPrint1();
}

void loop(void) 
{


  int16_t adc0, adc1, adc2, adc3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);

  int sensorValue = analogRead(A0);
  float voltage = sensorValue/38.881 - 0.49;
  Current = adc1* 0.0083238312- 0.47;
  //Serial.print(voltage);
  //Batt_Mon = adc0/1000;


if (Current < 0)
  { Current = 0; }
if (voltage < 0)
  { voltage = 0; }

Power =   (Current * 1000 * voltage)/1000;


//  Serial.print(0);
 // Serial.print(" ");
 // Serial.print(adc0);
 // Serial.print(" ");
 // Serial.print(adc1);
//  Serial.print("    ");
//  Serial.print(Current);
 // Serial.print(voltage);
 // Serial.print(" ");
//  Serial.println(" ");


  display.setCursor(50, 24);
  display.fillRect(43, 22, 44, 10, BLACK),
  display.setTextColor(RED);  
  display.setTextSize(1);
  display.print(voltage, 3);



  display.setCursor(54, 40);
  display.fillRect(43, 38, 40, 10, BLACK),
  display.setTextColor(GREEN);  
  display.setTextSize(1);
  display.print(Current, 2);
  
   display.setCursor(54, 55);
  display.fillRect(33, 52, 50, 10, BLACK),
  display.setTextColor(BLUE);  
  display.setTextSize(1);
  display.print(Power, 1);

}


void tftPrint1() 
{
  display.fillScreen(BLACK);
  display.setCursor(0, 0);
  display.fillRoundRect(0, 0, 96, 20, 4, WHITE);
  display.setCursor(5, 5);
  display.setTextColor(RED);  
  display.setTextSize(2);
  display.print("iSupply");
  display.setCursor(6, 4);
  display.setTextColor(GREEN);
  display.print("iSupply");
  display.setCursor(7, 3);
  display.setTextColor(BLUE);
  display.print("iSupply");
  
  display.setCursor(0, 24);
  display.setTextColor(RED);  
  display.setTextSize(1);
  display.print("Voltage");
  display.print("        V");
  display.println("");
  display.println("");

  //display.setCursor(10, 30);
  display.setTextColor(GREEN);
  display.setTextSize(1);
  display.print("Current");
  display.print("       mA");
  display.println("");
  display.println("");

  //display.setCursor(10, 40);
  display.setTextColor(BLUE);
  display.setTextSize(1);
  display.print("Power");
  display.print("         mW");
}
