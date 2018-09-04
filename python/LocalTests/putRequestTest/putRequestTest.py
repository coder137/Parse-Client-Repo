import httpconstants as h

import requests
import json

"""
curl -X PUT \
-H "X-Parse-Application-Id: myAppId" \
-H "X-Parse-REST-API-Key: undefined" \
--data-urlencode "{\"Name\":\"Niket\"}" \
http://192.168.29.186:1337/parse/classes/Random/4picLkjqDj
"""

# ? url
url = "http://localhost:1337/parse/"
classes = "classes/Random/4picLkjqDj"

# ? header
header = dict()
header[h.x_parse_application_id] = "myAppId"
# header[h.x_parse_rest_api_key] = user.rest_api_key
header[h.content_type] = h.application_json # ! Note this field is VERY important
print(header)

# ? data to change
payload = {"Score": 123, "Boolean": False}
payload = json.dumps(payload)

print(payload)
print(type(payload))

# ? Send request
r = requests.put(url+classes, headers=header, data=payload)
print(r.status_code)

r.raise_for_status()

pretty_json = json.dumps(json.loads(r.text), indent=4, sort_keys=True)
print(pretty_json)
