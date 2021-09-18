/*
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "VAAL-2021";
const char* password = "kope@new21";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.1.21:8008/check";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 500;
int led = 15;

void setup() {
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {

  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {

        String payload = http.getString();
        Serial.println(payload);

        if (payload == "off") {
          digitalWrite(led, LOW);
        } 
        if (payload == "on"){
          digitalWrite(led, HIGH);
        }
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}*/

//order 
// white green orange yellow
//from   left to right if car is facing u

int front_left = 0;
int back_left = 2;

int front_right = 15;
int back_right = 13;

void setup(){
  pinMode(front_right, OUTPUT);
  pinMode(front_left, OUTPUT);
  
  pinMode(back_right, OUTPUT);
  pinMode(back_left, OUTPUT);

}

void loop(){
  m_front();

  delay(2000);

  m_stop();

  delay(750);

  m_left();

  delay(1500);

  m_stop();

  delay(750);

  m_front();

  delay(1000);

}

void m_front(){
  digitalWrite(front_left, HIGH);
  digitalWrite(front_right, HIGH);

  digitalWrite(back_left, LOW);
  digitalWrite(back_right, LOW);  
}

void m_right(){
  digitalWrite(front_left, HIGH);
  digitalWrite(front_right, LOW);

  digitalWrite(back_left, LOW);
  digitalWrite(back_right, LOW);  
}

void m_left(){
  digitalWrite(front_left, LOW);
  digitalWrite(front_right, HIGH);

  digitalWrite(back_left, LOW);
  digitalWrite(back_right, LOW);  
}

void m_back(){
  digitalWrite(front_left, LOW);
  digitalWrite(front_right, LOW);

  digitalWrite(back_left, HIGH);
  digitalWrite(back_right, HIGH);  
}

void m_stop(){
  digitalWrite(front_left, LOW);
  digitalWrite(front_right, LOW);

  digitalWrite(back_left, LOW);
  digitalWrite(back_right, LOW);  
  
}
