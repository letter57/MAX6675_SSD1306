// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include "Arduino.h"
#include "max6675.h"
#include <Wire.h>
#include <Adafruit_TinyUSB.h>
#include <Adafruit_SSD1306.h>

/**
 * @brief       MAX6675 GPIO definition
 * 
 * @details     thermoDO = 17  ->  P0.17
 *              thermoCS = 21  ->  P0.21
 *              thermoCLK = 14 ->  P0.14
 */
int thermoDO = 17;
int thermoCS = 21;
int thermoCLK = 14;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

/**
 * @brief       SSD1306 GPIO definition
 * 
 * @details     SSD1306_SDA_PIN 35  ->  P1.03
 *              SSD1306_SCL_PIN 44  ->  P1.12
 */
#define SSD1306_SDA_PIN 35
#define SSD1306_SCL_PIN 44

/**
 * @brief       OLED Value Definition.
 * 
 */
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/**
 * @brief       Register Definition.
*/
static float Celsius;

/**
 * @brief       
 * 
 */
void setup()
{
    Wire.setPins(SSD1306_SDA_PIN, SSD1306_SCL_PIN);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();

    // Draw a single pixel in white
    display.drawPixel(10, 10, SSD1306_WHITE);   
    Serial.begin(9600); 
    Serial.println("MAX6675 test");
    // wait for MAX chip to stabilize
    delay(500);
}

/**
 * @brief       
 * 
 */
void loop()
{
    // basic readout test, just print the current temp
  
    Serial.print("C = "); 
    Celsius = thermocouple.readCelsius();
    Serial.println(Celsius);
    
    //Serial.print("F = ");
    //Serial.println(thermocouple.readFahrenheit());
 
    // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
    //delay(1000);

    display.clearDisplay();
    display.setCursor(0,20);             // Start at top-left corner  
    display.setTextSize(2);              // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.print(F("C = ")); display.println(Celsius, BIN);

    display.display();
    delay(1000);
}