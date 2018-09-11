#include "HttpRequests.h"

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
    parseServer_addHeaderToClient(http, url, applicationId);

    *status = http.GET();
    
    return parseServer_returnData(http, status);
}

/**
 * ! Call FREE when data is returned
 */
char * parseServer_postRequest(const char *url, const char *applicationId, const char * data, int * status)
{
    HTTPClient http;
    parseServer_addHeaderToClient(http, url, applicationId);

    *status = http.POST(data);

    return parseServer_returnData(http, status);
}

/**
 * ! Call FREE when data is returned
 */
char * parseServer_putRequest(const char *url, const char *applicationId, const char * data, int * status)
{
    HTTPClient http;
    parseServer_addHeaderToClient(http, url, applicationId);

    *status = http.PUT(data);

    return parseServer_returnData(http, status);
}

void parseServer_addHeaderToClient(HTTPClient &http, const char *url, const char *applicationId)
{
    http.begin(url);
    http.addHeader(HTTPCONSTANT_PARSE_APPLICATION_ID, applicationId);
    http.addHeader(HTTPCONSTANT_CONTENT_TYPE, HTTPCONSTANT_APPLICATION_JSON);
}

char * parseServer_returnData(HTTPClient &http, int *status)
{
    char * returnData = NULL;

    if(status > 0)
    {
        String payload = http.getString();
        returnData = (char *) malloc(sizeof(char)*(payload.length() + 1));
        strcpy(returnData, payload.c_str());
    }

    http.end();
    return returnData;
}
