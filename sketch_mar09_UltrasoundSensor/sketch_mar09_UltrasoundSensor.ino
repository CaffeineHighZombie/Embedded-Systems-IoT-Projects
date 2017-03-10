
// Define pins numbers
const int trigPin = 9;
const int echoPin = 10;

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
  int arrSize = 100; // Define array size - for sensor data normalization
  int distanceArr[arrSize];
  int distance;

  // Collect the 100 data points from sensor and store in the array
  for(int i=0; i<arrSize; i++) {
    distanceArr[i] = getSensorData();
    delay(1); // A small 1ms delay between data collection - change it according to accruacy needed or variance in measured distance
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

  // Slicing just the mid data range (<1sigma) and finding the mean of that
  long sum = 0;
  for(int i=0; i<arrSize/2; i++) {
    sum += distanceArr[i];
  }
  distance = sum/(arrSize/2);
  
  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
