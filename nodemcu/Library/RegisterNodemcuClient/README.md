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
