#include <Arduino.h>
#include <U8g2lib.h>
#include "OLED.h"


//I2C四针OLED屏幕，软件模拟I2C
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, SCL, SDA);

/* OLED初始化
 * 无参数
 * 无返回
 */
void OLED_Init(void)
{
    //初始化
    u8g2.begin();
    //开启中文字符集支持
    u8g2.enableUTF8Print();
    //设置字体(官方提供的字符有限，推荐查看https://github.com/larryli/u8g2_wqy)
    u8g2.setFont(u8g2_font_wqy14_t_gb2312);

}

/* OLED输出字符串
 * 参数: int direction, int cursor_x, int cursor_y, const char* str
 * 无返回
 */
void OLED_String(int direction, int cursor_x, int cursor_y, int str)
{
    //设置字体方向
    u8g2.setFontDirection(direction);
    //清除缓存
    u8g2.clearBuffer();
    //设置光标
    u8g2.setCursor(cursor_x, cursor_y);
    //打印
    u8g2.print(str);
    //发送缓存到显示器
    u8g2.sendBuffer();
}

