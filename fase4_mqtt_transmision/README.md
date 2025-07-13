
# Fase 4: Lectura de datos del sensor en Lichee RV Dock

Esta fase del proyecto se centra en la lectura de datos del sensor MPU6050 desde la Lichee RV Dock, utilizando el sistema de archivos `sysfs` en `/sys/bus/iio`. El objetivo es obtener valores de aceleración y velocidad angular de forma periódica, aplicando los factores de escala correctos, y prepararlos para su posterior transmisión.

---


## Sensor utilizado: MPU6050

El **MPU6050** es un sensor inercial que integra un **acelerómetro triaxial** y un **giroscopio triaxial** en un solo chip.

<img width="470" height="411" alt="image" src="https://github.com/user-attachments/assets/3c29f155-7355-4b8b-b1a0-80bf58265590" />


### 📌 Acelerómetro: mide aceleraciones lineales en tres ejes (en m/s²)

- **Eje X (`accel['x']`)**: eje longitudinal horizontal del plano del sensor.
- **Eje Y (`accel['y']`)**: eje transversal horizontal del plano del sensor.
- **Eje Z (`accel['z']`)**: eje perpendicular al plano del sensor (vertical).

### 📌 Giroscopio: mide velocidades angulares de rotación alrededor de los mismos ejes (en °/s)

- **Eje X (`gyro['x']`)**: rotación alrededor del eje X físico del sensor.
- **Eje Y (`gyro['y']`)**: rotación alrededor del eje Y físico del sensor.
- **Eje Z (`gyro['z']`)**: rotación perpendicular al plano del sensor.

---

## Script Python para Lectura del Sensor

El siguiente script realiza la lectura del sensor desde la ruta `/sys/bus/iio/devices/iio:device0`, aplica los factores de escala y publica los valores en consola.

```python
import os
import time
import paho.mqtt.client as mqtt

# === CONFIGURACIÓN ===
device_path = "/sys/bus/iio/devices/iio:device0"
broker_ip = "10.164.246.220"  # IP de tu PC
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
gyro_scale  = read_value("in_anglvel_scale")

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
            "gyro" : {"x": gx, "y": gy, "z": gz}
        }

        message = f"{data}"
        client.publish(topic, message)
        print(f"Publicado: {message}")

        time.sleep(interval)

except KeyboardInterrupt:
    client.loop_stop()
    print("Finalizado")
```

---

## Requisitos

- La Lichee RV Dock debe tener el sensor conectado y funcionando vía I2C.
- Python 3 instalado.
- Entorno virtual `mqtt_env` con `paho-mqtt` instalado.
- El broker MQTT debe estar corriendo en el PC (por ejemplo, Mosquitto).

---

## Ejecución del Script

```bash
source mqtt_env/bin/activate
python3 mpu6050_mqtt.py
```

---

Este script garantiza la lectura precisa del sensor utilizando el sistema de archivos del kernel, escalando adecuadamente las mediciones crudas y transmitiendo los datos para su posterior integración con ROS2.
