
bool xPWM;
int cuenta_PWM;
int duty_PWM_interno;

typedef enum{
    inicioPWM,
    pasa_uno,
    sigue_uno,
    pasa_cero,
	sigue_cero,
	terminaPWM
} EstPWM_t;

static EstPWM_t estPWM;

void PWMInit(void);
void DUTY(int duty_PWM);
int cambioDUTY(int DP);
int tomadato(int ciclo1);


