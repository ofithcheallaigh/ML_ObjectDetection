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

#include "channel1.h" //input_array_1
#include "channel2.h" //input_array_2

#include "model.h"
// #include "object_detect.h"

// Figure out what's going on in our model
#define DEBUG 1

const int numSamples = 5000;

int samplesRead = numSamples;

// Declare the 3D array of data.
float reshaped_data[1][5000][2];

// Declare the 2D array of data.
float output_data[5000][2];


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

constexpr int tensorArenaSize = 60 * 1024;
byte tensorArena[tensorArenaSize] __attribute__((aligned(16)));

// Array to map grids
const char* GRIDS[] = {
  "Zero",
  "One",
  "Two",
  "Three",
  "Four",
  "Five",
  "Six",
  "Seven",
  "Eight",
  "Nine",       
};

#define NUM_GRIDS (sizeof(GRIDS) / sizeof(GRIDS[0]))
// #define NUM_GRIDS 10

void setup() {

    // Wait for Serial to connect
  #if DEBUG
    while(!Serial);
  #endif
  delay(1000);
  Serial.begin(9600);
  while(!Serial);
  Serial.print("Starting..."); // Text to note start of data collection

    // Get the TFL repsentation of the model byte array
  tflModel = tflite::GetModel(model);
    if (tflModel->version() != TFLITE_SCHEMA_VERSION) 
    {
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

/*
  int output_shape[] = {1, 10};
  // TfLiteTensor* output_tensor = Interpreter->output(0);
  tflOutputTensor->dims->data[0] = output_shape[0];
  tflOutputTensor->dims->data[1] = output_shape[1];
*/
  // Get a pointer to the output tensor data
  // float* output_data = tflOutputTensor->data.f;

#if DEBUG
  Serial.print("Number of dimensions: ");
  Serial.println(tflInputTensor->dims->size);
  Serial.print("Dim 1 size: ");
  Serial.println(tflInputTensor->dims->data[0]);
  Serial.print("Dim 2 size: ");
  Serial.println(tflInputTensor->dims->data[1]);
  Serial.print("Input type: ");
  Serial.println(tflInputTensor->type);
#endif
}

void loop() 
{
  int i;
  while(samplesRead < numSamples)
  {
    reshaped_data[0][samplesRead][0] = input_array_1[samplesRead];
    reshaped_data[0][samplesRead][1] = input_array_2[samplesRead];

    // float value = reshaped_data[0][i][j];
    // float value = reshaped_data[0][i][j][0];
    // int input_index = j + i * 2;
    // tflInputTensor->data.f[input_index] = value;
    // tflInputTensor->data.f[0] = value;

    // tflInputTensor->data.f[samplesRead * 2 + 0] = input_array_1[samplesRead];
    // tflInputTensor->data.f[samplesRead * 2 + 1] = input_array_2[samplesRead];

    samplesRead++;

    if(samplesRead == numSamples)
    {
    // Run inferencing
    TfLiteStatus invokeStatus = tflInterpreter->Invoke();
    if (invokeStatus != kTfLiteOk) 
      {
        Serial.println("Invoke failed!");
        while (1);
        return;
      }

    for (int i = 0; i < NUM_GRIDS; i++) 
    {
      Serial.print(GRIDS[i]);
      Serial.print(": ");
      Serial.println(tflOutputTensor->data.f[i], 6);
    }
    Serial.println();
    }
  }
}

