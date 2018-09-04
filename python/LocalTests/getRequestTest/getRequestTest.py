import httpconstants as h

import requests
import json

"""
curl -X GET \
-H "X-Parse-Application-Id: {application_id}" \
-H "X-Parse-REST-API-Key: {rest_api_key}" \
https://parseapi.back4app.com/classes/hello
"""

# ? url
url = "http://localhost:1337/parse/"
classes = "classes/Random"

# ? header
header = dict()
header[h.x_parse_application_id] = "myAppId"
# header["X-Parse-REST-API-Key"] = user.rest_api_key
header[h.content_type] = h.application_json

# ? Send request
r = requests.get(url+classes, headers=header)
print(r.status_code)

r.raise_for_status()

# Use json to decode
pretty_json = json.dumps(json.loads(r.text), indent=4, sort_keys=True)
print(pretty_json)
