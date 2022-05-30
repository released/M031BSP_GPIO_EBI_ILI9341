// Animates 256 white pixels to simulate flying through a star field

// Demonstrates use of the fastPixel() function in the library
// which is about 15% faster than drawPixel()

// #include <SPI.h>
#include <TFT_ILI9341.h>

// Use hardware SPI
// TFT_ILI9341 tft = TFT_ILI9341();

// With 256 stars the update frame rate is about 45Hz
#define NSTARS 256
static uint8_t sx[NSTARS] = {0};
static uint8_t sy[NSTARS] = {0};
static uint8_t sz[NSTARS] = {0};

static uint8_t za, zb, zc, zx;

// Fast 0-255 random number generator from http://eternityforest.com/Projects/rng.php:
static uint8_t rng(void)//void uint8_t __attribute__((always_inline)) rng(void)
{
  zx++;
  za = (za^zc^zx);
  zb = (zb+za);
  zc = (zc+(zb>>1)^za);
  return zc;
}

void setup_TFT_Starfield(void) {
  za = random(0,256);
  zb = random(0,256);
  zc = random(0,256);
  zx = random(0,256);

  // Serial.begin(115200);
  // init();
  setRotation(1);
  fillScreen(TFT_BLACK);

  // fastSetup() must be used immediately before fastPixel() to prepare screen
  // It must be called after any other graphics drawing function call if fastPixel()
  // is to be called again
  fastSetup(); // Prepare plot window range for fast pixel plotting
}

void loop_TFT_Starfield(void)
{
  unsigned long t0 = micros();
  uint8_t spawnDepthVariation = 255;
  int i = 0;
  int old_screen_x = 0;
  int old_screen_y = 0;
  int screen_x = 0;
  int screen_y = 0;
  uint8_t r, g, b;
  unsigned long t1 = 0;

  for(i = 0; i < NSTARS; ++i)
  {
    if (sz[i] <= 1)
    {
      sx[i] = 160 - 120 + rng();
      sy[i] = rng();
      sz[i] = spawnDepthVariation--;
    }
    else
    {
      old_screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
      old_screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;

      // This is a faster pixel drawing function for occassions where many single pixels must be drawn
      fastPixel(old_screen_x, old_screen_y,TFT_BLACK);

      sz[i] -= 2;
      if (sz[i] > 1)
      {
        screen_x = ((int)sx[i] - 160) * 256 / sz[i] + 160;
        screen_y = ((int)sy[i] - 120) * 256 / sz[i] + 120;
  
        if (screen_x >= 0 && screen_y >= 0 && screen_x < 320 && screen_y < 240)
        {
          // uint8_t r, g, b;
          r = g = b = 255 - sz[i];
          fastPixel(screen_x, screen_y, color565(r,g,b));
        }
        else
          sz[i] = 0; // Out of screen, die.
      }
    }
  }
  t1 = micros();
  //static char timeMicros[8] = {};

  // Serial.println(t1 - t0);
  printf("runTime : %dms\r\n" , t1 - t0);

}


