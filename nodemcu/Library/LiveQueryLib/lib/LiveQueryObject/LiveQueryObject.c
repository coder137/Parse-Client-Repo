#include "LiveQueryObject.h"

/**
 * @param const char * appIdPass
 * @param cJSON *subscribeObject
 * @return uint8_t
 * created = 0 (fail)
 * created = 1 (success)
 * {
 *      "op": "connect",
 *      "applicationId": {applicationId}
 * }
 */
// TODO, Make the fields dynamic
uint8_t createConnectToken(const char * appIdPass, cJSON *connectObject)
{
    uint8_t created;
    created = deleteJSONObject_IfNull( cJSON_AddStringToObject(connectObject, LIVEQUERY_OP, LIVEQUERY_TO_CONNECT) );
    created &= deleteJSONObject_IfNull( cJSON_AddStringToObject(connectObject, LIVEQUERY_APPLICATION_ID, appIdPass) );

    return created;
}

/**
 * @param const char *classname
 * @param const char *key
 * @param const char *value
 * @param cJSON *subscribeObject
 * @return uint8_t
 * created = 0 (fail)
 * created = 1 (success)
 * {
 *      "op": "subscribe",
 *      "requestId": 1,
 *      "query": {
 *          "className": "Player",
 *          "where": {"name", "test"},
 *          "fields": ["name"] //optional
 *      },
 *      "sessionToken": ""
 * }
 */
// DONE, Make the fields dynamic
// TODO, Make requestID dynamic
uint8_t createSubscribeToken(const char * className, const char *key, const char *value, cJSON *subscribeObject)
{
    uint8_t created;
    created = deleteJSONObject_IfNull( cJSON_AddStringToObject(subscribeObject, LIVEQUERY_OP, LIVEQUERY_TO_SUBSCRIBE) );
    created &= deleteJSONObject_IfNull( cJSON_AddNumberToObject(subscribeObject, LIVEQUERY_REQUEST_ID, 1) );

    cJSON * queryObject = cJSON_CreateObject();
    created &= deleteJSONObject_IfNull( cJSON_AddStringToObject(queryObject, LIVEQUERY_CLASSNAME, className) );

    cJSON * identifier_object = cJSON_CreateObject();
    created &= deleteJSONObject_IfNull( cJSON_AddStringToObject(identifier_object, key, value) );    
    cJSON_AddItemToObject(queryObject, LIVEQUERY_WHERE, identifier_object); 

    cJSON_AddItemToObject(subscribeObject, LIVEQUERY_QUERY, queryObject);

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
