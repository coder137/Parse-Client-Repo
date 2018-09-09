#ifndef LiveQueryUser_H
#define LiveQueryUser_H

#include <WebSocketsClient.h>

uint8_t connectToServer(WebSocketsClient &webSocket);
uint8_t subscribeToServer(WebSocketsClient &webSocket, const char *className, const char *key, const char *value);

#endif
