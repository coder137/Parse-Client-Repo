import json
import params

def onMessage_callback(ws, connection_data: dict, connection_type: str, action, *args, **kwargs):
    if connection_data[params.OP] == connection_type:
        action(ws, connection_data, **kwargs)

def on_error(ws, error):
    print("error: ", str(error))

def on_close(ws):
    print("### closed ###")
