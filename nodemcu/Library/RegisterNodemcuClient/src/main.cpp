#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#include <Ticker.h>

// ? lib deps
#include <WebSocketsClient.h>

// ! lib
#include <cJSON.h>
#include <LiveQueryObject.h>
#include <LiveQueryUser.h>
#include <HttpRequests.h>

// ! Own
#include "password.h"

// ? Pins
uint8_t pin = D4;


void setup() 
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    Serial.begin(9600);
    while(!Serial);

    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting...");
    }
    Serial.printf("LocalIP: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("MacAddr: %s\n", WiFi.macAddress().c_str());

    //TODO, Get Request depending on query
}

void loop() 
{
    // put your main code here, to run repeatedly:
}
