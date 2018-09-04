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
# ? Server url data
url = "http://192.168.29.186:1337/parse/"
classes = "classes/Random"

# ? headers
header = dict()
print(classes)
header[h.x_parse_application_id] = "myAppId"
# header[h.x_parse_rest_api_key] = user.rest_api_key
header[h.content_type] = h.application_json
print(header)

# ? data
payload = {"Name":"Boi", "Score":50000, "Boolean": False}
payload = json.dumps(payload)

# ? debug
print(payload)
print(type(payload))
# exit(0)

# ? Send request
r = requests.post(url+classes, headers=header, data=payload)
print(r.status_code)

r.raise_for_status()

pretty_json = json.dumps(json.loads(r.text), indent=4, sort_keys=True)
print(pretty_json)
