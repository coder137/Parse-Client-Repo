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

#include <DatabaseObjectSchema.h>

// ! Own
#include "password.h"
// #include "config.h"

// ? Pins
uint8_t pin = D4;


void setup() 
{
    // ? Pins
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    // ? Serial Monitor
    Serial.begin(9600);
    while(!Serial);

    // ? Wifi Action
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting...");
    }
    Serial.printf("LocalIP: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("MacAddr: %s\n", WiFi.macAddress().c_str());

    // DONE, Do not move forward till connection to database isn't established
    int status;
    char * url = createInitialGetRequestUrl(WiFi.macAddress().c_str());
    Serial.printf("url: %s\n", url);

    char * payload = parseServer_getRequest(url, "myAppId", &status);
    while(status != HTTP_CODE_OK)
    {
        Serial.printf("Status: %d\n", status);

        free(payload);
        payload = parseServer_getRequest(url, "myAppId", &status);
        delay(1000);
    }
    free(url);

    Serial.println(payload);

    // TODO, Make this modular
    // TODO, From here we start Validating the database
    
    // DONE, Parse the object
    // DONE get the "results" object
    cJSON *object = cJSON_Parse(payload);
    cJSON *arrayObject = cJSON_GetObjectItemCaseSensitive(object, "results"); 

    int size = cJSON_GetArraySize(arrayObject);
    Serial.printf("Size: %d\n", size);

    cJSON_Delete(object);    

    if(size == 0)
    {
        // DONE, Create a class schema using cJSON
        cJSON *databaseSchema = cJSON_CreateObject();
        createInitialDatabaseSchema(databaseSchema, WiFi.macAddress().c_str());
        Serial.printf("%s\n\n", cJSON_Print(databaseSchema));

        // DONE, parseServer_postRequest
        char post_url[] = "";
        strcat(post_url, serverIpAddress);
        strcat(post_url, serverDevicesClass);
        Serial.printf("PostURL: %s\n", post_url);

        int post_status;
        char * postRequestPayload = parseServer_postRequest(post_url, "myAppId", cJSON_Print(databaseSchema), &post_status);

        Serial.println(post_status);
        Serial.println(postRequestPayload);

        if (post_status != HTTP_CODE_CREATED)
        {
            // TODO, There is a problem here (DO NOT CONTINUE)
            // ! This problem should mostly NOT occur (Due to the status == HTTP_CODE_OK check above)
        }

        // Free all the memory here
        Serial.println("Freeing POST Objects");
        free(postRequestPayload);
        cJSON_Delete(databaseSchema);
        Serial.println("DONE Freeing POST Objects");
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
        // TODO, parseServer_postRequest

        // ! OR

        // TODO, Find the most recent updated value (??)
        // TODO, Delete all the other objects related to this schema
    }

    // ! Free the Objects
    Serial.println("Freeing GLOBAL Get objects");
    free(payload); // ! IMP, Free top payload
    Serial.println("Done Freeing GLOBAL Objects");
}

void loop() 
{
    // put your main code here, to run repeatedly:
}
