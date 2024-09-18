#include <Arduino.h>
#include <U8g2lib.h>

#define SDA 19
#define SCL 18
//I2C四针OLED屏幕，软件模拟I2C
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, SCL, SDA);


void setup() {
    //初始化
    u8g2.begin();
    //开启中文字符集支持
    u8g2.enableUTF8Print();

}

void loop() {
    //设置字体(官方提供的字符有限，推荐查看https://github.com/larryli/u8g2_wqy)
    u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    //设置字体方向
    u8g2.setFontDirection(0);
    //清除缓存
    u8g2.clearBuffer();
    //设置光标
    u8g2.setCursor(0, 15);
    //打印
    u8g2.print("Hello ESP32!");
    u8g2.setCursor(0, 32);
    u8g2.print("你好，志豪!");
    //发送缓存到显示器
    u8g2.sendBuffer();

}

