# LiveQueryLib

A functional approach to creating a LiveQueryLib.

**AIM** is to create a working liveQuery Websocket interface to the Parse Server in Python

## Working / Docs

The `liveQueryLib.py` file is the main code that runs

`liveQueryGeneric.py` contains the generic functions that do not need to be modified

`liveQueryUser.py` contains the user defined functions that can undergo moderate amount of change

`params.py` contains all the variables that will be used by the 3 files above

## TODO

- Add Logging
- Address TODO issues
- Add `super` functions i.e `default` functionality for the `liveQueryUser.py` functions

## Tests

- [x] Tested locally
- [ ] Tested with Back4App

# FAQ

## Writing this code in classes would be much simpler and probably more efficient. Why are you not using classes? 

Apart from the main `websocket.WebSocketApp()` class I have avoided using classes.

Usage of functions in this case would help port the code to languages such as `C` for low level interfacing. In such cases visualising a functional approach in Python is beneficial

## Do you plan to write this libary using classes?

My first priority is to get a working *functional* library in python.

I then aim to write this websocket library in C for the ESP8266/ESP32 devices. 

Only then would I write this using classes
