#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <WebSocketsClient.h>

#include <Ticker.h>

// ! lib
#include <cJSON.h>
#include <LiveQueryObject.h>

// ! Password files
#include "password.h"

IPAddress ip(192, 168, 29, 100);
IPAddress gateway(192, 168, 29, 1);
IPAddress subnet(255, 255, 255, 0);

WebSocketsClient webSocket;

// ? Debug pin
uint8_t pin = D4;

// ? Variables

// ? Function Defn
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);

Ticker attachConnectedTicker;

/**
 * DONE, Create and parse json
 * TODO, Create a library for making json objects
 * DONE, Connect
 * TODO, Subscribe
 * 
 * TODO, Parse Events
 * TODO, create
 * TODO, enter
 * TODO, update
 * TODO, leave
 * TODO, delete
 */
void setup() 
{
    // ? Init pins
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    // ? Init Serial Monitor
    Serial.begin(9600);
    while(!Serial);
    
    // ? Wifi Init
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();

    Serial.println("Connected: IP Address: ");
    Serial.println(WiFi.localIP());

    // ? Init Websocket
    webSocket.begin("192.168.29.186", 1337, "/");

    webSocket.onEvent(webSocketEvent);
}

void loop() 
{
    // put your main code here, to run repeatedly:
    webSocket.loop();
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length)
{
    switch(type)
    {
        case WStype_ERROR:
        {
            Serial.printf("Error: %s\n", payload);
            break;
        }
        case WStype_DISCONNECTED:
        {
            Serial.println("Disconnected");
            break;
        }
        case WStype_CONNECTED:
        {
            Serial.printf("Connected to URL: %s\n", payload);
            // DONE, You can put your connect statement here (subscribe)
            // DONE cJSON_GetStringValue

            // ! 
            cJSON *subscribeObject = cJSON_CreateObject();
            uint8_t isCreated = createConnectToken("myAppId", subscribeObject);
            if (isCreated)
            {
                Serial.printf("Send: %s\n", cJSON_Print(subscribeObject));
                webSocket.sendTXT(cJSON_Print(subscribeObject));
                // webSocket.sendTXT("{\"op\":\"connect\",\"applicationId\": \"myAppId\"}");
            }
            else
            {
                Serial.println("Error: Connected");
            }       
            break;
        }
        case WStype_TEXT:
        {
            Serial.printf("Text Received: %s %u\n", payload, length);
            // TODO, Add other handlers here

            // !
            // DONE, Parse the payload here first
            cJSON * parseObject = cJSON_Parse((char *) payload);
            // Serial.printf("JsonObject: %s\n", cJSON_Print(parseObject) );

            const cJSON * opObject = cJSON_GetObjectItemCaseSensitive(parseObject, "op");
            Serial.printf("op param: %s\n", opObject->valuestring);

            if (strcmp(opObject->valuestring, "connected") == 0)
            {
                Serial.printf("Connected");

                //TODO, Subscribe to an object here
            }

            break;
        }
        case WStype_BIN:
        {
            Serial.printf("Get Binary Length %u\n", length);
            hexdump(payload, length);
            break;
        }
    }  
}