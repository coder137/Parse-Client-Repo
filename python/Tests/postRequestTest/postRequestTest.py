import configs as user
import httpconstants as h

import requests
import json

"""
curl -X POST \
-H "X-Parse-Application-Id: {application_id}" \
-H "X-Parse-REST-API-Key: {rest_api_key}" \
--data-urlencode "{\"row1\":\"row1data\", \"row2\":\"row2data\"}" \
https://parseapi.back4app.com/classes/new
"""

classes = "classes/new"

header = dict()
print(classes)
header[h.x_parse_application_id] = user.application_id
header[h.x_parse_rest_api_key] = user.rest_api_key

payload = {"row1": "row1data", "row2": "row2data"}
print(header)
print(payload)

r = requests.post(user.server_url+classes, headers=header, data=payload)
print(r.status_code)

r.raise_for_status()

pretty_json = json.dumps(json.loads(r.text), indent=4, sort_keys=True)
print(pretty_json)