
# Fase 4: Lectura de datos del sensor en Lichee RV Dock

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

## Pasos para la Lectura de Datos del MPU6050 desde la Lichee RV Dock

### 1. Requisitos Previos

- Sensor MPU6050 habilitado en `/sys/bus/iio/devices/iio:device*`
- Conexión I2C activa y funcionando
- Python 3

---

## 2. Script de Lectura Continua

```python
import os
import time

# Ruta del dispositivo
device_path = "/sys/bus/iio/devices/iio:device0"

# Leer valor de archivo
def read_value(filename):
    with open(os.path.join(device_path, filename), 'r') as f:
        return float(f.read().strip())

# Obtener escalas
accel_scale = read_value("in_accel_scale")
gyro_scale = read_value("in_anglvel_scale")

# Intervalo de muestreo
interval = 1  # segundos

# Bucle principal
try:
    while True:
        # Acelerómetro
        ax = read_value("in_accel_x_raw") * accel_scale
        ay = read_value("in_accel_y_raw") * accel_scale
        az = read_value("in_accel_z_raw") * accel_scale

        # Giroscopio
        gx = read_value("in_anglvel_x_raw") * gyro_scale
        gy = read_value("in_anglvel_y_raw") * gyro_scale
        gz = read_value("in_anglvel_z_raw") * gyro_scale

        # Mostrar por pantalla
        print(f"Accel: x={ax:.2f}, y={ay:.2f}, z={az:.2f} | Gyro: x={gx:.2f}, y={gy:.2f}, z={gz:.2f}")
        time.sleep(interval)
except KeyboardInterrupt:
    print("Lectura finalizada.")
```

---

Este script permite leer en tiempo real los datos del sensor y verificar el correcto funcionamiento del MPU6050 integrado con el driver del kernel y el sistema `/sys/bus/iio`.
