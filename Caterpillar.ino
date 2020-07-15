#include <FastLED.h>

#define LED_PIN     3
#define NUM_LEDS    48
#define BRIGHTNESS  96
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
}


void loop()
{
  ChangePalettePeriodically();

  static uint8_t startIndex = 0;
  startIndex = startIndex - 1;       /* motion speed and +/- for reverse/forward */

  FillLEDsFromPaletteColors(startIndex);

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);  //1000
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;     //255

  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

void ChangePalettePeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if ( lastSecond != secondHand) {
    lastSecond = secondHand;
    if ( secondHand ==  0)  {
      SetupOnOffPalette();
      currentBlending = NOBLEND;
    }
    if ( secondHand == 30)  {
      SetupBlackAndWhiteStripedPalette();
      currentBlending = NOBLEND;
    }
  }
}

void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);

  currentPalette[0] = CRGB::Green;
  currentPalette[4] = CRGB::Green;
  currentPalette[8] = CRGB::Green;
  currentPalette[12] = CRGB::Green;
}

void SetupOnOffPalette()
{
  CRGB on   = CRGB::Green;
  CRGB off  = CRGB::Black;

  currentPalette = CRGBPalette16(
   on, off, off, off, on, off, off, off, on, off, off, off, on, off, off, off );
}

void SetupEveryNthPalette(byte nth)
{

  // 'black out' all 16 palette entries...
  fill_solid(currentPalette, 16, CRGB::Black);

  currentPalette[0] = CRGB::Green;
  currentPalette[nth] = CRGB::Green;
  currentPalette[nth * 2] = CRGB::Green;
  currentPalette[nth * 3] = CRGB::Green;

}
