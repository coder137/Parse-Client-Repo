#ifndef DatabaseObjectSchema_H
#define DatabaseObjectSchema_H

#include <cJSON.h>
#include <inttypes.h>

#include <configs.h>

#ifdef __cplusplus
extern "C"
{
#endif

// ? Const char fields (Database Schema)
const char MAC[] = "mac";
const char DEVICE_NAME[] = "device_name";
const char PIN1[] = "pin1";
const char PIN2[] = "pin2";
const char PIN3[] = "pin3";
const char PIN4[] = "pin4";

const char PIN_NAME[] = "pin_name";
const char TYPE[] = "type";
const char VALUE[] = "value";

// ? Functions
char * createInitialGetRequestUrl(const char * mac_id);
void createInitialDatabaseSchema(cJSON * createSchemaObject, const char * mac_id);

// ? Helper functions
void _createPinObjectSchema(cJSON * createPinObject, const char * pin_name, const char * type, int value);
void _createPinSchema(cJSON * createSchemaObject,const char *pin, const char * pin_name, const char *type, int value);

#ifdef __cplusplus
}
#endif

#endif