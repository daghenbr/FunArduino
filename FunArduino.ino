#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_RING_PIN    6
#define LED_STRIP_PIN    5

// How many NeoPixels are attached to the Arduino?
#define LED_RING_COUNT 42
#define LED_STRIP_COUNT 42

// Declare our NeoPixel strip object:
Adafruit_NeoPixel ledRing(LED_RING_COUNT, LED_RING_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledStrip(LED_STRIP_COUNT, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

uint32_t colorGreen =   ledStrip.Color(0, 10, 0);
uint32_t colorRed =     ledStrip.Color(10, 0, 0);
uint32_t colorMagenta = ledStrip.Color(10, 0, 10);
uint32_t colorWhite =   ledStrip.Color(10, 10, 10);
uint32_t colorOk =      ledStrip.Color(0, 25, 0);
uint32_t colorFail =    ledStrip.Color(25, 0, 0);

int firstLed;

void setup()
{
  // put your setup code here, to run once:
  ledStrip.begin();
  ledStrip.show(); // Initialize all pixels to 'off'
  //ledStrip.setPixelColor(11, 255, 0, 255);
  //ledStrip.setPixelColor(12,   0, 0, 255);
  //ledStrip.setPixelColor(13, 255, 0,   0);
  //ledStrip.setPixelColor(14,   0,255,   0);
  //ledStrip.setBrightness(10); //Max 255
  ledStrip.show();
  
  ledRing.begin();
  ledRing.clear();
  ledRing.show();

  Serial1.begin(115200L);  //This could be used for an optical sensor
}

int mode;
long timeMs;


void loop()
{
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0)
  {
    byte a = Serial.read();
    mode = a & 0x03;
    timeMs = 0;
  }
  if(mode == 0)
  {
    if((timeMs % 80) == 0)
    {
      ledRing.setPixelColor((firstLed+0)%LED_RING_COUNT,   0,  0,   0);
      ledRing.setPixelColor((firstLed+1)%LED_RING_COUNT,  10, 0, 10);
      ledRing.setPixelColor((firstLed+2)%LED_RING_COUNT,   0,  0,  10);
      ledRing.setPixelColor((firstLed+3)%LED_RING_COUNT,  10,  0,   0);
      ledRing.setPixelColor((firstLed+4)%LED_RING_COUNT,   0, 10,   0);
      ledRing.show();
      firstLed++;
      if(firstLed >= LED_RING_COUNT)
        firstLed = 0;
    }
    if(timeMs == 0)
    {
      //ledStrip.fill(colorWhite);
      //ledStrip.show();
      
    }
  } else if(mode == 1)
  {
    if(timeMs == 0 || timeMs == 400 || timeMs == 800 || timeMs == 1200 || timeMs == 1600)
    {
      ledRing.fill(colorOk);
      ledStrip.fill(colorOk);
      ledRing.show();
      ledStrip.show();
    } else if(timeMs == 200 || timeMs == 600 || timeMs == 1000 || timeMs == 1400)
    {
      ledRing.clear();
      ledStrip.clear();
      ledRing.show();
      ledStrip.show();
    } else if(timeMs == 3000)
    {
      ledRing.fill(colorWhite);
      ledStrip.fill(colorWhite);
      ledRing.show();
      ledStrip.show();
    }
  } else if(mode == 2)
  {
    if(timeMs == 0 || timeMs == 400 || timeMs == 800 || timeMs == 1200 || timeMs == 1600)
    {
      ledRing.fill(colorFail);
      ledStrip.fill(colorFail);
      ledRing.show();
      ledStrip.show();
    } else if(timeMs == 200 || timeMs == 600 || timeMs == 1000 || timeMs == 1400)
    {
      ledRing.clear();
      ledStrip.clear();
      ledRing.show();
      ledStrip.show();
    } else if(timeMs == 3000)
    {
      ledRing.fill(colorWhite);
      ledStrip.fill(colorWhite);
      ledRing.show();
      ledStrip.show();
    }
  } else if(mode == 3)
  {
    for(int i=0; i<LED_RING_COUNT; i++)
      ledRing.setPixelColor(i,    0,  0,   0);
    ledRing.show();
    ledStrip.show();
  }
  
  delay(1);
  timeMs++;
}

