#include "LiveQueryObject.h"

/**
 * @param const char * appIdPass
 * @param cJSON *subscribeObject
 * @return uint8_t
 * created = 0 (fail)
 * created = 1 (success)
 */
// TODO, Make the fields dynamic
uint8_t createConnectToken(const char * appIdPass, cJSON *connectObject)
{
    uint8_t created;
    created = deleteJSONObject_IfNull( cJSON_AddStringToObject(connectObject, "op", "connect") );
    created &= deleteJSONObject_IfNull( cJSON_AddStringToObject(connectObject, "applicationId", appIdPass) );

    return created;
}

//TODO, Test this function
// TODO, Make the fields dynamic
uint8_t createSubscribeToken(const char * className, cJSON *identifier_object, cJSON *subscribeObject)
{
    uint8_t created;
    created = deleteJSONObject_IfNull( cJSON_AddStringToObject(subscribeObject, "op", "subscribe") );
    created &= deleteJSONObject_IfNull( cJSON_AddNumberToObject(subscribeObject, "requestId", 1) );

    cJSON * queryObject = cJSON_CreateObject();
    created &= deleteJSONObject_IfNull( cJSON_AddStringToObject(queryObject, "className", className) );
    cJSON_AddItemToObject(queryObject, "where", identifier_object); 

    cJSON_AddItemToObject(subscribeObject, "query", queryObject);

    return created;
}

/**
 * @param cJSON *object
 * @return uint8_t
 * if NULL -> delete -> return 0
 * else -> return 1
 */
uint8_t deleteJSONObject_IfNull(cJSON *object)
{
    if(object == NULL)
    {
        cJSON_Delete(object);
        return 0; //FAIL
    }

    return 1; //SUCCESS
}