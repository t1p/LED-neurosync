#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>

#include "FastLED.h"
#include "main.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "696a423a33414dffacce94c930ff99b3";
//char auth[] = "Z2dPFXTcXVH6I_ARt-lUjH1pRbxcjN1x";
char auth[] = "RUUOCQGuO43JtkpXqbrfHhhWHYeAhNeJ";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Technoashram";
char pass[] = "analemma3000";

#define PIN 21
#define LED_PIN 2
#define SR_501_PIN  4

uint8_t sensor_on = 1;

WiFiUDP Udp;
const unsigned int localPort = 8888;        // local port to listen for UDP packets (here's where we send the packets)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

BLYNK_WRITE(V1)
{
  int shift = param.asInt();
  ledMode = shift;
  Serial.printf("ledmode = %u \n", ledMode);
  // for (int i = 0; i < strip.numPixels(); i++)
  // {
  //   strip.setPixelColor(i, Wheel(shift & 255));
  //   // OR: strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + shift) & 255));
  // }
  // strip.show();
}

BLYNK_WRITE(V2)
{
  int shift = param.asInt();
  sensor_on = shift;
  Serial.printf("sensor_on = %u\n", sensor_on);
}

BLYNK_WRITE(V3)
{
  int shift = param.asInt();
  int brght = shift;
  Serial.printf("brght = %u \n", brght);
  FastLED.setBrightness( brght );
}

#define WSLED_PIN     21
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B

#define BRIGHTNESS  2
#define FRAMES_PER_SECOND 60

bool gReverseDirection = false;

