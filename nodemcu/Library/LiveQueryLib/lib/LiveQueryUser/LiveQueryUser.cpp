#include "LiveQueryUser.h"

#include <cJSON.h>
#include <LiveQueryObject.h>

// TODO, Make ApplicationID dynamic
uint8_t connectToServer(WebSocketsClient &webSocket)
{
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
    cJSON_Delete(connectObject);

    return isCreated;
}

uint8_t subscribeToServer(WebSocketsClient &webSocket, const char *className, const char *key, const char *value)
{    
    cJSON * subscribeObject = cJSON_CreateObject();
    uint8_t isCreated = createSubscribeToken(className, key, value, subscribeObject);
    if(isCreated)
    {
        Serial.printf("Send: %s\n", cJSON_Print(subscribeObject));
        webSocket.sendTXT(cJSON_Print(subscribeObject));
    }
    else
    {
        Serial.println("Error: Subscribe");
    }
    cJSON_Delete(subscribeObject);

    return isCreated;
}
