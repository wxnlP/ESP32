#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <string.h>
#include <ArduinoJson.h>

/* 
ProductKey  k0v2sE6vkvg
DeviceSecret    3a27d38a9232c75bf2147e7643724429
DeviceName  esp32
Region  cn-shanghai
MQTT连接参数
{
    "clientId": "",
    "username": "",
    "mqttHost": "",
    "passwd": "",
    "port": 1883
}
*/

//MQTT连接参数
#define   MQTT_host         "e8580caa81.st1.iotda-device.cn-north-4.myhuaweicloud.com"     
#define   MQTT_port         1883
#define   MQTT_client_id    ""
#define   MQTT_username     ""
#define   MQTT_password     ""
#define   DeviceId          ""
//阿里云平台的话题定义
#define   MQTT_PublishTopic     "$oc/devices/667c326d7dbfd46fabc23238_wxnlP/sys/properties/report"
#define   MQTT_GetTopic         "$oc/devices/667c326d7dbfd46fabc23238_wxnlP/sys/shadow/get/request_id={request_id}"
#define   MQTT_SubscribeTopic   "$oc/devices/667c326d7dbfd46fabc23238_wxnlP/sys/shadow/get/response/#"
//WiFi参数
#define   WiFi_ssid  "CMCC-a7u7"
#define   WiFi_password  "fd5gm9uu"

//定义WiFi对象和MQTT对象
WiFiClient espClient;
PubSubClient  client(espClient);
//模拟数据发送

unsigned long lastMs = 0;
// 构建上传的数据
//引脚定义
const int buttonPin = 2;
int buttonState = 0;
int lastButtonState = 0;

/*WiFi初始化函数*/
void WiFi_Init(void)
{
    
    WiFi.begin(WiFi_ssid, WiFi_password);
    Serial.print("正在连接WiFi中");
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" ");
    Serial.println("连接成功！");
    Serial.print("网络IP:");
    Serial.println(WiFi.localIP());
}

/*MQTT连接函数*/
void MQTT_Connection(void)
{
    //若MQTT没有连接，则建立连接
    while(!client.connected())
    {
        Serial.println("MQTT Server is connecting....");
        delay(60);
        //创建MQTT连接
        if(client.connect(MQTT_client_id, MQTT_username, MQTT_password))
        {
            Serial.println("MQTT Connected!");
        }
        //如果连接失败，返回错误状态码
        else
        {
            Serial.print("MQTT Connect err:");
            Serial.println(client.state());
            delay(5000);
        }
    }
}


void DataUpload(bool de_status)
{
    // 构建JSON对象
    JsonDocument  doc;
    JsonObject service = doc.createNestedArray("services").createNestedObject();
    service["service_id"] = "001";
    JsonObject properties = service.createNestedObject("properties");
    properties["ON_OFF"] = de_status;
    properties["address"] = 2024;
    
    // 将JSON对象序列化为字符串
    char buffer[256];
    size_t n = serializeJson(doc, buffer);
    
    boolean status = client.publish(MQTT_PublishTopic, buffer, n);
    if (status)
    {
        Serial.println("数据上传成功！");
        // Serial.println(buffer);
    }
    else Serial.println("数据上传失败");
}

void Get(void)
{
    // 构建JSON对象
    JsonDocument  doc1;
    doc1["object_device_id"] = "667c326d7dbfd46fabc23238_wxnlP";
    doc1["service_id"] = "001";
    
    // 将JSON对象序列化为字符串
    char buffer[256];
    size_t n = serializeJson(doc1, buffer);
    
    boolean status = client.publish(MQTT_GetTopic, buffer, n);
    if (status)
    {
        Serial.println("数据上传成功！");
        Serial.println(buffer);
    }
    else Serial.println("数据上传失败");
}

/*订阅话题的回调函数*/
// void callback(char* topic, byte* payload, unsigned int length)
// {
//     Serial.println("Message arrived [");
//     Serial.print(topic);
//     Serial.print("]");
//     Serial.println();
//     Serial.println("响应数据：");
//     for (int i=0; i<length; i++)
//     {
//         Serial.println((char)payload[i]);
//     }
//     Serial.println();

// }
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.println("]");

    // 将 payload 转换为 String 类型
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    Serial.println("响应数据：");
    Serial.println(message);

    // 使用 ArduinoJson 解析 JSON 数据
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, message);

    if (error) {
        Serial.print("JSON parsing failed: ");
        Serial.println(error.c_str());
        return;
    }

    // 提取所需的键值对
    bool desired_on_off = doc["shadow"][0]["desired"]["properties"]["ON_OFF"];
    const char* desired_event_time = doc["shadow"][0]["desired"]["event_time"];
    bool reported_on_off = doc["shadow"][0]["reported"]["properties"]["ON_OFF"];
    int address = doc["shadow"][0]["reported"]["properties"]["address"];
    const char* reported_event_time = doc["shadow"][0]["reported"]["event_time"];
    int version = doc["shadow"][0]["version"];
    const char* service_id = doc["shadow"][0]["service_id"];
    const char* object_device_id = doc["object_device_id"];

    // 打印结果
    Serial.println("Desired ON_OFF: " + String(desired_on_off));
    Serial.println("Desired Event Time: " + String(desired_event_time));
    Serial.println("Reported ON_OFF: " + String(reported_on_off));
    Serial.println("Address: " + String(address));
    Serial.println("Reported Event Time: " + String(reported_event_time));
    Serial.println("Version: " + String(version));
    Serial.println("Service ID: " + String(service_id));
    Serial.println("Object Device ID: " + String(object_device_id));
    if (desired_on_off != reported_on_off) {DataUpload(desired_on_off);}
    
}

void setup() 
{

    Serial.begin(9600);
    WiFi_Init();
    client.setServer(MQTT_host, MQTT_port);
    client.setCallback(callback);
    client.subscribe(MQTT_SubscribeTopic);
}

void loop() 
{
    MQTT_Connection();
    // 读取按钮状态
    buttonState = digitalRead(buttonPin);

    // 检查按钮是否被按下
    if (buttonState == LOW && lastButtonState == HIGH) {
        // 按钮被按下，准备发送数据
        Serial.println("Button pressed, sending data...");
        Get();
    }
    lastButtonState = buttonState;

    // 保持MQTT客户端运行（如果需要）
    client.loop(); // 根据需要启用
    delay(50); // 去抖动
    
}

