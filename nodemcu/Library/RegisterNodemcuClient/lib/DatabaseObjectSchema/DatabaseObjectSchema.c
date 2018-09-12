#include "DatabaseObjectSchema.h"

#include <LiveQueryObject.h>

char * createInitialGetRequestUrl(const char * mac_id)
{
    cJSON * getObject = cJSON_CreateObject();
    cJSON_AddStringToObject(getObject, MAC, mac_id);

    uint32_t final_length = strlen( cJSON_Print(getObject) ) +
                            SERVER_IP_ADD_LENGTH +
                            SERVER_DEVICES_CLASS_LENGTH +
                            SERVER_QUERY_LENGTH;
    
    // Serial.printf("Length: %" PRIu32 "\n", final_length);
    char * returnData = (char *) malloc(sizeof(char) * final_length);    

    strcat(returnData, serverIpAddress);
    strcat(returnData, serverDevicesClass);
    strcat(returnData, serverQuery);
    strcat(returnData, cJSON_PrintUnformatted(getObject)); // IMP

    cJSON_Delete(getObject); // ! Delete the above JSON object
    return returnData;
}

void createInitialDatabaseSchema(cJSON * createSchemaObject, const char * mac_id)
{
    cJSON_AddStringToObject(createSchemaObject, MAC, mac_id);
    cJSON_AddStringToObject(createSchemaObject, DEVICE_NAME, ""); // Give a dummy name here

    // NOTE, Create Schemas with default data
    _createPinSchema(createSchemaObject, PIN1, NULL, NULL, 128);
    _createPinSchema(createSchemaObject, PIN2, NULL, NULL, 128);
    _createPinSchema(createSchemaObject, PIN3, NULL, NULL, 128);
    _createPinSchema(createSchemaObject, PIN4, NULL, NULL, 128);
}

void _createPinObjectSchema(cJSON * createPinObject, const char * pin_name, const char * type, int value)
{
    cJSON_AddStringToObject(createPinObject, PIN_NAME, pin_name);
    cJSON_AddStringToObject(createPinObject, TYPE, type);
    cJSON_AddNumberToObject(createPinObject, VALUE, value);
}

void _createPinSchema(cJSON * createSchemaObject,const char *pin, const char * pin_name, const char *type, int value)
{
    cJSON * createPin1Object = cJSON_CreateObject();
    _createPinObjectSchema(createPin1Object, pin_name, type, value);
    cJSON_AddItemToObject(createSchemaObject, pin, createPin1Object);
}