CRGB leds[LED_COUNT];
void setup()
{
  // Debug console
  Serial.begin(9600);

  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  Blynk.begin(auth, ssid, pass, IPAddress(10,2,1,70), 8080);

  FastLED.addLeds<CHIPSET, WSLED_PIN, COLOR_ORDER>(leds, LED_COUNT).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  //strip.begin();
  //strip.show();

  pinMode(LED_PIN, OUTPUT);
  pinMode(SR_501_PIN, INPUT_PULLUP);

  xTaskCreate(
                    taskOne,          /* Task function. */
                    "TaskOne",        /* String with name of task. */
                    10000,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */

 Udp.begin(localPort);

}

uint16_t counter;
uint8_t toggle_c = 0;

void loop()
{
  if (digitalRead(SR_501_PIN)){
    digitalWrite(LED_PIN, HIGH);
    if(!toggle_c){
      toggle_c = 1;
      Serial.println("SR_501_PIN = 1");
    }
  }else{
    digitalWrite(LED_PIN, LOW);
    if(toggle_c){
      toggle_c = 0;
      Serial.println("SR_501_PIN = 0");
    }
  }
  //delay(1);

    //Fire2012(); // run simulation frame
  if(!sensor_on){
  switch (ledMode) {
    case 999: break;                           // пазуа
    case  2: rainbow_fade(); break;            // плавная смена цветов всей ленты
    case  3: rainbow_loop(); break;            // крутящаяся радуга
    case  4: random_burst(); break;            // случайная смена цветов
    case  5: color_bounce(); break;            // бегающий светодиод
    case  6: color_bounceFADE(); break;        // бегающий паровозик светодиодов
    case  7: ems_lightsONE(); break;           // вращаются красный и синий
    case  8: ems_lightsALL(); break;           // вращается половина красных и половина синих
    case  9: flicker(); break;                 // случайный стробоскоп
    case 10: pulse_one_color_all(); break;     // пульсация одним цветом
    case 11: pulse_one_color_all_rev(); break; // пульсация со сменой цветов
    case 12: fade_vertical(); break;           // плавная смена яркости по вертикали (для кольца)
    case 13: rule30(); break;                  // безумие красных светодиодов
    case 14: random_march(); break;            // безумие случайных цветов
    case 15: rwb_march(); break;               // белый синий красный бегут по кругу (ПАТРИОТИЗМ!)
    case 16: radiation(); break;               // пульсирует значок радиации
    case 17: color_loop_vardelay(); break;     // красный светодиод бегает по кругу
    case 18: white_temps(); break;             // бело синий градиент (?)
    case 19: sin_bright_wave(); break;         // тоже хрень какая то
    case 20: pop_horizontal(); break;          // красные вспышки спускаются вниз
    case 21: quad_bright_curve(); break;       // полумесяц
    case 22: flame(); break;                   // эффект пламени
    case 23: rainbow_vertical(); break;        // радуга в вертикаьной плоскости (кольцо)
    case 24: pacman(); break;                  // пакман
    case 25: random_color_pop(); break;        // безумие случайных вспышек
    case 26: ems_lightsSTROBE(); break;        // полицейская мигалка
    case 27: rgb_propeller(); break;           // RGB пропеллер
    case 28: kitt(); break;                    // случайные вспышки красного в вертикаьной плоскости
    case 29: matrix(); break;                  // зелёненькие бегают по кругу случайно
    case 30: new_rainbow_loop(); break;        // крутая плавная вращающаяся радуга
    case 31: strip_march_ccw(); break;         // чёт сломалось
    case 32: strip_march_cw(); break;          // чёт сломалось
    case 33: colorWipe(0x00, 0xff, 0x00, thisdelay);
      colorWipe(0x00, 0x00, 0x00, thisdelay); break;                                // плавное заполнение цветом
    case 34: CylonBounce(0xff, 0, 0, 4, 10, thisdelay); break;                      // бегающие светодиоды
    case 35: Fire(55, 120, thisdelay); break;                                       // линейный огонь
    case 36: NewKITT(0xff, 0, 0, 8, 10, thisdelay); break;                          // беготня секторов круга (не работает)
    case 37: rainbowCycle(thisdelay); break;                                        // очень плавная вращающаяся радуга
    case 38: TwinkleRandom(20, thisdelay, 1); break;                                // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод)
    case 39: RunningLights(0xff, 0xff, 0x00, thisdelay); break;                     // бегущие огни
    case 40: Sparkle(0xff, 0xff, 0xff, thisdelay); break;                           // случайные вспышки белого цвета
    case 41: SnowSparkle(0x10, 0x10, 0x10, thisdelay, random(100, 1000)); break;    // случайные вспышки белого цвета на белом фоне
    case 42: theaterChase(0xff, 0, 0, thisdelay); break;                            // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ НЕЧЁТНОЕ)
    case 43: theaterChaseRainbow(thisdelay); break;                                 // бегущие каждые 3 радуга (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3)
    case 44: Strobe(0xff, 0xff, 0xff, 10, thisdelay, 1000); break;                  // стробоскоп

    case 45: BouncingBalls(0xff, 0, 0, 3); break;                                   // прыгающие мячики
    //case 46: BouncingColoredBalls(3, ballColors); break;                            // прыгающие мячики цветные
    case 46: Fire2012(); break;  
    case 888: demo_modeA(); break;             // длинное демо
    case 889: demo_modeB(); break;             // короткое демо
  }
  }else{
    if(digitalRead(SR_501_PIN)){
      colorWipe(0xff, 0xff, 0xff, thisdelay);
      colorWipe(0x00, 0x00, 0x00, thisdelay);
    }
  }

}


void taskOne( void * parameter )
{
 while (1)
 {
     Blynk.run();

   delay(1);
 }

}


//void taskTwo( void * parameter)
//{

//  OSCBundle bundle;
//while(1){
//  int size = Udp.parsePacket();
//  if (size > 0) {
 //   while (size--) {
 //     bundle.fill(Udp.read());
 //   }
 //   if (!bundle.hasError()) {
//      bundle.dispatch("/led_state_ch", led_state_ch);
 //   } else {
 //     error = bundle.getError();
 //     Serial.print("error: ");
 //     Serial.println(error);
 //   }
//  }

 //   delay(1);
//  }
//}

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120

void Fire2012()
{
// Array of temperature readings at each simulation cell
  static byte heat[LED_COUNT];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < LED_COUNT; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / LED_COUNT) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= LED_COUNT - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < LED_COUNT; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (LED_COUNT-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}
