import paho.mqtt.client as mqtt
import time
import random

broker_ip = "192.168.1.30"  # <- Cambiar por la IPpasame el codigo bash de cada comando actual de la PC

client = mqtt.Client()
client.connect(broker_ip, 1883, keepalive=120)

while True:
    estado = random.choice(["Luz:ON", "Luz:OFF"])
    client.publish("sensor/luz", estado)
    print(f"Publicado: {estado}")
    time.sleep(1)
