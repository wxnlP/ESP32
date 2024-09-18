#include <Arduino.h>

#define port 14

uint16_t port_value;

void setup() {
    Serial.begin(9600);
    // pinMode(port, INPUT);
    analogReadResolution(12); //12 位分辨率
    analogSetAttenuation(ADC_11db); // 输入衰减
    ledcSetup(0, 2000, 8);
    ledcAttachPin(12, 0);
    Serial.println("串口开始！");
}

void loop() {
    port_value = analogRead(port);
    ledcWrite(0, port_value);
    Serial.println(port_value);
    delay(50);
}

