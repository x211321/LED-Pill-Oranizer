#define BUTTON_PIN D2
#define BUTTON_DEBOUNCE_INTERVAL 500

unsigned long lastButtonPressMillis;

void init_button()
{
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, RISING);
}

ICACHE_RAM_ATTR void handleButtonInterrupt()
{
  noInterrupts();

  if (millis() - lastButtonPressMillis > BUTTON_DEBOUNCE_INTERVAL) {
    lastButtonPressMillis = millis();
    schedule_addConfirmRequest();
  }

  interrupts();
}
