#include <ESP8266WiFi.h>
#include <WiFiClient.h>
const char* ssid = "ONO2359";
const char* password = "utNtsvcQztm5";
 
const int sensor = 1;
const int sensorOUT = 2;
 
const char* host = "maker.ifttt.com";
const int httpsPort = 80;
String key = "8GrwCSdPqlkFLYylixP6P";
String evento = "post_tweet";
WiFiClient client;
void setup() {
 pinMode(sensor,INPUT);
 pinMode(sensorOUT,OUTPUT);
 Serial.begin(115200);
 Serial.println();
 Serial.print("Conectando wifi: ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi conectado!");
 Serial.println("IP: ");
 Serial.println(WiFi.localIP());
 
}
 
void loop() {
  
  Serial.println(digitalRead(sensor));
 delay(100);
  Serial.println(digitalRead(sensorOUT));
 delay(100);
 if(digitalRead(sensor))
 {
  Serial.println("Sensor activado");
  Serial.print("Conectando a: ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
   Serial.println("conexion fallida");
   return;
 }
 
 String url = "/trigger/"+evento+"/with/key/"+key;
 
 Serial.print("requesting URL: ");
 Serial.println(url);
 
 client.print(String("GET ") + url + " HTTP/1.1\r\n" +
 "Host: " + host + "\r\n" +
 "User-Agent: Arduino\r\n" +
 "Connection: close\r\n\r\n");
 
 Serial.println("request sent");
 while (client.connected()) {
  String line = client.readStringUntil('\n');
  if (line == "\r") {
   Serial.println("headers received");
   break;
  }
 }
 String line = client.readStringUntil('\n');
 
 Serial.println("reply was:");
 Serial.println("==========");
 Serial.println(line);
 Serial.println("==========");
 Serial.println("closing connection");
 
 delay(10000);
 }
}
