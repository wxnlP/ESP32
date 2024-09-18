#ifndef __OLED_H

#define SDA 19
#define SCL 18

void OLED_Init(void);
void OLED_String(int direction, int cursor_x, int cursor_y, int str);

#endif
