#ifndef LiveQueryObject_H
#define LiveQueryObject_H

#include <inttypes.h>
#include <cJSON.h>
#include <LiveQueryConstants.h>

#ifdef __cplusplus
extern "C"
{
#endif

uint8_t createConnectToken(const char * appIdPass, cJSON *subscribeObject);
uint8_t createSubscribeToken(const char * className, const char *key, const char *value, cJSON *subscribeObject);

uint8_t deleteJSONObject_IfNull(cJSON *object);

#ifdef __cplusplus
}
#endif

#endif
