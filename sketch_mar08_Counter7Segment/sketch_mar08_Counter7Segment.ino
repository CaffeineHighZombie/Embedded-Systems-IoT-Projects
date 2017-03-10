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

// Create 
boolean incLastButton = LOW;
boolean incCurrentButton = LOW;
boolean decLastButton = LOW;
boolean decCurrentButton = LOW;

//count variable for display
byte count = 0;
                                                 
void setup() {                
  //7 Segment display setup
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  // setting switch pins to input mode
  pinMode(incSwitch, INPUT);
  pinMode(decSwitch, OUTPUT);
  
}

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
  
void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 8; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {
  incCurrentButton = debounceInc(incLastButton);
  if (incLastButton == LOW && incCurrentButton == HIGH)
  {
    count++;
  }
  incLastButton = incCurrentButton;
  
  decCurrentButton = debounceDec(decLastButton);
  if (decLastButton == LOW && decCurrentButton == HIGH)
  {
    count--;
  }
  decLastButton = decCurrentButton;
  if (count>=0 && count<10) {
    sevenSegWrite(count);  
  }   
  else {
    count = 0;
  }
   
  delay(100);
}
