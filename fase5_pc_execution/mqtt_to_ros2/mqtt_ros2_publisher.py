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

        self.mqtt_client.connect('localhost', 1883, 60)
        self.mqtt_client.loop_start()

    def on_connect(self, client, userdata, flags, rc):
        self.get_logger().info('Conectado al broker MQTT')
        client.subscribe('sensor/mpu6050')

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
