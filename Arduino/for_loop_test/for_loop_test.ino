
/**********************************************************************************************/
// *** Taken from: https://forum.arduino.cc/t/nano-ble-sense-and-ultrasonic-sensor/626958/3 ***/
/**********************************************************************************************/
// function prototype to define default timeout value
static unsigned int pulseInFun(const byte pin, const byte state, const unsigned long timeout = 1000000L);

// using a macro to avoid function call overhead
#define WAIT_FOR_PIN_STATE(state) \
  while (digitalRead(pin) != (state)) { \
    if (micros() - timestamp > timeout) { \
      return 0; \
    } \
  }

static unsigned int pulseInFun(const byte pin, const byte state, const unsigned long timeout) {
  unsigned long timestamp = micros();
  WAIT_FOR_PIN_STATE(!state);
  WAIT_FOR_PIN_STATE(state);
  timestamp = micros();
  WAIT_FOR_PIN_STATE(!state);
  return micros() - timestamp;
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

float channel1_array[3000];
#define echoPinCh1 8 //8 // Echo pin on sensor wired to Pin D8 on dev kit
#define trigPinCh1 9 // // Echo pin on sensor wired to Pin D9 on dev kit
#define SAMPLES_LIMIT 3000

float durationCh1, durationCh2;  // Variable for the duration of sound wave travel

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPinCh1, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(echoPinCh1, INPUT);   // Sets the echoPin as an INPUT
  Serial.begin(9600);
  while(!Serial);
  Serial.print("Starting..."); // Text to note start of data collection

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=2000; i>0; i--)  
  {  
      // Here I need to get my data samples, invoke the model and generate an output
      // Clears the trigPin condition
      digitalWrite(trigPinCh1, LOW);
      delayMicroseconds(2);

      // Sets the trigPin HIGH (ACTIVE) for 10 microseconds, as required by sensor
      digitalWrite(trigPinCh1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPinCh1, LOW);

      // Reads the echoPin, returns the sound wave travel time in microseconds
      // I need to convert the long data type to int - this is for memory usage
      durationCh1 =  pulseInFun(echoPinCh1, HIGH);
      // distanceCh2 = durationCh2 * 0.034 / 2;
      Serial.println(i);
      // channel1_array[i] = durationCh1;
      // i++;
  }    
  delay(10000);
}
