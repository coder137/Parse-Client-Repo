#ifndef configs_H
#define configs_H

#include <string.h>

const char serverIpAddress[] = "http://192.168.29.186:1337/parse/classes/";
const char serverDevicesClass[] = "Devices";
const char serverQuery[] = "?where=";

#define SERVER_IP_ADD_LENGTH strlen(serverIpAddress)
#define SERVER_DEVICES_CLASS_LENGTH strlen(serverDevicesClass)
#define SERVER_QUERY_LENGTH strlen(serverQuery)

#endif