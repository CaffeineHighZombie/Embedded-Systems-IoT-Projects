
// Define pins for 5 LEDs
const int lowLed = 2; // Low level indicator
const int oneLed = 3; // Below one-fourth level indicator
const int twoLed = 4; // Below two-fourth level indicator
const int threeLed = 5; // Below three-fourth level indicator
const int fourLed = 6; // Below full level indicator
const int highLed = 7; // Full level indicator

void setup() {
  // Setup the LED pins as output
  pinMode(lowLed, OUTPUT);
  pinMode(oneLed, OUTPUT);
  pinMode(twoLed, OUTPUT);
  pinMode(threeLed, OUTPUT);
  pinMode(fourLed, OUTPUT);
  pinMode(highLed, OUTPUT);
  
  // Start Serial
  Serial.begin(9600);
  
}

// Subroutine to turn off all LEDs
void turnOffAll() {
  digitalWrite(lowLed, LOW);
  digitalWrite(oneLed, LOW);
  digitalWrite(twoLed, LOW);
  digitalWrite(threeLed, LOW);
  digitalWrite(fourLed, LOW);
  digitalWrite(highLed, LOW);
  
}

// Subroutine to turn on one particular LED given the argument
void turnOnLed(int ledPin) {
  digitalWrite(ledPin, HIGH);
}

void loop() {

  // Wait till there's data on the Serial
  while(Serial.available() == 0);
  char sData = Serial.read(); // Data sent over the serial line being char byte data
  
  // Map LED switch-on to the input serial data
  switch (sData) {
    case '0':
      turnOffAll();
      turnOnLed(lowLed);
      break;
    case '1':
      turnOffAll();
      turnOnLed(oneLed);
      break;
    case '2':
      turnOffAll();
      turnOnLed(twoLed);
      break;
    case '3':
      turnOffAll();
      turnOnLed(threeLed);
      break;
    case '4':
      turnOffAll();
      turnOnLed(fourLed);
      break;
    case '5':
      turnOffAll();
      turnOnLed(highLed);
      break;
  
  }

  delay(100); // Just an arbitrary 100ms delay
  // Flush out serial buffer
  Serial.flush();  

}
