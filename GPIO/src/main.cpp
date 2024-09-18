#include <Arduino.h>

// 引脚定义
int LED_Green = 2;
int KEY1 = 14;
int KeyStatus = 0;
 //状态标志位

int ChangeStatus(int KeyStatus)
{
	int Status = KeyStatus;
	if (digitalRead(KEY1) == 0)
	{
		delay(20);
		while (digitalRead(KEY1)==0);
		delay(20);
		if (Status == 0){Status = 1;}
		else {Status = 0;}
	}
	return Status;	
}

void setup() {
	// put your setup code here, to run once:
	pinMode(KEY1, INPUT_PULLUP); // 按键下拉输入
	pinMode(LED_Green, OUTPUT);

}

void loop() {
	// put your main code here, to run repeatedly:
	KeyStatus = ChangeStatus(KeyStatus);
	digitalWrite(LED_Green, KeyStatus);

}

