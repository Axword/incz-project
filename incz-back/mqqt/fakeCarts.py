import random
import requests
import time

def run():
    while(True):
        id= random.randint(2,5)
        measurment = {  'measure_acceleration_total_vector': round(random.uniform(0, 90), 2),
                        'measure_angle_pitch': round(random.uniform(0, 90), 2),
                        'measure_acceleration_pitch': round(random.uniform(0, 90), 2),
                        'measure_angle_yaw': round(random.uniform(0, 90), 2),
                        'measure_acceleration_yaw':  round(random.uniform(0, 90), 2),
                        'measure_reciver_one_rx': round(random.uniform(0, 90), 2),
                        'measure_reciver_two_rx': round(random.uniform(0, 90), 2),
                        'cart_id': id
                        }
        try:
            r = requests.post('http://localhost:8000/measurment/', data=measurment)
            print(r.text)
        except Exception:
            pass
        time.sleep(40.0)
    


if __name__ == '__main__':
    run()