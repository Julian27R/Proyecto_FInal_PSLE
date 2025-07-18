# Fase 1 – Preparación del entorno y compilación del driver MPU6050

<img width="1024" height="1536" alt="image" src="https://github.com/user-attachments/assets/c85ee62a-5ff6-49a8-8f6b-ebb2b20d38cf" />


Esta fase describe cómo preparar el entorno de la Lichee RV Dock y compilar el driver `inv_mpu6050` para habilitar la comunicación IIO con el sensor MPU6050.

---

## 1. Imagen Cargada en la Lichee
En el siguiente link se encuentra la página para Descargar la imagen de Ubuntu 24.04.2 para plataformas RISC-V usada en la Lichee Rv Dock para este Proyecto.
https://ubuntu.com/download/risc-v
<img width="747" height="34" alt="image" src="https://github.com/user-attachments/assets/f2919085-56ec-4adc-8bc8-a8944225aa0d" />

## 2. Preparación del entorno en Lichee Pi

### 2.1 Instalar Linux con soporte para desarrollo

```bash
sudo apt update
sudo apt install build-essential git cmake python3 python3-pip
```

### 2.2 Instalar headers del kernel (necesarios para compilar drivers)

```bash
sudo apt install linux-headers-$(uname -r)
```

---

## 3. Compilar y cargar el driver del MPU6050

### 3.1 Obtener el driver

```bash
git clone --depth=1 --branch rpi-6.12.y https://github.com/raspberrypi/linux.git
cd linux
```

### 3.2 Preparar el entorno de compilación

```bash
sudo apt install build-essential bc libncurses-dev flex bison libssl-dev
sudo apt install make gcc
```

---
### 3.3 Modificaciones necesarias para compatibilidad con Lichee RV Dock (kernel 6.8)

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

Editar inv_mpu_ring.c

```bash
nano inv_mpu_ring.c
```

Ubicar en inv_mpu_ring.c la línea correspondiente y reemplazar por:
  
```c
inv_sensors_timestamp_interrupt(ts, 0, 1, 1, pf->timestamp);
```

🔧 inv_mpu_i2c.c

- Modificar la llamada a la función i2c_mux_add_adapter para coincidir con la firma requerida por el kernel 6.8:

```c
int i2c_mux_add_adapter(struct i2c_mux_core *muxc, unsigned int chan_id,
                        u32 class, u32 flags);
```

- Modificación sugerida:

Editar inv_mpu_i2c.c

```bash
nano inv_mpu_i2c.c
```

Ubicar la línea correspondiente y reemplazar por

```c
i2c_mux_add_adapter(muxc, chan_id, 0, 0);
```

Estas modificaciones aseguran compatibilidad con el entorno de kernel actual de la Lichee RV Dock antes de proceder con la compilación.

### 3.4 Crear Makefile externo y compilar el módulo

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

### 3.5 Cargar el módulo en el kernel

Una vez que el módulo ha sido compilado correctamente, es necesario cargarlo junto con todos los módulos dependientes del subsistema IIO y del subsistema I2C multiplexado.

A continuación se detalla el procedimiento completo paso a paso:

1. Cargar subsistemas IIO requeridos por inv_mpu6050.ko

El módulo principal inv_mpu6050.ko depende de los siguientes módulos del kernel:

- industrialio
- industrialio-triggered-buffer
- inv_sensors_timestamp

Cargarlos con:

```bash
sudo modprobe industrialio
sudo modprobe industrialio-triggered-buffer
sudo modprobe inv_sensors_timestamp
```
Luego cargar el módulo principal del driver MPU6050:

```bash
sudo insmod inv_mpu6050.ko
```

Verifica que se haya cargado correctamente:

```bash
lsmod | grep inv_mpu
```

2. Cargar módulos base de I2C-MUX

Antes de cargar el módulo I2C del driver (inv-mpu6050-i2c.ko), es necesario asegurarse de que estén cargados los siguientes módulos del kernel, ya que proporcionan símbolos que el driver necesita

Símbolos requeridos:

- i2c_mux_alloc
- i2c_mux_add_adapter
- i2c_mux_del_adapters

Módulos que deben cargarse:

```bash
sudo modprobe i2c-mux
sudo modprobe i2c-mux-pinctrl
sudo modprobe i2c-mux-reg
```

Una vez cargadas las dependencias anteriores, se puede cargar el módulo inv-mpu6050-i2c.ko

```bash
sudo insmod inv-mpu6050-i2c.ko
```

Verifica que esté cargado:

```bash
lsmod | grep inv_mpu
```

Ejemplo de salida esperada:

![Imagen de WhatsApp 2025-07-13 a las 19 08 45_ea93bef8](https://github.com/user-attachments/assets/e729d707-9d35-427e-a3ee-5c74f8ad740f)

Resultado esperado:

- Los módulos inv_mpu6050 y inv_mpu6050_i2c están correctamente cargados.
- El sensor MPU6050 queda expuesto a través del subsistema IIO.
  
