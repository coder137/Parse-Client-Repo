#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <WebSocketsClient.h>

#include <Ticker.h>

// ! lib
#include <cJSON.h>
#include <LiveQueryObject.h>
#include <LiveQueryUser.h>

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
void getMemoryHeap();

Ticker attachConnectedTicker;
Ticker MemoryHeapTicker;

/**
 * DONE, Create and parse json
 * DONE, Create a library for making json objects
 * DONE, Connect
 * DONE, Subscribe
 * 
 * DONE, Parse Events
 * DONE, Attach Custom Event handler
 * DONE, Create a different lib to work with the various events 
 * DONE, [IMP] Check memory leakage and usage (CJSON * Objects) (Call cJSON_Delete)
 * ., create
 * ., enter
 * ., update
 * ., leave
 * ., delete
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
    Serial.println(WiFi.macAddress());

    // ? Tickers
    MemoryHeapTicker.attach_ms(200, getMemoryHeap);

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
            connectToServer(webSocket);
            break;
        }
        case WStype_TEXT:
        {
            Serial.printf("Text Received: %s %u\n", payload, length);

            // DONE, Make OP names dynamic
            // DONE, Parse the payload here first
            cJSON * parseObject = cJSON_Parse((char *) payload);
            cJSON * opObject = cJSON_GetObjectItemCaseSensitive(parseObject, LIVEQUERY_OP);

            // ? Debugging
            Serial.printf("OP param: %s\n", opObject->valuestring);

            if (strcmp(opObject->valuestring, LIVEQUERY_IS_CONNECTED) == 0)
            {
                Serial.println("Connected");
                subscribeToServer(webSocket, "Test", "name", "test");
            }

            if (strcmp(opObject->valuestring, LIVEQUERY_IS_SUBSCRIBED) == 0)
            {
                Serial.println("Subscribed");
            }

            // NOTE, This is how the check occurs
            // if (strcmp(opObject->valuestring, "") == 0)
            // {
            //     Serial.printf("");
                
            // }

            cJSON_Delete(parseObject);
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

void getMemoryHeap()
{
    Serial.printf("MemoryHeap: %" PRIu32 "\n", ESP.getFreeHeap());
}
