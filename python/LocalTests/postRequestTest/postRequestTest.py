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

# ? url
url = "http://localhost:1337/parse/"
classes = "classes/Random"

# ? header
header = dict()
print(classes)
header[h.x_parse_application_id] = "myAppId"
# header[h.x_parse_rest_api_key] = user.rest_api_key
header[h.content_type] = h.application_json # ! Note this field is VERY important
print(header)

# ? data
payload = {"Name": "Test", "Score": 5000, "Boolean": False}
payload = json.dumps(payload)

print(payload)
print(type(payload))

# ? Send request
r = requests.post(url+classes, headers=header, data=payload)
print(r.status_code)

r.raise_for_status()

pretty_json = json.dumps(json.loads(r.text), indent=4, sort_keys=True)
print(pretty_json)
