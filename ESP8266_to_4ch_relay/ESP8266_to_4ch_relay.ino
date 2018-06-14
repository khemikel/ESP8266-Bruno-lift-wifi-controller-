#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_GFX.h>
#include <ESP_Adafruit_SSD1306.h>

////**********START CUSTOM PARAMS******************//
const char* host = "Garage_Controls"; // Bruno lift & my garage door
const char* ssid = "MY_WIFI";
const char* password = "MY_WIFI_PASSWD";
const long interval = 11000 // 11 seconds
const short interval = 1000 // 1 seconds

//Define the pins
define RELAY_PIN_1 12 // Lift 'Up'
define RELAY_PIN_2 13 // Lift 'Down'
define RELAY_PIN_3 14 // Garage door
define RELAY_PIN_4 15 // Future Use

//Define MQTT 
define mqtt_server "MQTT_IP"  //HA. 
define door_topic "sensor/lift/state1"
define button_topic "sensor/garage/action1"
define button_topic_2 "sensor/garage/action2"

const char* mqtt_user = "YOURMQTTUSER"; //HA. 
const char* mqtt_pass = "YOURMQTTPW"; //HA. 
 
//************END CUSTOM PARAMS********************//

//Setup Variables
String switch1;
String switch2;
String switch3;
String switch4;
String strTopic;
String strPayload;

void setup() {
  //Set Relay(output) and Door(input) pins
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(RELAY_PIN_4, OUTPUT);
  digitalWrite(RELAY_PIN_1, LOW);
  digitalWrite(RELAY_PIN_2, LOW);
  digitalWrite(RELAY_PIN_3, LOW);
  digitalWrite(RELAY_PIN_4, LOW);
  pinMode(DOOR_PIN, INPUT);
  Serial.begin(115200);
  client.setServer(mqtt_server, 1883
  client.setCallback(callback);
}

void loop() {
  //If MQTT client can't connect to broker, then reconnect
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); //the mqtt function that processes MQTT messages
}




void reconnect() {
  //Reconnect to Wifi and to MQTT. If Wifi is already connected, then autoconnect doesn't do anything.
  Serial.print("Attempting MQTT connection...");
  if (client.connect(host, mqtt_user, mqtt_pass)) {
    Serial.println("connected");
    client.subscribe("sensor/garage/#");
  } else {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    // Wait 5 seconds before retrying
    delay(5000);
  }
}
