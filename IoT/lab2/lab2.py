#! /usr/bin/env python3
import requests
import json
import time
import os

base_url = "https://stage.nthu-smart-farming.kits.tw/api/api/"

email = os.environ["EMAIL"]
password = os.environ["PASSWORD"]

group_id = "2fe29c0e-04f3-4536-864b-bd5abb890169"
sensor_type = "AIR_TEMPERATURE"
sensor_id = "6f403270-66e2-4341-86c7-f2a3ab812744"

from_time = str(int((time.time() - 1000) * 1000))
to_time = str(int(time.time() * 1000))

url = "sensors_in_timeinterval/AIR_TEMPERATURE//1635247976000/1635248991000"

# Login
r = requests.post(base_url + "account/login", data={
    "email": email,
    "password": password
})

if r.status_code != 200:
    print(r.status_code, "Error: ", r.text)
    exit(1)

token = r.json()["token"]

headers = {
  'Content-Type': 'application/json',
  'Authorization': f'Bearer {token}'
}

# Get data
r = requests.get(base_url + f"sensors_in_timeinterval/{sensor_type}/{sensor_id}/{from_time}/{to_time}", headers=headers)

if r.status_code != 200:
    print(r.status_code, "Error: ", r.text)
    exit(1)

for item in r.json()["Items"]:
    print(f"Value: { item['value'] }, Timestamp: { item['timestamp'] }")
