#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

/*定义变量*/
const char* ssid = "pi";
const char* password = "123456789";
int httpCode;

String http = "http://apis.juhe.cn/simpleWeather/query";
String key = "601e49e0abae983d06b21dc7a05f6b2a";
String city = "上海";
String url = http + "?city=" + city + "&key=" + key ;
String data;

String weather;
unsigned int temperature;
String direct;

/*自定义函数*/

/* 网络连接函数
参数1：ssid(网络名称)
参数2：passwd(密码)
返回值：无
*/
void WiFiConnect(const char* ssid, const char* password)
{
    Serial.println(" ");
    Serial.print("开始连接网络");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }
    Serial.println(" ");
    Serial.println("[INFO] WiFi连接成功。");
    Serial.print("[INFO] IP:");
    Serial.println(WiFi.localIP());
}

/* 网络请求函数
参数：无
返回值：无
*/
void WiFiRquest(void)
{
    //创建HTTPClient对象
    HTTPClient Client;
    Client.begin(url);
    httpCode = Client.GET(); 
    Serial.printf("[INFO] HTTP状态码:%d\r\n", httpCode);
    data = Client.getString();
    // Serial.print("[INFO] 天气数据:\r\n");
    // Serial.println(data);
    DynamicJsonDocument Doc(1024);
    deserializeJson(Doc, data);
    weather = Doc["result"]["realtime"]["info"].as<String>();
    temperature = Doc["result"]["realtime"]["temperature"].as<unsigned int>();
    direct = Doc["result"]["realtime"]["direct"].as<String>();
    Serial.printf("[INFO] 天气:%s\r\n", weather);
    Serial.printf("[INFO] 温度:%d°C\r\n", temperature);
    Serial.printf("[INFO] 风向:%s\r\n", direct);

}


void setup() {
    //初始化串口
    Serial.begin(9600);
    delay(100);
    WiFiConnect(ssid, password);
    WiFiRquest();
}

void loop() {

}
