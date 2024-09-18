#include <Arduino.h>

#define FREQ        2000    // 频率
#define CHANNEL     0       // 通道
#define RESOLUTION  8       // 分辨率
#define LED         12      // LED 引脚


void setup() {
    // put your setup code here, to run once:
    ledcSetup(CHANNEL, FREQ, RESOLUTION);
    ledcAttachPin(LED, CHANNEL);
}

void loop() {
    // put your main code here, to run repeatedly:
    ledcWrite(CHANNEL, 50);
    
}

