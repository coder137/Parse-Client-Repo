# RegisterNodemcuClient

## AIM

To register a nodemcuClient to a parseServer and subscribe to itself

## STEPS

1. Add itself to the database
    1. get request to find itself
    2. `if not exists` -> post
    3. `if exists` -> continue
2. Subscribe to itself using `mac_addr`
3. Attach suitable event handlers to deal with events

> Go into details

## Modules Used

Check `lib/readme.txt` for entire dependencies

### Parsing JSON
- cJSON

### Server Credentials and passwords
- configs
    - All Server Config details
- `password.h` -> HIDDEN
    - contains `ssid` and `password` as `const char`
  
### DatabaseSchemas
- DatabaseObjectSchema
    - Create the POST, GET, PUT, DELETE Requests with CJSON

### Http
- HttpConstants
    - Various `Parse-Server` Header constants required
- HttpRequests
    - `Parse-Server` GET, POST, PUT and DELETE requests

### LiveQuery (Websockets)
- LiveQueryConstants
    - `Parse-Server` constants used
- LiveQueryObject
    - `connect` and `subscribe` tokens created 
    - LOW LEVEL
- LiveQueryUser
    - Built on `LiveQueryObject`
    - `connectToServer` and `subscribeToServer`

## Database Schema

``` json
{
    "mac": "<mac_addr>",
    "device_name": "<user_name>",
    "pin1": {
        "pin_name": "<pin_name>",
        "type": "control/switch",
        "value": 128-0/1-0
    },
    "pin2": {...},
    "pin3": {...},
    "pin4": {...}
}
```
