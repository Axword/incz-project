import random
import requests
import time
from paho.mqtt import client as mqtt_client
import json


broker = 'eu1.cloud.thethings.network'
port = 1883
topic = "#"
# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 100)}'
username = 'supermarket-app@ttn'
password = 'NNSXS.GDNQOD2TJHR6F2JKER4ASZP4T5YLY3BDYBVSEAQ.HRNVMOCZTNSN3S77UXFQIAY3YMNOFB3ZTVXIK2SNFSBKUE5VFZ7A'
measurment = {}


def connect_mqtt() -> mqtt_client:
    try:
        def on_connect(client, userdata, flags, rc):
            if rc == 0:
                client.connected_flag = True
                print("Connected to MQTT Broker!")
            else:
                print("Failed to connect, return code %d\n", rc)

        client = mqtt_client.Client(client_id)
        client.username_pw_set(username, password)
        client.on_connect = on_connect
        client.connect(broker, port)
    except Exception as e:
        time.sleep(5)
        print('retry')
        connect_mqtt()
    return client


def subscribe(client: mqtt_client):
    keys= [
        'measure_acceleration_total_vector',
        'measure_angle_pitch',
        'measure_acceleration_pitch',
        'measure_angle_yaw',
        'measure_acceleration_yaw',
        'measure_reciver_one_rx',
        'measure_reciver_two_rx',
    ]
    def on_message(client, userdata, msg):
        try:
            data = json.loads(msg.payload)
            measurments = data['uplink_message']['decoded_payload']
            # measurment = {  'measure_acceleration_total_vector': msg.payload.get('measure_acceleration_total_vector'),
            #                 'measure_angle_pitch': msg.payload.get('measure_angle_pitch'),
            #                 'measure_acceleration_pitch': msg.payload.get('measure_acceleration_pitch'),
            #                 'measure_angle_yaw': msg.payload.get('measure_angle_yaw'),
            #                 'measure_acceleration_yaw':  msg.payload.get('measure_acceleration_yaw'),
            #                 'measure_reciver_one_rx': msg.payload.get('measure_reciver_one_rx'),
            #                 'measure_reciver_two_rx': msg.payload.get('measure_reciver_two_rx'),
            #                 'cart_id': 1
            #                 }
            for key, value in measurments.items():
                dict[key] = value
            print(dict)
            if len(dict.keys()) == 8:
                requests.post("localhost:8000/measurment/", data=dict)
        except Exception as e:
            print("Error while serializing message")
            pass
    client.subscribe(topic)
    client.on_message = on_message


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    run()