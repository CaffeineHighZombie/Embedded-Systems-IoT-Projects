
#include <RH_ASK.h> // RadioHead ASK library
#include <SPI.h> // Not actually used but needed to compile RH_ASK based code

// Define pins numbers
const int trigPin = 5;
const int echoPin = 6;

// Create RH_ASK driver
RH_ASK driver;

// Define water level points - it would inverse of tank height due to use of ultrasound sensor
// Edit them according to use case and scenario - currently in cm
const float highPoint = 10; // Highest tank full point`
const float lowPoint = 50; // Tank empty point
// const float buffPoint = 5; // Give some buffer for motor switch on/off - taking into account possible sensor noise and signal delays

void setup() {
  pinMode(trigPin, OUTPUT); // Set the trigPin as an Output
  pinMode(echoPin, INPUT); // Set the echoPin as an Input

  // See if RH_ASK driver initialized
  if (!driver.init())
         Serial.println("init failed");

}

// Routine to distance data from Ultrasound sensor
int getSensorData() {
  // Define variables
  long duration;
  int distance;
  
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, return the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (in centimeters)
  distance= duration*0.034/2;

  return distance;
}

void loop() {
  // Define an array for output collection over a time period
  int timeDelay = 100; // Delay in milliseconds between data collection - change it according to rate of variance in measured distance
  int arrSize = 10; // Define array size
  int distanceArr[arrSize];
  int range;
  char msg;
  
  // Collect the 100 data points from sensor and store in the array
  for(int i=0; i<arrSize; i++) {
    distanceArr[i] = getSensorData();
    delay(timeDelay); // A small 1ms delay between data collection - change it according to accuacy needed or variance in measured distance
  }
  
  // Sort the Array
  for(int i=0; i<arrSize; i++) {
    for(int j=i+1; j<arrSize; j++) {
      if(distanceArr[i] > distanceArr[j] ) {
           int temp = distanceArr[i];
           distanceArr[i] = distanceArr[j];
           distanceArr[j] = temp;
      }
    }
  }
 
  // Calculate the range as level gradations with median of sorted sensor data array
  range = (distanceArr[arrSize/2] - highPoint) * 100 / (lowPoint - highPoint);
  // Constrain the range between 0 and 100 to clip noise or extraneous data
  range = constrain(range, 0, 100);
  
  // Create level gradations based on range and transmit it over RF433
  if (range >= 95) 
    msg = '0';
  else if (range >= 75)
    msg = '1';
  else if (range >= 50)
    msg =  '2';
  else if (range >= 25)
    msg =  '3';
  else if (range >= 5)
    msg = '4';
  else
    msg = '5';
  
  // Transmitting the gradation data over RF433
  const char *msgPointer = &msg;
  driver.send((uint8_t *)msgPointer, strlen(msgPointer));
  driver.waitPacketSent();

}
