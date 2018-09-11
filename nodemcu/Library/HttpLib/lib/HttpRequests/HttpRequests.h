#ifndef HttpRequests_H
#define HttpRequests_H

#include <ESP8266HTTPClient.h>

char * parseServer_getRequest(const char *url, const char *applicationId, int * status);
char * parseServer_postRequest(const char *url, const char *applicationId, const char * data, int * status);
char * parseServer_putRequest(const char *url, const char *applicationId, const char * data, int * status);

// ? Helper
void parseServer_addHeaderToClient(HTTPClient &http, const char *url, const char *applicationId);
char * parseServer_returnData(HTTPClient &http, int *status);

#endif
