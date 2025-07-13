
# Fase 3: Lectura y Transmisión de Datos del Sensor MPU6050 en Lichee RV Dock

Esta fase del proyecto documenta el proceso de **lectura de datos desde el sensor MPU6050** utilizando la interfaz IIO en Lichee RV Dock, así como la **transmisión de datos vía MQTT** hacia un PC.

---

## 🧩 Parte 1: Lectura de datos en crudo (IIO)

1. **Verificar dispositivo IIO**  
   ```bash
   ls /sys/bus/iio/devices
   ```

2. **Listar archivos disponibles del sensor**  
   ```bash
   cd /sys/bus/iio/devices/iio:device0
   ls
   ```

3. **Leer valor en crudo de aceleración en X**  
   ```bash
   cat in_accel_x_raw
   ```

---

## 📏 Parte 2: Conversión a Unidades Reales

El MPU6050 entrega datos crudos que deben ser multiplicados por un **factor de escala** para obtener unidades físicas:

- Acelerómetro: `in_accel_scale` → convierte a m/s²
- Giroscopio: `in_anglvel_scale` → convierte a °/s

### Script de lectura y conversión

```bash
#!/bin/bash

cd /sys/bus/iio/devices/iio:device0 || exit

accel_scale=$(cat in_accel_scale)
gyro_scale=$(cat in_anglvel_scale)

while true; do
  ax=$(cat in_accel_x_raw)
  ay=$(cat in_accel_y_raw)
  az=$(cat in_accel_z_raw)

  gx=$(cat in_anglvel_x_raw)
  gy=$(cat in_anglvel_y_raw)
  gz=$(cat in_anglvel_z_raw)

  ax_val=$(echo "$ax * $accel_scale" | bc -l)
  ay_val=$(echo "$ay * $accel_scale" | bc -l)
  az_val=$(echo "$az * $accel_scale" | bc -l)

  gx_val=$(echo "$gx * $gyro_scale" | bc -l)
  gy_val=$(echo "$gy * $gyro_scale" | bc -l)
  gz_val=$(echo "$gz * $gyro_scale" | bc -l)

  echo "Accel [m/s²]  X:$ax_val  Y:$ay_val  Z:$az_val"
  echo "Gyro  [°/s]   X:$gx_val  Y:$gy_val  Z:$gz_val"
  echo ""
  sleep 0.5
done
```

---

## 📡 Parte 3: Transmisión de Datos vía MQTT

### A. Configuración del Cliente (Lichee)

1. **Instalar dependencias**
   ```bash
   sudo apt update
   sudo apt install python3-pip python3-venv -y
   ```

2. **Crear entorno virtual e instalar Paho-MQTT**
   ```bash
   python3 -m venv mqtt_env
   source mqtt_env/bin/activate
   pip install paho-mqtt
   ```

3. **Crear script publicador**
   ```bash
   nano lichee_sensor_mqtt.py
   ```

```python
import paho.mqtt.client as mqtt
import time
import random

broker_ip = "10.233.238.220"  # Cambiar por IP del PC (broker)

client = mqtt.Client()
client.connect(broker_ip, 1883, keepalive=120)

while True:
    estado = random.choice(["Luz:ON", "Luz:OFF"])
    client.publish("sensor/luz", estado)
    print(f"Publicado: {estado}")
    time.sleep(1)
```

---

### B. Configuración del Broker (PC)

1. **Instalar Mosquitto**
   ```bash
   sudo apt update
   sudo apt install mosquitto mosquitto-clients -y
   ```

2. **Permitir conexiones externas**
   ```bash
   sudo nano /etc/mosquitto/mosquitto.conf
   ```

3. **Reiniciar servicio**
   ```bash
   sudo systemctl restart mosquitto
   ```

4. **Verificar puerto 1883**
   ```bash
   sudo ss -tuln | grep 1883
   ```

---

### C. Verificación del Funcionamiento

En la PC, abrir una terminal y ejecutar:

```bash
mosquitto_sub -h localhost -t sensor/luz
```

---

## 📌 Resumen del Sensor MPU6050

- **Acelerómetro**: mide aceleraciones lineales en tres ejes (X, Y, Z).
- **Giroscopio**: mide velocidades angulares en °/s en tres ejes (X, Y, Z).
