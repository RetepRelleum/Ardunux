#ifndef ARDUINO_H_INCLUDED
#define ARDUINO_H_INCLUDED

#define __ESP_ARDU
#include "posixTime.h"
#include "WString.h"
#include <stdio.h>
#include <SerialConsole.h>
#include <iostream>

const double PI = 3.141592653589793238460;
const int A1 = 1;

int analogRead(int in);
int digitalRead(int in);

void analogReadResolution(int a);

using namespace std;

//typedef bool int;
typedef uint8_t byte;

long random(long);
long random(long, long);
void randomSeed(unsigned long);
long map(long, long, long, long, long);

#endif // ARDUINO_H_INCLUDED

void setup(void);
void loop(void);
uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)