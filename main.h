


#define LED_COUNT 150          // число светодиодов в кольце/ленте
#define LED_DT 13             // пин, куда подключен DIN ленты

extern int max_bright;         // максимальная яркость (0 - 255)
extern int ledMode;

//extern byte ballColors[3][3];


extern int BOTTOM_INDEX;        // светодиод начала отсчёта
extern int TOP_INDEX;
extern int EVENODD;
extern struct CRGB leds[];
extern int ledsX[LED_COUNT][3];     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)


extern int thisdelay;          //-FX LOOPS DELAY VAR
extern int thisstep;           //-FX LOOPS DELAY VAR
extern int thishue;             //-FX LOOPS DELAY VAR
extern int thissat;           //-FX LOOPS DELAY VAR

extern int thisindex;
extern int thisRED;
extern int thisGRN;
extern int thisBLU;

extern int idex;                //-LED INDEX (0 to LED_COUNT-1
extern int ihue;                //-HUE (0-255)
extern int ibright;             //-BRIGHTNESS (0-255)
extern int isat;                //-SATURATION (0-255)
extern int bouncedirection;     //-SWITCH FOR COLOR BOUNCE (0-1)
extern float tcount;          //-INC VAR FOR SIN LOOPS
extern int lcount;              //-ANOTHER COUNTING VAR