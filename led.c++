#define LED 19

portMUX_TYPE mux0 = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE mux1 = portMUX_INITIALIZER_UNLOCKED;

volatile bool state0 = 0;
volatile bool state1 = 0;
volatile bool counter = 0;
hw_timer_t * timer0;
hw_timer_t * timer1;

void IRAM_ATTR onTimer0() {
  portENTER_CRITICAL(&mux0);
  state0 = !state0;
  portEXIT_CRITICAL(&mux0);
}

void IRAM_ATTR onTimer1() {
  portENTER_CRITICAL(&mux1);
  state1 = !state1;
  counter++;
  portEXIT_CRITICAL(&mux1);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);
  timer0 = timerBegin(0, 80, true);
  timer1 = timerBegin(1, 80, true);
  timerAttachInterrupt(timer0, onTimer0, true);
  timerAttachInterrupt(timer1, onTimer1, true);
  timerAlarmWrite(timer0, 1000000, true);
  timerAlarmWrite(timer1, 500000, true);
  timerAlarmEnable(timer0);
  timerAlarmEnable(timer1);
}

void loop() {
  digitalWrite(LED_BUILTIN, state0);
  digitalWrite(LED, state1);
  if (counter == 10) {
    if (timer1 != NULL) {
      timerAlarmDisable(timer1);
      timerDetachInterrupt(timer1);
      timerEnd(timer1);
      timer1 = NULL;
    }
  }
}
