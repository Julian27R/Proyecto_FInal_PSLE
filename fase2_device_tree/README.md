# Fase 2: Habilitación del bus I2C2 (TWI2) en Lichee RV Dock para el sensor MPU6050

Esta fase consiste en habilitar el bus I2C2 (TWI2) en la placa **Lichee RV Dock** para permitir la comunicación con el sensor **MPU6050**. Este bus no está activado por defecto en el Device Tree (árbol de dispositivos), por lo que se requiere modificarlo manualmente y recompilar el árbol de dispositivos.

## ℹ️ Introducción

La placa Lichee RV Dock incluye hasta 4 controladores I2C (TWI0, TWI1, TWI2 y TWI3), pero no todos están activos por defecto.

Para conectar el sensor MPU6050 usando los pines:

- 🟢 PB0 → SCL (reloj)  
- 🟢 PB1 → SDA (datos)  

se debe habilitar el controlador TWI2.

| Controlador | Pines físicos          | Dirección base   |
|-------------|------------------------|------------------|
| TWI2        | 3.3V, PB0, PB1, GND    | 0x02502800 (hex) |

📌 Referencias visuales:

- Diagrama de pines (PB0/PB1 destacados):  

  <img width="313" height="404" alt="image" src="https://github.com/user-attachments/assets/2b7e4969-3aa5-482f-a8fe-690b31d26102" />


- Tabla de direcciones base de controladores I2C:  

  <img width="692" height="190" alt="image" src="https://github.com/user-attachments/assets/f0cdd62d-5347-4390-9034-5302243f3fb5" />

---

## 🛠️ Pasos realizados

### 1. Exportar el árbol de dispositivos (`.dtb`) y convertirlo a formato editable (`.dts`)

```bash
cp /boot/dtbs/$(uname -r)/allwinner/sun20i-d1-lichee-rv-dock.dtb ~/sun20i-d1-lichee-rv-dock.dtb
dtc -I dtb -O dts -o arbol.dts sun20i-d1-lichee-rv-dock.dtb
```

---

### 2. Editar `arbol.dts` para activar el bus I2C2 (TWI2) y registrar el MPU6050

Se edita el archivo

```bash
nano arbol.dts
```

Se añadieron las siguientes secciones:

#### a) Nodo para `i2c2@2502800`:

```dts
i2c2@2502800 {
    compatible = "allwinner,sun20i-d1-i2c";
    reg = <0x02502800 0x400>;
    interrupts = <0x1b 0x04>;
    clocks = <0x04 0x46>;
    resets = <0x04 0x1a>;
    dmas = <0x08 0x2d 0x08 0x2d>;
    dma-names = "rx", "tx";
    pinctrl-names = "default";
    pinctrl-0 = <&i2c2_pb0_pb1_pins>;
    status = "okay";

    mpu6050@68 {
        compatible = "invensense,mpu6050";
        reg = <0x68>;
        mount-matrix = "1", "0", "0", "0", "1", "0", "0", "0", "1";
    };
};
```

#### b) Nodo de pines `i2c2_pb0_pb1_pins`:

```dts
i2c2_pb0_pb1_pins: i2c2-pb0-pb1-pins {
    pins = "PB0", "PB1";
    function = "i2c2";
};
```

---

### 3. Compilar nuevamente el Device Tree

```bash
dtc -I dts -O dtb -o arbol.dtb arbol.dts
```

---

### 4. Renombrar y reemplazar el archivo `.dtb`

```bash
mv arbol.dtb sun20i-d1-lichee-rv-dock.dtb
sudo cp sun20i-d1-lichee-rv-dock.dtb /boot/dtbs/$(uname -r)/allwinner/sun20i-d1-lichee-rv-dock.dtb
sudo cp sun20i-d1-lichee-rv-dock.dtb /boot/dtb.dtb
```

---

### 5. Reiniciar la placa

```bash
sudo reboot
```

---

### 6. Verificar que el I2C2 esté habilitado y el sensor reconocido

#### a) Comprobar si el driver fue cargado correctamente:

```bash
dmesg | grep -i i2c
```

#### b) Listar los buses I2C:

```bash
ls /dev/i2c-*
```

Debe aparecer `/dev/i2c-1`.

#### c) Escanear el bus I2C2:

```bash
sudo i2cdetect -y 1
```

Debe mostrar el sensor en la dirección `0x68` con el código `UU`, indicando que ya fue reclamado por el kernel.

---

## ✅ Resultado

El sensor **MPU6050** fue correctamente detectado en el bus **I2C2** a través de los pines **PB0** (SCL) y **PB1** (SDA), y el driver `inv-mpu6050` lo reconoció automáticamente al reiniciar el sistema.
