# **RoboSenseLink: Sistema Distribuido de Sensado Inercial con MQTT y ROS 2**
<img width="859" height="335" alt="image" src="https://github.com/user-attachments/assets/8e6bc8b6-88b6-48cc-91b8-65b248896520" />

## 📘**1. Descripción**
**RoboSenseLink** es un sistema distribuido que utiliza sensores inerciales conectados por MQTT para enviar datos a un nodo maestro basado en ROS 2. El objetivo es monitorear, registrar y analizar el comportamiento de objetos en movimiento (por ejemplo, un robot móvil o brazo robótico) a través de una red confiable y modular.

---

## 🧱 2. Parte Estructural – RoboSenseLink

### 🔌 Hardware

#### 📍 Nodo Sensor Inercial (Unidad remota)
- **Plataforma**: Lichee RV Dock (SBC con SoC RISC-V, ejecutando Linux)
- **Sensor conectado**: MPU6050 (acelerómetro + giroscopio, vía I2C directo)
- **Alimentación**: Entrada de 5V a través de USB
- **Conectividad**:
  - Red Wi-Fi (para conexión a MQTT Broker)
- **Función principal**:
  - Actúa como nodo sensor inercial, captando datos del MPU6050 sin microcontroladores intermedios
  - Transmite los datos vía MQTT

---

#### 🖥️ Nodo Central (Estación base o robot)
- **Dispositivo**: PC con Linux (Ubuntu 22.04 compatible con ROS 2)
- **Conectividad**: Red local (Wi-Fi compartida con la Lichee RV Dock)
- **Responsabilidades**:
  - Ejecutar el entorno ROS 2 (distro recomendada: Humble)
  - Correr el **broker MQTT** (Mosquitto) que recibe los datos enviados por la Lichee
  - Ejecutar un **nodo publicador ROS 2**, que:
    - Actúa como **cliente MQTT**, se conecta al broker local
    - Recibe los mensajes publicados por la Lichee (en JSON)
    - Convierte estos mensajes a formato ROS 2
    - Publica en el tópico `/sensor/mpu6050`
  - Ejecutar uno o varios **nodos suscriptores ROS 2** (por ejemplo, en otra terminal del mismo PC), que:
    - Se **suscriben al tópico `/sensor/mpu6050`**
    - 
---

### 💻 Software

#### 🔧 Software en Lichee RV Dock (Nodo Sensor Inercial)
- **Sistema operativo**: Ubuntu 24.04 (RISC-V) ejecutándose en la Lichee RV Dock
- **Lenguaje**: Python
- **Tareas**:
  - Lectura de datos del sensor MPU6050 mediante el bus I2C (por driver IIO)
  - Procesamiento básico y empaquetado del dato (JSON)
  - Publicación de datos en un tópico MQTT (`sensor/mpu6050`) usando `paho-mqtt`
- **Tipo de nodo**: Publicador MQTT

---

#### 🌐 Broker MQTT
- **Broker**: Mosquitto
- **Ubicación**: Instalado en el nodo central (PC)
- **Características**:
  - Bajo consumo de recursos
  - Soporte para múltiples clientes (nodos sensores y clientes ROS)
  - Permite desacoplar adquisición de sensores y procesamiento ROS
  - Compatible con `paho-mqtt` y con scripts Python

---

#### 🤖 Nodo ROS 2 en la PC (cliente MQTT + publicador ROS 2)
- **Lenguaje**: Python (`rclpy`)
- **Nombres típicos de nodos**:
  - `mqtt_to_ros_node`: actúa como **cliente MQTT** que recibe datos desde el tópico `sensor/mpu6050`
  - **Transforma** el contenido MQTT (JSON) en un mensaje `sensor_msgs/Imu`
  - **Publica** el mensaje ROS 2 en el tópico `/sensor/mpu6050`
- **Tareas del nodo**:
  - Mapea datos de acelerómetro y giroscopio en los campos estándar de ROS 2
- **Visualización y prueba**:
  - `ros2 topic echo /sensor/mpu6050`

---

#### 📥 Nodo ROS 2 suscriptor (terminal separada)
- **Lenguaje**: Python 
- **Función**: Se **suscribe** al tópico `/sensor/mpu6050`
- **Tareas posibles**:
  - Visualizar datos

---

#### 🐧 Sistema Operativo
- **Distribución Linux**: Ubuntu 22.04 LTS (recomendado)
- **ROS 2 Distro recomendada**: Humble (soporte LTS)
- **Herramientas complementarias**:
  - `ros2 run`,  `ros2 topic echo`

---

## ⚙️ 3. Parte Funcional – RoboSenseLink

## **Diagrama de Flujo**
<img width="522" height="1220" alt="Diagrama_Flujo_PF" src="https://github.com/user-attachments/assets/055177ba-2d91-47ba-9180-b45806c6280f" />

---

## ** 4. Diagrama de bloque**
<img width="1497" height="372" alt="image" src="https://github.com/user-attachments/assets/0d366e73-ac4f-49bc-9ee2-34de72ac2c87" />

---

## **5. Pruebas del Sistema (Verificación y Validación)**

Esta fase tiene como objetivo demostrar el correcto funcionamiento del sistema distribuido RoboSenseLink, desde la adquisición del sensor MPU6050 hasta la visualización en ROS 2.

---

#### 1. Publicación del sensor desde la Lichee (vía MQTT)

- Verificar que la Lichee RV Dock publica datos del sensor en el tópico `sensor/mpu6050` usando MQTT.

```bash
source mqtt_env/bin/activate python3 mpu6050_mqtt.py
```

### 2. Transformación y publicación en ROS 2 desde la PC

- Verificar que el nodo ROS 2 en la PC recibe los datos desde MQTT y los publica en /sensor/mpu6050.

```bash
 ros2 topic echo /sensor/mpu6050
```

## 📊 Indicadores de funcionamiento esperados

| **Indicador**         | **Valor esperado**              | **Verificación**            |
|------------------------|----------------------------------|-----------------------------|
| Publicación MQTT       | Datos llegan a broker            | `python3 mpu6050_mqtt.py`  |
| Publicación ROS 2      | Mensajes tipo `sensor_msgs/Imu` | `ros2 topic echo`           |

---

## 🧪 Pruebas por módulo

### Sensor MPU6050
- Verificar lectura correcta por I2C en la Lichee.
- Comprobar existencia de dispositivo:

```bash
i2cdetect -y 2
```

### Cliente MQTT en Lichee
- Verificar que el script MQTT publica correctamente los datos con formato JSON.

### Nodo ROS 2 publicador (cliente MQTT → ROS)
- Verificar conversión correcta de mensaje JSON a sensor_msgs/Imu.

---

# 🔁 Prueba del sistema completo
Simular movimiento del sensor MPU6050 y observar:

1. Publicación MQTT desde Lichee.
2. Reenvío y transformación por nodo ROS 2 en PC.


  
  


