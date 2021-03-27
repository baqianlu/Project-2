//ONENET MQTT
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
const char* ssid = "vaemc";  //你家的WIFI账号
const char* password = "1224657851";//你家的WIFI密码
// MQTT 配置

#define IP  "183.230.40.39"
#define MQTT_PORT 6002
#define PRODUCT_ID    "400534" //产品ID
#define DEVICE_ID    "684134736" //设备ID
#define API_KEY    "aRKrT7YLOaujgmBDxLelHW1X2b8="
#define TOPIC     "esp8266"  //主题
#define HOST  "api.heclouds.com"




String readString; //UNO发过来的消息

WiFiClient espClient;
PubSubClient client(espClient);
HTTPClient http;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(IP, MQTT_PORT); //链接MQTT服务器
  client.setCallback(callback);


  while (!client.connected()) {


    Serial.println("正在连接MQTT服务器中.....");
    //    if (client.connect(mqtt_devicename)) {
    if (client.connect(DEVICE_ID, PRODUCT_ID, API_KEY)) { //设备ID、产品ID、apikey
      Serial.println("连接MQTT服务器成功！");
    } else {
      Serial.print("连接失败 ");
      Serial.print(client.state());
      delay(2000);
    }
  }


  client.publish(TOPIC, "hello"); //发送消息到MQTT








}

//接收服务器发来的消息
void callback(char *topic, byte *payload, unsigned int length) {
  //  Serial.print("Message arrived in topic: ");
  //  Serial.println(topic);
  //  Serial.print("Message:");
  String str = "";
  for (int i = 0; i < length; i++) {
    str += (char) payload[i];
    //Serial.print((char) payload[i]);
  }
  //  Serial.println();
  //  Serial.println("-----------------------");
  Serial.print(str);
}


void loop() {

  client.subscribe(TOPIC, 1);
  client.loop();


}
