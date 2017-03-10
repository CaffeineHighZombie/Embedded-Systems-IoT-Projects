// Define the LED digit patters, from 0 - 9
// Note that these patterns are for common cathode displays
// For common anode displays, change the 1's to 0's and 0's to 1's
// 1 = LED on, 0 = LED off, in this order:
//                                    Arduino pin: 2,3,4,5,6,7,8
byte seven_seg_digits[10][8] = { { 1,1,1,0,1,1,1,0 },  // = 0
                                 { 0,0,1,0,1,0,0,0 },  // = 1
                                 { 1,1,0,0,1,1,0,1 },  // = 2
                                 { 0,1,1,0,1,1,0,1 },  // = 3
                                 { 0,0,1,0,1,0,1,1 },  // = 4
                                 { 0,1,1,0,0,1,1,1 },  // = 5
                                 { 1,1,1,0,0,0,1,1 },  // = 6
                                 { 0,0,1,0,1,1,0,0 },  // = 7
                                 { 1,1,1,0,1,1,1,1 },  // = 8
                                 { 0,1,1,0,1,1,1,1 }   // = 9
                               };

// Initialize switch input
int incSwitch = 11;
int decSwitch = 12;

// Create boolean variables for software debouncing for both the switches
boolean incLastButton = LOW;
boolean incCurrentButton = LOW;
boolean decLastButton = LOW;
boolean decCurrentButton = LOW;

//count variable for display
byte count = 0;
                                                 
void setup() {                
  //7 Segment display setup
  pinMode(2, OUTPUT); // Segment A  
  pinMode(3, OUTPUT); // Segment B
  pinMode(4, OUTPUT); // Segment C
  pinMode(5, OUTPUT); // Segment D
  pinMode(6, OUTPUT); // Segment E
  pinMode(7, OUTPUT); // Segment F
  pinMode(8, OUTPUT); // Segment G
  pinMode(9, OUTPUT); // Segment dp
  
  // setting switch pins to input mode
  pinMode(incSwitch, INPUT);
  pinMode(decSwitch, INPUT);
  
}

// Software debounce for increment switch
boolean debounceInc(boolean last)
{
  boolean current = digitalRead(incSwitch);
  if (last != current)
  {
    delay(5);
    current = digitalRead(incSwitch);
  }
  return current;
}

// Software debounce for decrement switch
boolean debounceDec(boolean last)
{
  boolean current = digitalRead(decSwitch);
  if (last != current)
  {
    delay(5);
    current = digitalRead(decSwitch);
  }
  return current;
}

// Routine to write integer value on to 7 Segment LED
void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 8; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {
  // Check if the increment switch has been pressed
  incCurrentButton = debounceInc(incLastButton);
  if (incLastButton == LOW && incCurrentButton == HIGH)
  {
    count++; // Increase the count variable
  }
  incLastButton = incCurrentButton;

  // Check if the decrement switch has been pressed
  decCurrentButton = debounceDec(decLastButton);
  if (decLastButton == LOW && decCurrentButton == HIGH)
  {
    count--; // Decrement the count variable
  }
  decLastButton = decCurrentButton;

  // Write count value on the display
  if (count>=0 && count<10) { // Check bound conditions
    sevenSegWrite(count);  // Call the display write routine
  }   
  else {
    count = 0; // If the count crosses the (0,9) bounds, set it to zero - not a perfect solution - but works till another display segment with carry is introduced, if needed
  }
   
  delay(100); // A small 100ms delay
}
