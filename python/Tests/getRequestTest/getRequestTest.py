# Create a configs.py file
import configs as user 
import requests
import json

"""
curl -X GET \
-H "X-Parse-Application-Id: {application_id}" \
-H "X-Parse-REST-API-Key: {rest_api_key}" \
https://parseapi.back4app.com/classes/hello
"""

classes = "classes/hello"

header = dict()
header["X-Parse-Application-Id"] = user.application_id
header["X-Parse-REST-API-Key"] = user.rest_api_key
header["Content-Type"] = "application/json"

# print("Hello requests")
r = requests.get(user.server_url+classes, headers=header)
print(r.status_code)

r.raise_for_status()

# print(r.content) # Byte format
# print()
# print(r.text) # UTF-8 decoded

# Use json to decode
pretty_json = json.dumps(json.loads(r.text), indent=4, sort_keys=True)
print(pretty_json)
