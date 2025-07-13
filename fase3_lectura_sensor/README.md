
# Fase 3: Lectura de datos del sensor en Lichee RV Dock

Con el driver en espacio de núcleo ya activado (Fase 1) y el bus I2C2 habilitado (Fase 2), ahora es posible interactuar con el sensor MPU6050 usando la interfaz **IIO (Industrial I/O)** del kernel Linux.

---

## 4.1. Interfaz sysfs o IIO

Se verifica si se ha creado el dispositivo:

```bash
ls /sys/bus/iio/devices/
```

Se debe ver un dispositivo como `iio:device0`. Luego, se inspecciona su contenido:

```bash
cd /sys/bus/iio/devices/iio:device0/
ls
```

### Ejemplo de archivos disponibles:

- `in_accel_x_raw`, `in_accel_y_raw`, `in_accel_z_raw` → Aceleración cruda
- `in_angvel_x_raw`, `in_angvel_y_raw`, `in_angvel_z_raw` → Velocidad angular cruda
- `in_accel_scale` → Factor para convertir a m/s²
- `in_angvel_scale` → Factor para convertir a °/s

---

## 4.2. Conversión a unidades reales

El MPU6050 entrega datos enteros (16 bits) que deben escalarse usando factores disponibles en los archivos `*_scale`.

### Fórmulas:

```bash
acel_real = valor_raw * in_accel_scale
gyro_real = valor_raw * in_angvel_scale
```

---

## 4.3. Script de lectura continua

Se puede automatizar el proceso con un script bash (`monitor.sh`):

```bash
#!/bin/bash

cd /sys/bus/iio/devices/iio:device0 || exit

accel_scale=$(cat in_accel_scale)
gyro_scale=$(cat in_angvel_scale)

while true; do
    ax=$(cat in_accel_x_raw)
    ay=$(cat in_accel_y_raw)
    az=$(cat in_accel_z_raw)

    gx=$(cat in_angvel_x_raw)
    gy=$(cat in_angvel_y_raw)
    gz=$(cat in_angvel_z_raw)

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

Este script convierte y muestra en consola los valores físicos del acelerómetro y giroscopio.
