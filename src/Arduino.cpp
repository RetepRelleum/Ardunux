#include "Arduino.h"
#include <math.h>

int analogRead(int in)
{
    int ret=(int)(250.0 * sin(2.0 * M_PI * (double)(micros()) / 1000000 * 340));
    return ret;
    
}

void analogReadResolution(int a){
    
}
int digitalRead(int in){
    return 0;
}

int touchRead(int in ){
    return random(0,500);
}