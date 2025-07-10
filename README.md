# Project Beacon

In this project, I designed and programmed an electronic circuit for a dropper and beacon system for a drone. The beacon is a falling object equipped with LEDs, and the dropper releases it. The entire system is controlled by a Raspberry Pi running a control algorithm using ROS2.

## Hardware

I chose an ESP microcontroller because it's easy to use for wireless communication. One ESP module communicates with the Raspberry Pi, controls the dropper, and sends commands to another ESP on the beacon via ESP-NOW.  
Communication with the Raspberry Pi is done through UART.  
The dropper operates with a 25V electromagnet, so I designed a transistor switch to control it from the ESP. I simulated this circuit in LTspice.

## Code

After finishing the hardware design, I worked with my teammates to write the software. I programmed the ESP on the host (dropper) side, one of my friends wrote the code for the beacon ESP (slave), and another teammate developed the ROS2 node that sends commands via USB.

## Results

The whole system worked correctly during the competition, but unfortunately, we didn't get a chance to deploy it using GPS on the drone.
