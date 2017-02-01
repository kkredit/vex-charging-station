#define LED_PIN 2

void toggleLed();

void setup() {
  /* Set LED_PIN as output */
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, false);
}

void loop() {
  delay(500);
  toggleLed();
}

void toggleLed(){
  static bool ledStatus = false;
  ledStatus = !ledStatus;
  digitalWrite(LED_PIN, ledStatus);
}

