/*
 * Sensor: HC-SR04 Ultrasonic sensor
 * Dev kit: Arduino Uno
 * 
 * 
 * Grid:
 *          X
 * |-----------------|
 * |  1  |  2  |  3  | 
 * |-----------------|
 * |  4  |  5  |  6  | 
 * |-----------------|
 * |  7  |  8  |  9  | 
 * |-----------------|
 * 
 * X = obstacle
 * 
 * This version of the code will NOT use the pulsein function, which isn't present in the Nona BLE uC. 
 * As such, this is test code for what might be ported to the Nano
*/

// function prototype to define default timeout value
static unsigned int newPulseIn(const byte pin, const byte state, const unsigned long timeout = 1000000L);

// using a macro to avoid function call overhead
#define WAIT_FOR_PIN_STATE(state) \
  while (digitalRead(pin) != (state)) { \
    if (micros() - timestamp > timeout) { \
      return 0; \
    } \
  }

static unsigned int newPulseIn(const byte pin, const byte state, const unsigned long timeout) {
  unsigned long timestamp = micros();
  WAIT_FOR_PIN_STATE(!state);
  WAIT_FOR_PIN_STATE(state);
  timestamp = micros();
  WAIT_FOR_PIN_STATE(!state);
  return micros() - timestamp;
}

/*
 * Sensor: HC-SR04 Ultrasonic sensor
 * Dev kit: Arduino Uno
 * 
 * 
 * Grid:
 *          X
 * |-----------------|
 * |  1  |  2  |  3  | 
 * |-----------------|
 * |  4  |  5  |  6  | 
 * |-----------------|
 * |  7  |  8  |  9  | 
 * |-----------------|
 * 
 * X = obstacle
 */


#define echoPinCh1 9 //8 // Echo pin on sensor wired to Pin D8 on dev kit
#define trigPinCh1 10 // // Echo pin on sensor wired to Pin D9 on dev kit
#define echoPinCh2 2 // Echo pin on sensor wired to Pin D8 on dev kit
#define trigPinCh2 3 // Echo pin on sensor wired to Pin D9 on dev kit
// #define SAMPLE_LIMIT 20001
#define SAMPLE_LIMIT 100001

long channel1();
long channel2();


// defines variables
long durationCh1, durationCh2;  // Variable for the duration of sound wave travel
long distanceCh1, distanceCh2;                   // Variable for the distance measurement
long cm;
int j, i;
long k;



void setup() {
  delay(10000); // Delay to serial monitor to be set up
  pinMode(trigPinCh1, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(echoPinCh1, INPUT);   // Sets the echoPin as an INPUT
  pinMode(trigPinCh2, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(echoPinCh2, INPUT);   // Sets the echoPin as an INPUT
  Serial.begin(9600);           // Serial Communication is starting with 9600 of baudrate speed
  Serial.print("Ultrasonic Sensor Data Capture Start"); // Text to note start of data collection
  Serial.println(",");
  Serial.print("Obstacle: Umbreall holder, open door mid hallway");
  Serial.println(",");
  Serial.print("Grid place: 9 (Steady)");
  Serial.println(",");
  delay(30000); // Delay to serial monitor to be set up
}
void loop() 
{ 
  // long int t1 = millis();
  // Serial.print("~~~Start~~~");
  // Serial.println(",");
  Serial.print("Ch1: ");
  Serial.println(",");
  long int t1 = millis();
  channel1();
  long int t2 = millis();
  Serial.print("~~~Ch1 End~~~");
  Serial.println(",");
  Serial.print("Channel 1 time: "); 
  Serial.print(t2-t1); 
  Serial.println(" milliseconds");
  Serial.println(",");

  delay(1000); // 1 second delay

  // Serial.print("~~~Start~~~");
  // Serial.println(",");
  Serial.print("Ch2: ");
  Serial.println(",");
  long int t3 = millis();
  channel2();
  long int t4 = millis();
  Serial.print("~~~Ch2 End~~~");
  Serial.println(",");
  Serial.print("Channel 2 time: "); 
  Serial.print(t4-t3); 
  Serial.println(" milliseconds");
  Serial.println(",");

  delay(300000); // 1 second delay

//    Serial.print(distanceCh1);
//    Serial.print(",");
//    Serial.println(distanceCh2);
    
} // End of void loop

long channel1()
{
    for(k=0; k < SAMPLE_LIMIT; k++)
    {
      // Clears the trigPin condition
      digitalWrite(trigPinCh1, LOW);
      delayMicroseconds(2);
      
      // Sets the trigPin HIGH (ACTIVE) for 10 microseconds, as required by sensor
      digitalWrite(trigPinCh1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPinCh1, LOW);
      
      // Reads the echoPin, returns the sound wave travel time in microseconds
      // I need to convert the long data type to int - this is for memory usage
      durationCh1 =  pulseIn(echoPinCh1, HIGH);
      distanceCh1 = durationCh1 * 0.034 / 2;
      // Serial.print("Ch1: ");
      Serial.print(durationCh1);
      // Serial.print(distanceCh1);
      Serial.println(",");
      // return distanceCh1;
    }
}

long channel2()
{
      for(k=0; k < SAMPLE_LIMIT; k++)
      {
        // Clears the trigPin condition
        digitalWrite(trigPinCh2, LOW);
        delayMicroseconds(2);
        
        // Sets the trigPin HIGH (ACTIVE) for 10 microseconds, as required by sensor
        digitalWrite(trigPinCh2, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPinCh2, LOW);
        
        // Reads the echoPin, returns the sound wave travel time in microseconds
        // I need to convert the long data type to int - this is for memory usage
        durationCh2 =  pulseIn(echoPinCh2, HIGH);
        distanceCh2 = durationCh2 * 0.034 / 2;
        // Serial.print("Ch2: ");
        // Serial.println(durationCh2);
        // Serial.print(distanceCh2);
        Serial.print(durationCh2);
        Serial.println(",");
        // return distanceCh2;
      }


}
