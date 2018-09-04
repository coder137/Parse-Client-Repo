Table of Contents

- [Getting Started](#getting-started)
- [Library](#library)
    - [DONE](#done)
- [Tests](#tests)
    - [DONE](#done)
    - [TODO](#todo)
- [For Local Tests](#for-local-tests)
    - [DONE](#done)
- [Important](#important)

# Getting Started

**Setup your Local Parse-Server environment**

- Run LocalTests

**Setup your Back4App environment**

- Run Tests

# Library

Each Library has its own `README.md` file

Client Libraries can be modified for both LocalTests as well as ServerTests

## DONE

- LiveQueryLib

# Tests

1. Create a `configs.py` -> keys given in `config.py`
2. Run the python script by modifying your equivalent `classes` string
3. Run code to get output `pipenv run python ${file}` -> .vscode tasks.json

## DONE

- getRequestTest
- postRequestTest

## TODO

- putRequestTest
- deleteRequestTest

> ADD MORE

# For Local Tests

`MONGODB_PURGE=false`

Run the `windows_start_mongodbrunner.bat` with admin privileges

## DONE

- liveQueryTest
- postRequestTest
- getRequestTest
- putRequestTest
- deleteRequestTest

# Important

- LiveQuery using Websockets
- Push Notification with Android
