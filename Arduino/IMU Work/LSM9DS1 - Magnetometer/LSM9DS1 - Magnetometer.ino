/*
  Arduino LSM9DS1 - Magnetometer work

  This work will use the magnetometer which is part of the LSM9DS1 sensor and the
  `analogWrite` function with the built-in LED, varying the intensity relative to the
  surrounding electrical devices
*/

#include <Arduino_LSM9DS1.h>

float x, y, z, ledValue;

void setup
