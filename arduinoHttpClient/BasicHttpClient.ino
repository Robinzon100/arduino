#include <ArduinoJson.h>
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

const char* wifi_name     = "ukrainka";
const char* wifi_password = "gabrieli04";
const char* api_http_url = "http://robled.herokuapp.com/state";



void setup() {
  pinMode(D7, OUTPUT);
  

  StaticJsonDocument<200> doc;

  Serial.begin(115200);


  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("THE MAGIC WILL HAPPEN IN %d...\n", t);
    Serial.flush();
    delay(1000);
    Serial.printf("listening to api at %d...\n", api_http_url );
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(wifi_name, wifi_password);

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    StaticJsonDocument<200> doc;

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, api_http_url)) {  // HTTP


       
      int httpCode = http.GET();

      
      if (httpCode > 0) {
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);

          DeserializationError error = deserializeJson(doc, payload);
          if (error) {
            Serial.println(error.c_str());
            return;
          }

          String state = doc["state"];
          Serial.println(state);
 
          if(state == "on"){
              digitalWrite(D7, HIGH);
          }else{
            digitalWrite(D7, LOW);
          }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(1000);
}
