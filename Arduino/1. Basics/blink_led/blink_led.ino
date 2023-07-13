/*
  blink_led

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control, attached to digital pin 13.
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output, or reference 13, which is the pin the LED is connected to.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {               // Repeat
  digitalWrite(13, HIGH);   // turn the LED on, bu setting voltage HIGH
  delay(500);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second

  // Serial.println("Hmm");
  // delay(1000);  
}
