# **RoboSenseLink: Sistema Distribuido de Sensado Inercial con MQTT y ROS 2**
<img width="859" height="335" alt="image" src="https://github.com/user-attachments/assets/8e6bc8b6-88b6-48cc-91b8-65b248896520" />

# **RoboSenseLink: Sistema Distribuido de Sensado Inercial con MQTT y ROS 2**
<img width="859" height="335" alt="image" src="https://github.com/user-attachments/assets/8e6bc8b6-88b6-48cc-91b8-65b248896520" />

## 📘**1. Descripción**
**RoboSenseLink** es un sistema distribuido que utiliza sensores inerciales conectados por MQTT para enviar datos a un nodo maestro basado en ROS 2. El objetivo es monitorear, registrar y analizar el comportamiento de objetos en movimiento (por ejemplo, un robot móvil o brazo robótico) a través de una red confiable y modular.

---

## 🧱 1.1 Parte Estructural – RoboSenseLink

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

## ⚙️ 1.2 Parte Funcional – RoboSenseLink

## **Diagrama de Flujo**
<img width="522" height="1220" alt="Diagrama_Flujo_PF" src="https://github.com/user-attachments/assets/055177ba-2d91-47ba-9180-b45806c6280f" />

