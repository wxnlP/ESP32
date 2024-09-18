#include <Arduino.h>

//引脚定义
#define LED 15
#define DCP 13          //电位器模拟摇杆
#define Resolution 12   //分辨率
#define Channel 0       //通道
#define Freq 50         //PWM频率

int value;
//模拟舵机控制周期
//对应 0.5ms（0.5ms/(20ms/256)）
int min_width = 0.5 / 20 * pow(2, Resolution);
//对应 2.5ms（2.5ms/（20ms/256））
int max_width = 2.5 / 20 * pow(2, Resolution);

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DCP, INPUT);
    //配置模拟输入
    analogReadResolution(Resolution); //12位分辨率--范围-> 0~4096
    analogSetAttenuation(ADC_11db);   //输入衰减
    //配置PWM输出
    ledcSetup(Channel, Freq, Resolution);
    ledcAttachPin(LED, Channel);
    //串口
    Serial.begin(9600);
}

void loop() {
    value = map(analogRead(DCP), 0, pow(2, Resolution), min_width, max_width);
    Serial.printf("读取的实际模拟值:%d\r\n映射以后的模拟值:%d\r\n", analogRead(DCP), value);
    Serial.println("------------------------------------------");
    ledcWrite(Channel, value);
    delay(500);
}

