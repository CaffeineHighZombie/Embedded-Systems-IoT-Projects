
// Define pins numbers
const int trigPin = 9;
const int echoPin = 10;

// Define variables
long duration;
int distance;

void setup() {
pinMode(trigPin, OUTPUT); // Set the trigPin as an Output
pinMode(echoPin, INPUT); // Set the echoPin as an Input
Serial.begin(9600); // Start the serial communication
}

void loop() {
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

// Print the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(100);
}
