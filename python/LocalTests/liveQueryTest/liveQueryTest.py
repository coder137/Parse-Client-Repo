# ! Not used
## https://websockets.readthedocs.io/en/stable/intro.html

# USED
## https://pypi.org/project/websocket-client/

# USED
## https://github.com/parse-community/parse-server/wiki/Parse-LiveQuery-Protocol-Specification

import websocket
import json

"""
CREATE
ENTER
UPDATE
LEAVE
DELETE
"""

def on_message(ws, message):
    print("message: ", str(message))
    connection_data = json.loads(message)

    if connection_data["op"] == "connected":
        print("CONNECTED")
        # ? We get {clientId}

        # Now subscribe to whatever you want
        subscribe_json = json.dumps({
            "op": "subscribe",
            "requestId": 1,
            "query": {
                "className": "Test",
                "where": {"Name": "Test"}
            }
        })
        ws.send(subscribe_json)
    
    if connection_data["op"] == "subscribed":
        print("SUBSCRIBED")
        # ? We get {clientId, requestId}

    if connection_data["op"] == "create":
        print("CREATED")
        pass
    
    if connection_data["op"] == "enter":
        print("ENTERED")
        pass
    
    if connection_data["op"] == "update":
        print("UPDATED")
        pass

    if connection_data["op"] == "leave":
        print("LEFT")
        pass

    if connection_data["op"] == "delete":
        print("DELETED")
        pass


def on_error(ws, error):
    print("error: ", str(error))

def on_close(ws):
    print("### closed ###")

def on_open(ws):
    print("OPENED")
    json_data = json.dumps({
        "op": "connect",
        "applicationId": "myAppId"
    })
    print(json_data)
    ws.send(json_data)

if __name__ == "__main__":
    websocket.enableTrace(True) # TODO, This is not needed comment it out
    ws = websocket.WebSocketApp("ws://localhost:1337/",
                              on_message = on_message,
                              on_error= on_error,
                              on_close = on_close)
    ws.on_open = on_open
    ws.run_forever(ping_timeout=1) # ! Make sure you set the ping_timeout, else ERROR
