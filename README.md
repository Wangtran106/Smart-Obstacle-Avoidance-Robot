# Smart Obstacle Avoidance & Wall-Follower Robot



This project features an Arduino-based autonomous robot designed for intelligent navigation. Equipped with three ultrasonic sensors, the robot can detect obstacles in real-time and execute a sophisticated wall-following algorithm to navigate through corridors and simple mazes.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Hardware Requirements](#hardware-requirements)
3. [Pin Mapping](#pin-mapping)
4. [Algorithm & Logic Analysis](#algorithm--logic-analysis)
5. [Code Structure](#code-structure)
6. [Installation & Setup](#installation--setup)

---

## Introduction
The robot utilizes three HC-SR04 ultrasonic sensors positioned at the Left - Middle - Right to scan its surroundings. This data is processed in real-time to control an L298N H-Bridge motor driver, which adjusts the direction and speed of two DC motors. A key highlight of this project is its Left-Wall Following capability, allowing the robot to autonomously navigate complex paths by maintaining a fixed distance from the wall.

---

## Hardware Requirements
| Component | Quantity | Notes |
| :--- | :--- | :--- |
| **Arduino Uno/Nano** | 1 | Central controller |
| **HC-SR04** | 3 | Ultrasonic distance sensors |
| **L298N Motor Driver** | 1 | For DC motor control |
| **DC Gear Motors** | 2 | Primary propulsion |
| **Li-ion 18650 Battery** | 2-3 | Power supply (7.4V - 11.1V) |
| **Robot Chassis** | 1 | 2-wheel or 4-wheel drive |

---

## Pin Mapping

### 1. Ultrasonic Sensors
- **Left Sensor:** Trig -> `A1`, Echo -> `A0`
- **Middle Sensor:** Trig -> `A2`, Echo -> `A3`
- **Right Sensor:** Trig -> `A4`, Echo -> `A5`

### 2. Motor Driver (L298N)
- **Motor A (Left):** IN1 -> `5`, IN2 -> `3`, ENA -> `6` (PWM)
- **Motor B (Right):** IN3 -> `9`, IN4 -> `10`, ENB -> `11` (PWM)

---

## Algorithm & Logic Analysis

The robot's operation is divided into three main phases within the `loop()` function:

### 1. Data Acquisition
The robot sends 5-microsecond trigger pulses to each sensor and measures the response time (`pulseIn`). Distance (cm) is calculated using:
`Distance = (Time * 0.034) / 2` (represented as `pingTime / 29 / 2` in code).

### 2. Decision Hierarchy
The robot follows a prioritized logic system to handle different scenarios:

*   **PRIORITY 1 (Emergency Reflex):** If an obstacle is too close in front (`middleDistance <= 7cm`), the robot immediately reverses (`back`) to avoid a collision.
*   **PRIORITY 2 (Directional Analysis):**
    *   If the left path is blocked but the right is clear -> Turn Right.
    *   If the right path is blocked but the left is clear -> Turn Left.
*   **PRIORITY 3 (Standard Cruising):** If all paths are clear, the robot switches to Left-Wall Following mode (`bamtrai`).

### 3. Left-Wall Following Algorithm
This logic ensures the robot stays parallel to the wall without colliding or drifting away.

1. **Distance Monitoring:** The robot continuously compares the `leftDistance` with a target value of 5cm.
2. **Micro-adjustments:**
    - If `leftDistance < 5cm`: Performs a `right(3)` (micro-turn right for 3ms) to move away from the wall.
    - If `leftDistance > 5cm`: Performs a `left(3)` (micro-turn left for 3ms) to move closer to the wall.
3. **Outcome:** These adjustments occur hundreds of times per second, resulting in a smooth, autonomous wall-following motion.

---

## Code Structure
- `void setup()`: Initializes I/O pins and Serial communication.
- `void loop()`: Continuous sensor reading and logic execution.
- `void right(int a)`, `void left(int a)`...: Basic motion control functions with a delay parameter `a`.
- `void bamtrai()`: Specific logic for wall-following behavior.

---

## Installation & Setup
1.  Download the `Test02.ino` file.
2.  Open it in the Arduino IDE.
3.  Connect your Arduino board via USB.
4.  Select the correct Board (Uno/Nano) and Port.
5.  Click Upload.
6.  Open the Serial Monitor (9600 baudrate) to monitor real-time sensor data.

---

## Tuning
If the robot does not perform as expected, you can adjust these parameters:
- `LeftSpeed` / `RightSpeed`: Adjust these to compensate for motor imbalance if the robot doesn't drive straight.
- **Distance Threshold (7cm):** Increase this if the robot is moving fast and needs more reaction time.

---
*Developed by Wangtran106.*

