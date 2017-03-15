
#include <RH_ASK.h> // RadioHead ASK library
#include <SPI.h> // Not actually used but needed to compile RH_ASK based code

// Create RH_ASK driver
RH_ASK driver;

// Define pins for 6 LEDs
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

  Serial.begin(9600); // Debugging only
  
  // See if RH_ASK driver initialized
  if (!driver.init())
         Serial.println("init failed");
  
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

  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
   char data = *buf;
   // Map LED switch-on to the input serial data
    switch (data) {
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
  }
  
  delay(100); // Just an arbitrary 100ms delay
 
}
