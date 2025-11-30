# Trail Blazer 🟢

**Trail Blazer** is an Arduino-powered autonomous maze-solving robot. It uses ultrasonic sensors to detect obstacles and navigate through mazes intelligently. This project demonstrates core robotics concepts such as sensor integration, motor control, and pathfinding algorithms.

---

## Features

- Autonomous maze navigation
- Uses **ultrasonic sensors** for front, left, and right obstacle detection
- Implements decision-making logic to handle multiple paths
- LED indicators and motor speed control for smooth operation
- Modular design for easy assembly and customization

---

## Components Required

- Arduino Uno or compatible board  
- 2 DC Motors with motor driver  
- Ultrasonic sensors (3x HC-SR04 recommended)  
- Jumper wires and breadboard  
- Power supply (battery pack)

---

## Pin Configuration

| Component              | Pin             |
|------------------------|----------------|
| Left Motor PWM         | 5              |
| Right Motor PWM        | 6              |
| Left Motor Direction   | 8, 9           |
| Right Motor Direction  | 12, 7          |
| Ultrasonic Front TRIG  | A4             |
| Ultrasonic Front ECHO  | A5             |
| Ultrasonic Left TRIG   | A3             |
| Ultrasonic Left ECHO   | A2             |
| Ultrasonic Right TRIG  | A1             |
| Ultrasonic Right ECHO  | A0             |

---

## How It Works

1. The robot continuously measures distances using **ultrasonic sensors**.
2. Based on detected obstacles, it decides whether to move forward, turn left, turn right, or move backward.
3. **Movement logic:**
   - Clear path → Move forward
   - Obstacle front → Prioritize left or right turn
   - Obstacle on multiple sides → Move backward and choose alternative path
4. Direction updates are tracked using a simple enum (`NORTH, EAST, SOUTH, WEST`) to avoid revisiting paths.

---

## Arduino Functions Overview

- `measureDistance(triggerPin, echoPin)` → Measures distance from ultrasonic sensor  
- `moveForward(leftSpeed, rightSpeed)` → Moves robot forward at specified speed  
- `turnLeft()` → Performs a 90° left turn  
- `turnRight()` → Performs a 90° right turn  
- `moveBackward()` → Moves robot backward  
- `moveBackwardAvoidingPath()` → Moves backward and chooses alternative path to avoid loops  
- `updateDirection(movement)` → Updates robot’s current orientation  

---

## Usage

1. Connect motors and sensors according to the pin configuration above.
2. Upload the Arduino code provided in this repository to your board.
3. Place the robot inside any maze.
4. Power on the robot and observe as it navigates and solves the maze autonomously.

---



