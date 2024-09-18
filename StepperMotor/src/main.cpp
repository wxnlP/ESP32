#include <Arduino.h>

#define Enable  5   
#define Dir     18  
#define Step    19  

// 状态值
#define FORWARD     1
#define ROLLBACK    0
#define ENABLE      1
#define DISABLE     0
// LEDC 外设
#define FREQ        500    // 频率
#define CHANNEL     0       // 通道
#define RESOLUTION  8       // 分辨率

void setup() {
    pinMode(Enable, OUTPUT);
    pinMode(Dir, OUTPUT);
    pinMode(Step, OUTPUT);
    digitalWrite(Enable, ENABLE);
    ledcSetup(CHANNEL, FREQ, RESOLUTION);
    ledcAttachPin(Step, CHANNEL);
}

void loop() {
    digitalWrite(Dir, FORWARD);
    ledcWrite(CHANNEL, 50);
}

