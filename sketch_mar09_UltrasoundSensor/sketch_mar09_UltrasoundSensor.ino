
// Define pins numbers
const int trigPin = 9;
const int echoPin = 10;

// Define water level points - it would inverse of tank height due to use of ultrasound sensor
// Edit them according to use case and scenario - currently in cm
const float highPoint = 3; // Highest tank full point
const float lowPoint = 20; // Tank empty point
// const float buffPoint = 2; // Give some buffer for motor switch on/off - taking into account possible sensor noise and signal delays

void setup() {
  pinMode(trigPin, OUTPUT); // Set the trigPin as an Output
  pinMode(echoPin, INPUT); // Set the echoPin as an Input
  Serial.begin(9600); // Start the serial communication
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
  int distance;
  int range;
  
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
 
  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distanceArr[arrSize/2]);

  // Get the median of the sorted sensor data array and constrain it low and high water levels to clip out any noise
  distance = constrain(distanceArr[arrSize/2], highPoint, lowPoint);
  
  // Calculate the range as level gradations with median of sensor data array
  range = (distance - highPoint) * 100 / lowPoint;

  // Print range on the Serial Monitor
  Serial.println(range);
}
