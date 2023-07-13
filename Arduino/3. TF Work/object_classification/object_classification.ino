/*
This code is used to run the generated model from my object detection project
*/

#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h> // Had to add "tflite_bridge"
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#include "model.h"

const float distanceThreshold = 2.5; // threshold of significant in G's

// **************************************** Globals ***************************************** /

// Declaring arrays to hold channel sample data
float channel1_array[10000];
float channel2_array[10000];
long tensor_array[10000][2];

// int channel1_array[10000];
// int channel2_array[10000];
// int tensor_array[10000][2];


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

#define echoPinCh1 8 //8 // Echo pin on sensor wired to Pin D8 on dev kit
#define trigPinCh1 9 // // Echo pin on sensor wired to Pin D9 on dev kit
#define echoPinCh2 2 // Echo pin on sensor wired to Pin D8 on dev kit
#define trigPinCh2 3 // Echo pin on sensor wired to Pin D9 on dev kit
// #define SAMPLE_LIMIT 20001
#define SAMPLES_LIMIT 10000

// long channel1();
// long channel2();


// defines variables
const int numSamples = 5000;
int samplesRead = numSamples;
// float durationCh1, durationCh2;  // Variable for the duration of sound wave travel
// long distanceCh1, distanceCh2;                   // Variable for the distance measurement
long cm;
int j, i;
long k;

// const int NUM_SAMPLES = 10000;
// int samplesRead = numSamples;

// Global variable used for TF Lite Micro
tflite::MicroErrorReporter tflErrorReporter;

// Import all the TF Lite Micro ops. I could pull in just the ones I need.
// For the minute I will take everything in. But this may change.
tflite::AllOpsResolver tflOpsResolver;

// Used to declare a variable that will be used to store a reference to a TF Lite model
const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

// Create a memory buffer in the micro:
// byte define the type of the array and `tensorArena` is the name of the array.
// [tensorArenaSize] is the size of the array. In this case, the array has a size of tensorArenaSize bytes.
// __attribute__((aligned(16))) is an attribute that tells the compiler to align the memory for 
// the array on a 16-byte boundary.
constexpr int tensorArenaSize = 35 * 1024;
byte tensorArena[tensorArenaSize] __attribute__((aligned(16)));

// Array to map grids
const char* GRIDS[] = {
  "zero",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine"          
};

#define NUM_GRIDS (sizeof(GRIDS) / sizeof(GRIDS[0]))

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPinCh1, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(echoPinCh1, INPUT);   // Sets the echoPin as an INPUT
  pinMode(trigPinCh2, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(echoPinCh2, INPUT);   // Sets the echoPin as an INPUT
  Serial.begin(9600);
  while(!Serial);
  Serial.print("Starting..."); // Text to note start of data collection

  // Get the TFL repsentation of the model byte array
  tflModel = tflite::GetModel(model);
    if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1);
  }
  
  // Generate an interpretor to run the model
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize);  

  // Assign memory for the model's input and output tensors
  tflInterpreter->AllocateTensors();

  // Pointers for the model input and output tensors
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);
}

void loop() 
{
  float durationCh1, durationCh2;  // Variable for the duration of sound wave travel
  // delay(1000);
  // Serial.print("In loop.."); // Text to note start of data collection
  // delay(1000); 
  // for(int i=1; i<SAMPLES_LIMIT; i++)
  // while(SAMPLES_READ < NUM_SAMPLES)

  while(samplesRead ==  numSamples) // SAMPLES_LIMIT = 10000
  {
    samplesRead = 0;
    break;
  }
  // for(i=0; i<5000; i++)  
  while(samplesRead < numSamples)
  {  
    // Serial.print("Here");

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

    // channel1_array[i] = durationCh1;
    // tflInputTensor->data.f16[channel1_array[i]]; // See line 178, this line came from there
    // tflInputTensor->data.f[i] = channel1_array[i];

    // Serial.print(channel1_array[i]); // Text to note start of data collection
    // Serial.println(",");

    // =======================================================
    // tensor_array[10000][1] = channel1_array;
    // tensor_array[10000][2] = channel2_array;
    // tflInputTensor->data.f[channel1_array];
    // tflInputTensor->data.f[channel1_array];
    // tflInputTensor->data.f[i] = channel1_array[i];
    // tflInputTensor->data.f[i*2+0] = durationCh1;
    // tflInputTensor->data.f[i*2+1] = durationCh1+2;
    tflInputTensor->data.f[samplesRead+0] = 2200;
    tflInputTensor->data.f[samplesRead+1] = 2010;

    samplesRead++;    
    // Serial.println(durationCh1);

    // delayMicroseconds(10);
    // i = i + 1;
    // Serial.println(i);
    // delayMicroseconds(2);
      

    // if(i == 4999)
    if(samplesRead == numSamples)
    { 
 
      TfLiteStatus invokeStatus = tflInterpreter->Invoke();
      Serial.println("Invoke");      
      if (invokeStatus != kTfLiteOk) 
      {
        Serial.println("Invoke failed!");
        while (1);
        return;
      }

      // Loop through the output tensor values from the model
      for (int i = 0; i < NUM_GRIDS; i++) 
      {
        Serial.print(GRIDS[i]);
        Serial.print(": ");
        Serial.println(tflOutputTensor->data.f[i], 6);
      }
      //======================================================= */ 
      Serial.println();
      delay(2000);
    }
  }
}
 
