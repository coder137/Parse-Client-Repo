import httpconstants as h

import requests
import json

"""
curl -X DELETE \
  -H "X-Parse-Application-Id: ${APPLICATION_ID}" \
  -H "X-Parse-REST-API-Key: ${REST_API_KEY}" \
  https://YOUR.PARSE-SERVER.HERE/parse/classes/Random/4picLkjqDj
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

# ? Send request
r = requests.delete(url+classes, headers=header)
print(r.status_code)

r.raise_for_status()

pretty_json = json.dumps(json.loads(r.text), indent=4, sort_keys=True)
print(pretty_json)
