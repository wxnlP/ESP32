#include <Arduino.h>
#include <WiFi.h>

//定义WIFI的 -账号-密码
const char* ssid = "pi";
const char* passwd = "123456789";

void setup() {
	Serial.begin(9600);

	//断开之前的WIFI连接当前WIFI
	WiFi.disconnect();
	WiFi.begin(ssid, passwd);
	Serial.println("开始连接网络......");
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println(" ");
	Serial.println("WiFi连接成功。");
	Serial.print("网络IP:");
	Serial.println(WiFi.localIP());

}

void loop() {

}
