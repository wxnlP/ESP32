#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// 阿里云设备信息
const char* productKey = "k0v2sE6vkvg";
const char* deviceName = "esp32";
const char* deviceSecret = "3a27d38a9232c75bf2147e7643724429";

// WiFi信息
const char* ssid = "CMCC-a7u7";
const char* password = "fd5gm9uu";

// 阿里云MQTT服务器地址
const char* mqttServer = "iot-06z00fd1p0l73zk.mqtt.iothub.aliyuncs.com";
const int mqttPort = 1883;

// 使用Google的公共DNS
// IPAddress dnsServer(8, 8, 8, 8);

WiFiClient espClient;
PubSubClient client(espClient);

// JSON对象
StaticJsonDocument<200> doc;

void connectWiFi();
void connectMQTT();
void callback(char* topic, byte* payload, unsigned int length);
void storeData(const char* data);

void setup() {
  Serial.begin(115200);
  connectWiFi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  // 构建JSON对象
  doc["method"] = "thing.service.property.set";
  doc["id"] = "1100426949";
  JsonObject params = doc.createNestedObject("params");
  params["LOCK"] = 0; // 添加属性
  doc["version"] = "1.0.0";

  connectMQTT();
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  // 序列化JSON对象为字符串
  char payload[256];
  size_t n = serializeJson(doc, payload, sizeof(payload));

  // 发布消息到MQTT服务器
  if (client.publish("/sys/k0v2sE6vkvg/esp32/thing/event/property/post", payload)) {
    Serial.println("Message published");
  } else {
    Serial.println("Message publish failed");
  }

  delay(10000); // 10秒发送一次
}

void connectWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  // 使用固定的DNS服务器
  // WiFi.config(INADDR_NONE, INADDR_NONE, dnsServer);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    String clientId = "k0v2sE6vkvg.esp32|securemode=2,signmethod=hmacsha256,timestamp=1719630866616|";
    if (client.connect(clientId, deviceName, deviceSecret)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // 处理从MQTT服务器接收到的消息
}

void storeData(const char* data) {
  StaticJsonDocument<200> doc;
  deserializeJson(doc, data);
  int lockState = doc["params"]["LOCK"];

  // 将lockState存储到EEPROM或文件系统
  Serial.print("LOCK state: ");
  Serial.println(lockState);
  // 这里可以添加具体的存储逻辑
}
