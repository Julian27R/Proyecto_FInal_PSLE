# Fase 5: Publicación de Datos del Sensor MPU6050 desde Lichee RV Dock hacia ROS 2 mediante MQTT

<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/2df76064-3f0d-467b-90f7-d5ec531302c4" />


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

- colcon y paho-mqtt instalados:

  ### Instalación de colcon

```bash
sudo apt update
sudo apt install python3-colcon-common-extensions -y
```

### Verificar versión de ROS

```bash
printenv | grep ROS
```

### Crear workspace en la PC (ROS 2)

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws
colcon build
source install/setup.bash
echo "source ~/ros2_ws/install/setup.bash" >> ~/.bashrc
```

### Crear paquete ROS 2 mqtt_to_ros2

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_python mqtt_to_ros2 --dependencies rclpy std_msgs
```
### Crear nodo publicador ROS

Crear archivo:

```bash
nano ~/ros2_ws/src/mqtt_to_ros2/mqtt_to_ros2/mqtt_ros2_publisher.py
```

Contenido del archivo:

```python
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import paho.mqtt.client as mqtt

class MqttRos2Publisher(Node):
    def __init__(self):
        super().__init__('mqtt_ros2_publisher')
        self.publisher_ = self.create_publisher(String, 'mpu6050/data', 10)

        # Setup MQTT
        self.mqtt_client = mqtt.Client()
        self.mqtt_client.on_connect = self.on_connect
        self.mqtt_client.on_message = self.on_message
        self.mqtt_client.connect("localhost", 1883, 60)
        self.mqtt_client.loop_start()

    def on_connect(self, client, userdata, flags, rc):
        self.get_logger().info("Conectado al broker MQTT")
        client.subscribe("sensor/mpu6050")

    def on_message(self, client, userdata, msg):
        message = msg.payload.decode()
        ros_msg = String()
        ros_msg.data = message
        self.publisher_.publish(ros_msg)
        self.get_logger().info(f'Publicado en ROS: {message}')

def main(args=None):
    rclpy.init(args=args)
    node = MqttRos2Publisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
```

### Editar setup.py

```bash
nano ~/ros2_ws/src/mqtt_to_ros2/setup.py
```

Modificar:

```python
from setuptools import find_packages, setup

package_name = 'mqtt_to_ros2'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='felipe',
    maintainer_email='felipe@todo.todo',
    description='Nodo que publica datos del MPU6050 recibidos por MQTT',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'mqtt_ros2_publisher = mqtt_to_ros2.mqtt_ros2_publisher:main',
        ],
    },
)
```

### Ejecutar el nodo publicador ROS 2

🖥️ En la PC (terminal con ROS 2 activo):

```bash
cd ~/ros2_ws
ros2 run mqtt_to_ros2 mqtt_ros2_publisher
```

📟 En la Lichee (terminal con entorno activo):
```bash
source mqtt_env/bin/activate
python3 mpu6050_mqtt.py
```

Esto activará la lectura continua del sensor MPU6050, enviando datos por MQTT y publicándolos en tiempo real en el tópico /mpu6050/data en ROS 2.

