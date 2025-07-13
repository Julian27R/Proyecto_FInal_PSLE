import os
import time
import paho.mqtt.client as mqtt

# === CONFIGURACIÓN ===
device_path = "/sys/bus/iio/devices/iio:device0"
broker_ip = "10.94.230.220"  # IP de tu PC
topic = "sensor/mpu6050"
interval = 1  # segundos

# === FUNCIONES DE LECTURA ===
def read_value(filename):
    with open(os.path.join(device_path, filename), 'r') as f:
        return float(f.read().strip())

# === MQTT SETUP ===
client = mqtt.Client()
client.connect(broker_ip, 1883, keepalive=120)
client.loop_start()

# === ESCALA ===
accel_scale = read_value("in_accel_scale")
gyro_scale = read_value("in_anglvel_scale")

# === BUCLE DE PUBLICACIÓN ===
try:
    while True:
        ax = read_value("in_accel_x_raw") * accel_scale
        ay = read_value("in_accel_y_raw") * accel_scale
        az = read_value("in_accel_z_raw") * accel_scale

        gx = read_value("in_anglvel_x_raw") * gyro_scale
        gy = read_value("in_anglvel_y_raw") * gyro_scale
        gz = read_value("in_anglvel_z_raw") * gyro_scale

        data = {
            "accel": {"x": ax, "y": ay, "z": az},
            "gyro":  {"x": gx, "y": gy, "z": gz}
        }

        # Publica como texto 
        message = f"{data}"
        client.publish(topic, message)
        print(f"Publicado: {message}")

        time.sleep(interval)

except KeyboardInterrupt:
    client.loop_stop()
    print("Finalizado")
