// pragma once prevents the file to be included twice
#pragma once
// #include ...
#include <Arduino.h>
// all other includes stays here in the .h file
// using namespace std;

// vars need to be extern
extern String myName;

// prototypes don't need named attributes in the .h file
void sayMyName(String);