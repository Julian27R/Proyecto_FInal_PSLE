# Fase 6: Publicación de Datos del Sensor MPU6050 desde Lichee RV Dock hacia ROS 2 mediante MQTT

Esta fase del proyecto implementa la integración de un sensor I2C (MPU6050) conectado a la Lichee RV Dock, utilizando MQTT como protocolo intermedio para transmitir los datos hacia un PC. En el PC, los datos son recibidos y publicados como mensajes en un tópico de ROS 2, permitiendo su acceso por otros nodos del sistema. Esta etapa establece la base para una arquitectura distribuida de percepción sensorial en entornos robóticos.

En esta fase, la Lichee RV Dock adquiere datos del sensor MPU6050 vía I2C y los transmite mediante el protocolo MQTT hacia un PC. En el PC, el nodo publicador de ROS 2 llamado mqtt_ros2_publisher recibe estos datos desde el broker MQTT y los publica en tiempo real en el tópico /mpu6050/data.

---

## ✅ Requisitos previos

### En la Lichee:

- Python 3 y entorno virtual creado (mqtt_env)
- Sensor MPU6050 conectado y funcionando vía I2C
- MQTT broker corriendo en el PC (usando mosquitto)

### En el PC:

- ROS 2 Humble instalado
- mosquitto instalado y en ejecución:  
  ```bash
  sudo systemctl start mosquitto
