#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Ticker.h>

// ? Own Libs
#include <HttpRequests.h>

// !
#include "password.h"

// ? Pins
uint8_t pin = D4;

// ? Class Declarations
Ticker memoryHeapTicker;

// ? Functions
void getMemoryHeap();

void testGetRequest();

void setup() 
{
    // ? Pins    
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    // ? Serial 
    Serial.begin(9600);
    while(!Serial);

    // ? WiFi
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting...");
    }
    Serial.println();
    Serial.printf("LocalIP: %s\n", WiFi.localIP().toString().c_str());

    // ? Ticker
    memoryHeapTicker.attach_ms(200, getMemoryHeap);

    // ? HTTP Client    
}

void loop() 
{
    // put your main code here, to run repeatedly:
    testGetRequest();
    delay(1000);
}

void testGetRequest()
{
    int status;
    char * payload = parseServer_getRequest("http://192.168.29.186:1337/parse/classes/Test", "myAppId", &status);
    Serial.printf("Payload: %s\n", payload);
    Serial.printf("Status: %d\n", status);
    free(payload); // ! You have to free the payload
    Serial.println("\n\n");
}

void getMemoryHeap()
{
    Serial.printf("Free Memory Heap: %" PRIu32 "\n", ESP.getFreeHeap());
}
