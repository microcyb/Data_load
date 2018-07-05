#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
FASTLED_USING_NAMESPACE

//IMPORTANT: Update the pin and NUM_LEDS to match your LED strip!
#define DATA_PIN  D5
#define LED_TYPE  WS2812B
#define COLOR_ORDER  GRB
#define NUM_LEDS 150
#define VOLTS	5
#define MILLI_AMPS  2000 // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)

CRGB leds[NUM_LEDS];
int currentFrame = 0;
int TOTAL_FRAMES = 94;
int FRAMES_PER_SECOND = 30;

/* ********************
   I SHORTENED THE DATA
   Will be doing a #include <PROGMEM.h>
   ******************** */
#ifndef PIXEL_DATA_H
   #define PIXEL_DATA_H
   const uint8_t PixelData[1200][4] PROGMEM = {
      {255,0,0,0}
      ,{255,0,0,0}
      ,{255,0,0,0}
      ,{255,255,255,0}
      ,{255,255,255,0}
      ,{255,255,255,0}
      ,{255,255,255,0}
      ,{255,255,255,0}
      ,{255,0,0,0}
      ,{0,0,0,0}
      ,{0,0,0,0}
}};
#endif
uint8_t brightnessIndex = 100;

void setup() {
	Serial.begin(115200);
	FastLED.setBrightness(brightnessIndex);
	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MILLI_AMPS);
}

void loop() {
	for (int i=0; i<NUM_LEDS; i++) {
	int pixelIndex = i % NUM_LEDS;
	int index = currentFrame*NUM_LEDS*3 + pixelIndex*3;
	leds[i] = CRGB(pgm_read_byte_near(PixelData+index), pgm_read_byte_near(PixelData+index+1),pgm_read_byte_near(PixelData+index+2));
	}
	FastLED.show();
	currentFrame ++;
	if (currentFrame >= TOTAL_FRAMES) currentFrame = 0;
	delay(1000/FRAMES_PER_SECOND);
}
