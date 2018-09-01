# ! Not used
## https://websockets.readthedocs.io/en/stable/intro.html

# USED
## https://pypi.org/project/websocket-client/

# USED
## https://github.com/parse-community/parse-server/wiki/Parse-LiveQuery-Protocol-Specification

import websocket
import json

# user defined libs
import liveQueryGeneric as lg
import liveQueryUser as lu
import params

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
    # print(type(connection_data))

    lg.onMessage_callback(ws, connection_data, params.CONNECT_DONE, lu.connect_action, 
                        requestId=1, className="Test", where={"Name": "Test"}) 
    
    lg.onMessage_callback(ws, connection_data, params.SUBSCRIBE_DONE, lu.subscribe_action)

    lg.onMessage_callback(ws, connection_data, params.CREATE, lu.create_action)

    lg.onMessage_callback(ws, connection_data, params.ENTER, lu.enter_action)

    lg.onMessage_callback(ws, connection_data, params.UPDATE, lu.update_action)

    lg.onMessage_callback(ws, connection_data, params.LEAVE, lu.leave_action)

    lg.onMessage_callback(ws, connection_data, params.DELETE, lu.delete_action)

def on_open(ws):
    print("opened")
    
    # TODO, Make applicationId dynamic
    json_data = json.dumps({
        params.OP: params.TO_CONNECT,
        "applicationId": "myAppId"
    })
    # print(json_data)
    ws.send(json_data)

if __name__ == "__main__":
    # websocket.enableTrace(True) # TODO, This is not needed comment it out
    ws = websocket.WebSocketApp("ws://localhost:1337/",
                              on_message = on_message,
                              on_error= lg.on_error,
                              on_close = lg.on_close)
    ws.on_open = on_open
    ws.run_forever(ping_timeout=1) # ! Make sure you set the ping_timeout, else ERROR
