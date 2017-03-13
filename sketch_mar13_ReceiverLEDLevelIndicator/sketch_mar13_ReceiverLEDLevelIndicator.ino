
// Define pins for 5 LEDs
const int lowLed = 2; // Low level indicator
const int oneLed = 3; // one-fourth level indicator
const int twoLed = 4; // two-fourth level indicator
const int threeLed = 5; // three-fourth level indicator
const int highLed = 6; // High level indicator

void setup() {
  // Setup the LED pins as output
  pinMode(lowLed, OUTPUT);
  pinMode(oneLed, OUTPUT);
  pinMode(twoLed, OUTPUT);
  pinMode(threeLed, OUTPUT);
  pinMode(highLed, OUTPUT);
  
}

void loop() {
  // Switch Low level indicator on, give one second delay and turn off
  digitalWrite(lowLed, HIGH);
  delay(1000);
  digitalWrite(lowLed, LOW);

  // Switch one-fourth level indicator on, give one second delay and turn off
  digitalWrite(oneLed, HIGH);
  delay(1000);
  digitalWrite(oneLed, LOW);
  
  // Switch two-fourth level indicator on, give one second delay and turn off
  digitalWrite(twoLed, HIGH);
  delay(1000);
  digitalWrite(twoLed, LOW);
  
  // Switch three-fourth level indicator on, give one second delay and turn off
  digitalWrite(threeLed, HIGH);
  delay(1000);
  digitalWrite(threeLed, LOW);
  
  // Switch High level indicator on, give one second delay and turn off
  digitalWrite(highLed, HIGH);
  delay(1000);
  digitalWrite(highLed, LOW);

}
