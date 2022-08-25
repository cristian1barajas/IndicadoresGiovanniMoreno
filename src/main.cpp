#include <Arduino.h>
#include <SPI.h>

// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls ‘Howdy’ across the matrix in a portrait (vertical) orientation.
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define pulse 17
#define PIN 2 // aqui definimos el pin que vamos a usar para cominicarnos con la matriz
// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
// NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
// Position of the FIRST LED in the matrix; pick two, e.g.
// NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
// NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
// rows or in vertical columns, respectively; pick one or the other.
// NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
// in the same order, or alternate lines reverse direction; pick one.
// See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic ‘v1’ (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// Example for NeoPixel Shield. In this application we’d like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino. When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order. The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
                                               NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                                                   NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                                               NEO_GRB + NEO_KHZ800); //Aqui definimos el tipo de matriz en este caso 8x8
const uint16_t colors[] = {
    matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)}; // colores que se van a mostrar en la matriz

#define NUMPIXELS 64 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int x = matrix.width();
int pass = 0;

bool drawArrow[64] = {0, 0, 1, 1, 1, 1, 0, 0,
                      0, 0, 1, 1, 1, 1, 0, 0,
                      0, 0, 1, 1, 1, 1, 0, 0,
                      0, 0, 1, 1, 1, 1, 0, 0,
                      1, 1, 1, 1, 1, 1, 1, 1,
                      0, 1, 1, 1, 1, 1, 1, 0,
                      0, 0, 1, 1, 1, 1, 0, 0,
                      0, 0, 0, 1, 1, 0, 0, 0};

bool drawX[64] = {1, 1, 0, 0, 0, 0, 1, 1,
                  1, 1, 1, 0, 0, 1, 1, 1,
                  0, 1, 1, 1, 1, 1, 1, 0,
                  0, 0, 1, 1, 1, 1, 0, 0,
                  0, 0, 1, 1, 1, 1, 0, 0,
                  0, 1, 1, 1, 1, 1, 1, 0,
                  1, 1, 1, 0, 0, 1, 1, 1,
                  1, 1, 0, 0, 0, 0, 1, 1};

void setup()
{
    pinMode(pulse, INPUT);
    /*
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(40); //brillo de los leds
    matrix.setTextColor(colors[0]);

    for (int i = 0; i < 134; i++)
    {
        matrix.fillScreen(0);
        matrix.setCursor(x, 0);
        matrix.print(F("BotLAB")); // modificamos aqui para escribir el texto que queramos
        if (--x < -36)
        {
            x = matrix.width();
            if (++pass >= 3)
                pass = 0;
            matrix.setTextColor(colors[pass]);
        }
        matrix.show();
        delay(100);
    }*/

    pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.clear(); // Set all pixel colors to 'off'
    delay(200);
}

bool lastPulseValue = 0;
bool pulseValue;

bool lastPulseValueNot = 1;
bool pulseValueNot;

void loop()
{
    pulseValue = digitalRead(pulse);
    if (lastPulseValue == 0 && pulseValue == 1)
    {   
        pixels.clear();
        for (int i = 0; i < NUMPIXELS; i++)
        {
            if (drawArrow[i] == 1)
            {
                pixels.setPixelColor(i, pixels.Color(0, 150, 0));
                pixels.show();
            }
        }
    }   
    lastPulseValue = pulseValue;

    pulseValueNot = digitalRead(pulse);
    if (lastPulseValueNot == 1 && pulseValueNot == 0)
    {
        pixels.clear();
        for (int i = 0; i < NUMPIXELS; i++)
        {
            if (drawX[i] == 1)
            {
                pixels.setPixelColor(i, pixels.Color(250, 0, 0));
                pixels.show();
            }
        }
    }
    lastPulseValueNot = pulseValueNot;
}