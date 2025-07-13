# Fase 1 – Preparación del entorno y compilación del driver MPU6050

Esta fase describe cómo preparar el entorno de la Lichee RV Dock y compilar el driver `inv_mpu6050` para habilitar la comunicación IIO con el sensor MPU6050.

---

## 1. Preparación del entorno en Lichee Pi

### 1.1 Instalar Linux con soporte para desarrollo

```bash
sudo apt update
sudo apt install build-essential git cmake python3 python3-pip
```

### 1.2 Instalar headers del kernel (necesarios para compilar drivers)

```bash
sudo apt install linux-headers-$(uname -r)
```

---

## 2. Compilar y cargar el driver del MPU6050

### 2.1 Obtener el driver

```bash
git clone --depth=1 --branch rpi-6.12.y https://github.com/raspberrypi/linux.git
cd linux
```

### 2.2 Preparar el entorno de compilación

```bash
sudo apt install build-essential bc libncurses-dev flex bison libssl-dev
sudo apt install make gcc
```

---
### 2.3 Modificaciones necesarias para compatibilidad con Lichee RV Dock (kernel 6.8)

Dado que el código fuente del driver está basado en el árbol del kernel 6.12 de Raspberry Pi, pero será compilado contra los headers del kernel 6.8 (utilizado en la Lichee RV Dock), es necesario adaptar dos archivos .c a las firmas de funciones esperadas por el sistema.

🔧 inv_mpu_ring.c

- Modificar la llamada a la función inv_sensors_timestamp_interrupt para que tenga 5 argumentos en lugar de 3.
- Firma esperada por el kernel 6.8:

```c
int inv_sensors_timestamp_interrupt(
    struct inv_sensors_timestamp *ts,
    uint32_t fifo_period,
    size_t fifo_nb,
    size_t sensor_nb,
    int64_t timestamp
);
```

- Modificación sugerida:

  editar inv_mpu_ring.c

```bash
nano inv_mpu_ring.c
```

  Ubicar en inv_mpu_ring.c la línea correspondiente y reemplazar por:
  
```c
inv_sensors_timestamp_interrupt(ts, 0, 1, 1, pf->timestamp);
```

### 2.4 Crear Makefile externo y compilar el módulo

Dentro del directorio `inv_mpu6050/`, crear el archivo `Makefile.external`:

```makefile
obj-m := inv_mpu6050.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
```

Luego, compilar usando:

```bash
make -f Makefile.external
```

---

### 2.4 Cargar el módulo en el kernel

Se recomienda usar `modprobe` para que el sistema cargue automáticamente las dependencias del driver:

```bash
sudo modprobe industrialio
sudo modprobe industrialio-triggered-buffer
sudo modprobe inv_sensors_timestamp
sudo insmod inv_mpu6050.ko
sudo insmod inv-mpu6050-i2c.ko
```

Verificar que el driver está cargado:

```bash
lsmod | grep inv_mpu
```

---

✅ **Resultado esperado**:
El módulo `inv_mpu6050` e `inv_mpu6050_i2c` se encuentran cargados correctamente y el sensor queda accesible mediante el sistema IIO.
