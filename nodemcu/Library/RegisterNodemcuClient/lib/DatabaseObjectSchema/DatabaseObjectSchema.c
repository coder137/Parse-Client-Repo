#include "DatabaseObjectSchema.h"

#include <LiveQueryObject.h>

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