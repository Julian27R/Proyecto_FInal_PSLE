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
  echo "----------------------------"
  sleep 0.5
done
