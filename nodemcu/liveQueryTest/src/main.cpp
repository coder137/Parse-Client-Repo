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
 * DONE, Create a library for making json objects
 * DONE, Connect
 * DONE, Subscribe
 * 
 * DONE, Parse Events
 * TODO, Attach Custom Event handler
 * TODO, Create a different lib to work with the various events 
 * TODO, [IMP] Check memory leakage and usage (CJSON * Objects) (Call cJSON_Delete)
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

            // TODO, Transfer this code into a function in lib
            // ! 
            cJSON *connectObject = cJSON_CreateObject();
            uint8_t isCreated = createConnectToken("myAppId", connectObject);
            if (isCreated)
            {
                Serial.printf("Send: %s\n", cJSON_Print(connectObject));
                webSocket.sendTXT(cJSON_Print(connectObject));
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

            // TODO, Make OP names dynamic
            // !
            // DONE, Parse the payload here first
            cJSON * parseObject = cJSON_Parse((char *) payload);
            const cJSON * opObject = cJSON_GetObjectItemCaseSensitive(parseObject, "op");

            // ? Debugging
            Serial.printf("OP param: %s\n", opObject->valuestring);
            // Serial.printf("JsonObject: %s\n", cJSON_Print(parseObject) );

            if (strcmp(opObject->valuestring, "connected") == 0)
            {
                Serial.printf("Connected");
                //DONE, Subscribe to an object here
                cJSON * subscribeObject = cJSON_CreateObject();
                cJSON * identifier_object = cJSON_CreateObject();
                
                uint8_t isCreated = deleteJSONObject_IfNull( cJSON_AddStringToObject(identifier_object, "name", "test") );
                isCreated &= createSubscribeToken("Test", identifier_object, subscribeObject);

                if(isCreated)
                {
                    Serial.printf("Send: %s\n", cJSON_Print(subscribeObject));
                    webSocket.sendTXT(cJSON_Print(subscribeObject));
                }
                else
                {
                    Serial.println("Error: Subscribed");
                }
            }

            if (strcmp(opObject->valuestring, "subscribed") == 0)
            {
                Serial.println("Subscribed");
            }

            // NOTE, This is how the check occurs
            // if (strcmp(opObject->valuestring, "") == 0)
            // {
            //     Serial.printf("");
                
            // }

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