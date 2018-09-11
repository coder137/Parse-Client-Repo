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
    int status;
    char * payload = parseServer_getRequest("http://192.168.29.186:1337/parse/classes/Devices?where={\"mac\":\"A0:20:A6:1A:4B:5A\"}",
                                            "myAppId", &status);

    Serial.printf("Status: %d\n", status);
    Serial.printf("Payload: %s\n", payload);

    if(status == HTTP_CODE_OK)
    {
        // TODO, Parse the object
        // TODO get the "results" object
        cJSON *object = cJSON_Parse(payload);
        cJSON *arrayObject = cJSON_GetObjectItemCaseSensitive(object, "results"); 
        int size = cJSON_GetArraySize(arrayObject);
        Serial.printf("Size: %d\n", size);

        if(size == 0)
        {
            // TODO, Create a class schema using cJSON
            // TODO, parseServer_postRequest
        }
        else if (size == 1)
        {
            // TODO, Update the current values of the schema using cJSON
            // TODO, parseServer_putRequest
        }
        else
        {
            // ! Error shouldn't happen
            // TODO, Delete all the other objects related to this schema
            // TODO, Create a class schema using cJSON
            // TODO, parseServer_postRequest with updated values
        }

        // ! Free the Objects
        cJSON_Delete(object);    
    }
    else
    {
        Serial.println("Cannot Proceed further");
    }
    free(payload);
}

void loop() 
{
    // put your main code here, to run repeatedly:
}
