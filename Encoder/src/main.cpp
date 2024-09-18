#include <Arduino.h>
#include <U8g2lib.h>
#include "OLED.h"

#define A 15
#define B 4

long int count = 0;
void read_Aencoder()
{
    if(digitalRead(A) == 0)
    {
        if(digitalRead(B) == 1) {count++;}
        else {count--;}
    }
    if(digitalRead(A) == 1)
    {
        if(digitalRead(B) == 0) {count++;}
        else {count--;}
    }
}

void read_Bencoder()
{
    if(digitalRead(B) == 0)
    {
        if(digitalRead(A) == 0) {count++;}
        else {count--;}
    }
    if(digitalRead(B) == 1)
    {
        if(digitalRead(A) == 1) {count++;}
        else {count--;}
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(A, INPUT);
    pinMode(B, INPUT);
    attachInterrupt(A, read_Aencoder, CHANGE);
    attachInterrupt(B, read_Bencoder, CHANGE);
    interrupts();
    OLED_Init();

}

void loop() {
    // OLED_String(0, 64, 32, "This a string.");
    // OLED_String(1, 64, 32, "This a string.");
    // OLED_String(2, 64, 32, "This a string.");
    // OLED_String(3, 64, 32, "This a string.");
    OLED_String(0, 0, 16, count);
}

