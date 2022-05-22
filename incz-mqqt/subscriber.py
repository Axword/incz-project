import random
import http.client
import json

from paho.mqtt import client as mqtt_client




broker = 'eu1.cloud.thethings.network'
port = 1883
topic = "#"
# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 100)}'
username = 'incz-shop@ttn'
password = 'NNSXS.UTTVC23CGHKJUCZKHOQJCVIIGTPOZS23WLZXPYA.WNTKJKJ2UICDQUU24UNJAO4N743Y2CSG6ZK7HOYIQTXKQKCKGSMA'


def connect_mqtt() -> mqtt_client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        conn = http.client.HTTPConnection('localhost',80)
        headers = {'Content-type': 'application/json'}
        measurment ={'timestamp': msg.payload.decode().timestamp, 
                       'measurment1': msg.payload.decode().measurment1,
                       'measurment2': msg.payload.decode().measurment2,
                        'measurment3': msg.payload.decode().measurment3,
                        'cart_Id': "1"}
        json_data =json.dumps(measurment)
        conn.request("POST", "measurments", json_data)
        response =conn.getresponse()
        print(response.status, response.reason)
        conn.close


    client.subscribe(topic)
    client.on_message = on_message


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    run()