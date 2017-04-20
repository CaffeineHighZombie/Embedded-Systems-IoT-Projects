
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

// Define Relay Pin for Motor control
const int relayPin = 8;

// Flow State flags for Motor On/Off check subroutines
const int arrSize = 5;
int previousState[arrSize] = {-1, -1, -1, -1, -1};
boolean motorState = false;

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

// Subroutine to check previous motor state and if the previous stream of meesage indicates full level state - and switch off motor appropriately
void motorOffCheck() {
  int arrSum = 0;
  for(int i=0; i<arrSize; i++)
    arrSum += previousState[i];
  
  if ((arrSum >= 23 && arrSum <= 25) && motorState == true) {
    digitalWrite(relayPin, LOW);
    motorState = false;
  }
}

// Subroutine to check previous motor state and if the strem of meesage indicates low level state - and switch on motor appropriately
void motorOnCheck() {
  int arrSum = 0;
  for(int i=0; i<arrSize; i++)
    arrSum += previousState[i];
  
  if ((arrSum >= 0 && arrSum <= 2) && motorState == false) {
    digitalWrite(relayPin, HIGH);
    motorState = true;
  }
}

// Subroutine implementing FIFO in the form of list - shift data points to left, drop the first element and add argument as last element in the list
void previousStateAdd(int num) {
  for(int i=0; i<arrSize-1; i++) {
    previousState[i] = previousState[i+1];
  }
  previousState[arrSize]= num;
}

// Main loop
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
        previousStateAdd(0);
        motorOnCheck();
        break;
      case '1':
        turnOffAll();
        turnOnLed(oneLed);
        previousStateAdd(1);
        break;
      case '2':
        turnOffAll();
        turnOnLed(twoLed);
        previousStateAdd(2);
        break;
      case '3':
        turnOffAll();
        turnOnLed(threeLed);
        previousStateAdd(3);
        break;
      case '4':
        turnOffAll();
        turnOnLed(fourLed);
        previousStateAdd(4);
        break;
      case '5':
        turnOffAll();
        turnOnLed(highLed);
        previousStateAdd(5);
        motorOffCheck();
        break;

    }
  }
  
  delay(10); // Just an arbitrary 10ms delay
 
}
