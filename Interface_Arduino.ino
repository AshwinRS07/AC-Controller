#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A0
#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

float temp,humi,heatIndex;
String str;

SoftwareSerial s(5,6);

void setup(){
 s.begin(9600);
// pinMode(A0,INPUT);
 dht.begin();
}
void loop()
{
  
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  heatIndex = dht.computeHeatIndex(temp,humi,false);
 // s.println(temp);
  //s.println(humi);
 // s.println(heatIndex);
  root["temp"] = temp;
  root["humidity"] = humi;
  root["heatIndex"] = heatIndex;
  
  if(s.available() > 0){
//    Serial.write(mySerial.read());
  root.printTo(s);
  //Serial.println("");
  }  
  delay(5000);
  
}
