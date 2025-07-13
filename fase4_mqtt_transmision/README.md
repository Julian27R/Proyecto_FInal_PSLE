
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

## Paso a paso: Lectura desde la interfaz sysfs o IIO (Industrial I/O)

### 1. Verificar si el sensor fue detectado por el kernel

```bash
ls /sys/bus/iio/devices/
```

### 2. Navegar al dispositivo

```bash
cd /sys/bus/iio/devices/iio:device0/
ls
```

Verás archivos como:

- `in_accel_{x,y,z}_raw`
- `in_anglvel_{x,y,z}_raw`
- `in_accel_scale`, `in_anglvel_scale`

### 3. Leer valores crudos del sensor

```bash
cat in_accel_x_raw
cat in_anglvel_x_raw
```

### 4. Convertir valores crudos a unidades reales

Usar los factores de escala proporcionados por el kernel:

```bash
cat in_accel_scale      # → factor para convertir a m/s²
cat in_anglvel_scale    # → factor para convertir a °/s
```

### 5. Script de monitoreo en tiempo real

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

Este script convierte en tiempo real los datos del sensor a unidades físicas comprensibles.
