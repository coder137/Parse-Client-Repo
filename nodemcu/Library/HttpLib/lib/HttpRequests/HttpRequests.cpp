#include "HttpRequests.h"

#include <ESP8266HTTPClient.h>
#include <HttpConstants.h>

/**
 * ! Make sure you call FREE when you get the data back from this function
 * @param const char *url
 * @param const char *applicationId
 * @param int * status
 * @return char *
 * `status` returns the status of the GET request
 * char * returns the payload of the GET request
 */
char * parseServer_getRequest(const char *url, const char *applicationId, int * status)
{
    HTTPClient http;
    http.begin(url);
    http.addHeader(HTTPCONSTANT_PARSE_APPLICATION_ID, applicationId);
    http.addHeader(HTTPCONSTANT_CONTENT_TYPE, HTTPCONSTANT_APPLICATION_JSON);

    *status = http.GET();
    char * returnData = NULL;
    
    if (status > 0)
    {
        String payload = http.getString();
        returnData = (char *) malloc(sizeof(char)*(payload.length() + 1));
        strcpy(returnData, payload.c_str());;
    }
    
    http.end();
    return returnData;
}
