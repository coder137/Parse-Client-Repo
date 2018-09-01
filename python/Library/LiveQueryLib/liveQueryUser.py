import params
import json

# TODO, Make the subscribe json into its own params object
def connect_action(ws, connection_data, **kwargs):
    # TODO, Add this to logging
    print(params.CONNECT_DONE)

    # TODO, Add a test here to check if all the kwargs are available

    # TODO, Add all these keys to param file
    subscribe_json = json.dumps({
        params.OP: params.TO_SUBSCRIBE,
        "requestId": kwargs["requestId"],
        "query": {
            "className": kwargs["className"],
            "where": kwargs["where"]
        }
    })
    ws.send(subscribe_json)

def subscribe_action(ws, connection_data, **kwargs):
    print(params.SUBSCRIBE_DONE)
    pretty_json = json.dumps(connection_data, indent=4, sort_keys=True)
    print(pretty_json)
    # ? Do other things here

def create_action(ws, connection_data, **kwargs):
    print(params.CREATE)
    pretty_json = json.dumps(connection_data, indent=4, sort_keys=True)
    print(pretty_json)
    # ? Do other things here
# {
#     "clientId": "<client_id>",
#     "object": {
#         "Name": "Test",
#         "__type": "Object",
#         "className": "Test",
#         "createdAt": "2018-09-01T08:44:26.936Z",
#         "objectId": "S9ZA4CWyST",
#         "updatedAt": "2018-09-01T08:44:26.936Z"
#     },
#     "op": "create",
#     "requestId": 1
# }

# ENTER
def enter_action(ws, connection_data, **kwargs):
    print(params.ENTER)
    pretty_json = json.dumps(connection_data, indent=4, sort_keys=True)
    print(pretty_json)

# UPDATE
def update_action(ws, connection_data, **kwargs):
    print(params.UPDATE)
    pretty_json = json.dumps(connection_data, indent=4, sort_keys=True)
    print(pretty_json)

# LEAVE
def leave_action(ws, connection_data, **kwargs):
    print(params.LEAVE)
    pretty_json = json.dumps(connection_data, indent=4, sort_keys=True)
    print(pretty_json)


# DELETE
def delete_action(ws, connection_data, **kwargs):
    print(params.DELETE)
    pretty_json = json.dumps(connection_data, indent=4, sort_keys=True)
    print(pretty_json)
