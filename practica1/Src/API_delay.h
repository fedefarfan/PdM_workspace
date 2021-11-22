


#define MAX_DELAY 10000

typedef uint32_t tick_t; // Que biblioteca se debe incluir para que esto compile
typedef bool bool_t;	  // Que biblioteca se debe incluir para que esto compile
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;


static void SystemClock_Config(void);
static void Error_Handler(void);
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

