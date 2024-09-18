#include <Arduino.h>
#include <U8g2lib.h>

#define SDA 19
#define SCL 18

int progress;

U8G2_SSD1306_128X64_NONAME_2_SW_I2C u8g2(U8G2_R0, SCL, SDA);

void setup() {
    u8g2.begin();

}

void loop() {
    u8g2.firstPage();
    do
    {
        u8g2.drawFrame(0, 10, 128, 20);
        u8g2.drawBox(5, 15, progress, 10);

    } while(u8g2.nextPage());
    if (progress<118) progress++;
    else progress = 0;

}
