/*
This code is used to run the generated model from my object detection project

Python code:  X_train.shape, X_test.shape, y_train.shape, y_test.shape
Generates:    ((134000, 2), (66000, 2), (134000,), (66000,))



https://www.programiz.com/c-programming/online-compiler/
#include <stdio.h>

int main() {
    int array[10][2];   
    // Fill the array with values
    
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 2; j++) {
        printf("%d ", array[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    return 0;
}


*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h> // Had to add "tflite_bridge"
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>
#include <tensorflow/lite/c/common.h>

#include "model.h"
#include "channel1.h" // input_array_1
#include "channel2.h" // input_array_2

const int kInputHeight = 5000;
const int kInputWidth = 2;
const int kInputDepth = 1;  // Assume input is a single channel

float arr[5000][2]; // 2D array of size 5x2
float float_array[5000][2];
// float floatData[5000 * 2];
float data_array[5000][2];


// defines variables
const int numSamples = 5000;
int samplesRead = numSamples;
// float durationCh1, durationCh2;  // Variable for the duration of sound wave travel
// long distanceCh1, distanceCh2;                   // Variable for the distance measurement
long cm;
int j, i;
long k;
long randomNumber1, randomNumber2;

// Create a 2D array to hold your input data
float input_data[5000][2];  // Assumes 1000 rows and 2 columns
float arrayOne[5000]; // Declare the array with 5000 elements
float arrayTwo[5000]; // Declare the array with 5000 elements
float valueOne = 100; // Replace 1.23 with the desired float value 
float valueTwo = 10296; // Replace 1.23 with the desired float value 

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

// TfLiteTensor* input_tensor;
// TfLiteTensor* output_tensor;

// The 2D array of 5000 rows and 2 columns.
// float** data_array = (float**)malloc(5000 * sizeof(float*));
/*
float** data_array = (float**)malloc(5000 * sizeof(float*));
for(int k = 0; k < 5000; k++) 
{
  data_array1[k] = malloc(2 * sizeof(float));
}
*/

// The float array.
// float* floatData = malloc(5000 * 2 * sizeof(float));

// Create a memory buffer in the micro:
// byte define the type of the array and `tensorArena` is the name of the array.
// [tensorArenaSize] is the size of the array. In this case, the array has a size of tensorArenaSize bytes.
// __attribute__((aligned(16))) is an attribute that tells the compiler to align the memory for 
// the array on a 16-byte boundary.
constexpr int tensorArenaSize = 60 * 1024;
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
  // randomNumber1 = random(300);
  
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

  // Get a pointer to the input tensor data.
  // float* input_data_ptr = tflInputTensor->data.f;
  randomSeed(42);
}

void loop() 
{
  Serial.println("In void loop");
  randomNumber1 = random(1,50); 
  randomNumber2 = random(1,300); 
  float durationCh1, durationCh2;  // Variable for the duration of sound wave travel
  // float* input_data_ptr = tflInputTensor->data.f;
  // Pointers for the model input and output tensors

  // tflInputTensor = tflInterpreter->input(0);
  // tflOutputTensor = tflInterpreter->output(0);
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);

  
  // Initialize all elements of the array with the same float value
  // for(int i = 0; i < 5000; i++)
  for(int i = 0; i < 5000; i++)
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
    durationCh1 = float(durationCh1);
    // durationCh1 = valueOne + randomNumber1;
    // arr[i][0] = durationCh1;
    arr[i][0] = input_array_1[i];
  }
  for(int i = 0; i < 5000; i++)
  {
    digitalWrite(trigPinCh1, LOW);
    delayMicroseconds(2);

    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds, as required by sensor
    digitalWrite(trigPinCh1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinCh1, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    // I need to convert the long data type to int - this is for memory usage
    durationCh2 =  pulseInFun(echoPinCh1, HIGH);
    durationCh2 = float(durationCh1);
    // durationCh2 = valueTwo + randomNumber1;
    arr[i][1] = input_array_2[i];
    }
  
    Serial.println("Reshaping Data");
    // Reshape the input data into a 3D array of shape [1, 5000, 2]
    float reshaped_data[1][5000][2];
    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 2; j++) {
            reshaped_data[0][i][j] = input_data[i][j];
        }
    }

    // Print the first few values of the reshaped data for verification
    for (int i = 0; i < 5; i++) {
        Serial.println(reshaped_data[0][i][0]);
        Serial.println(reshaped_data[0][i][1]);
    }

  while(samplesRead ==  numSamples) // SAMPLES_LIMIT = 10000
  {
    samplesRead = 0;
    break;
  }
  // for(i=0; i<5000; i++)  

  for (int i = 0; i < 5000; i++) 
  {
    for (int j = 0; j < 2; j++) 
    {
      // floatData[i * 2 + j] = data[i][j];
      // tflInputTensor->data.f[i * 2 + j] = data_array[i][j];
      // tflInputTensor->data.f[i * 2 + j] = arr[i][j];
      tflInputTensor->data.f[i * 2 + j] = reshaped_data[0][i][j];
    }
  }
  // if(samplesRead == numSamples)
  // { 
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
      Serial.println(tflOutputTensor->data.f[i],2); // The int here gives the decimal places
    }
    //======================================================= */ 
    Serial.println();
    delay(2000);
  // }
}
 