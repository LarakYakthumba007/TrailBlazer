// Maze Solving Robot

// Motor speed control pins
#define vel_motor_esq 5
#define vel_motor_dir 6

// Motor direction pins
#define e1 8
#define e2 9
#define d1 12
#define d2 7

// Ultrasonic sensor pins
int trigger_front = A4; // Front trigger
int echo_front = A5;    // Front echo
int trigger_left = A3;  // Left trigger
int echo_left = A2;     // Left echo
int trigger_right = A1; // Right trigger
int echo_right = A0;    // Right echo

// Thresholds for obstacle detection
#define THRESHOLD_FRONT 15 // Distance threshold for the front (in cm)
#define THRESHOLD_SIDE 20  // Distance threshold for the sides (in cm)

// Direction states
enum Direction { NORTH, EAST, SOUTH, WEST };
Direction currentDirection = NORTH;

void setup() {
  pinMode(trigger_front, OUTPUT);
  pinMode(echo_front, INPUT);
  pinMode(trigger_left, OUTPUT);
  pinMode(echo_left, INPUT);
  pinMode(trigger_right, OUTPUT);
  pinMode(echo_right, INPUT);

  pinMode(vel_motor_esq, OUTPUT);
  pinMode(vel_motor_dir, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);

  Serial.begin(9600);
  delay(1000);
}

void loop() {
  int right, left, front;

  // Measure distances from the ultrasonic sensors
  front = measureDistance(trigger_front, echo_front);
  left = measureDistance(trigger_left, echo_left);
  right = measureDistance(trigger_right, echo_right);

  // Debugging: Print distances
  Serial.print("Front: ");
  Serial.println(front);
  Serial.print("Left: ");
  Serial.println(left);
  Serial.print("Right: ");
  Serial.println(right);

  // Movement logic based on updated requirements
  if (front > THRESHOLD_FRONT && left > THRESHOLD_SIDE && right > THRESHOLD_SIDE) {
    // Front, left, and right are clear; move forward
    Serial.println("Front clear, moving Forward");
    moveForward(80, 90);
    updateDirection('F');
  } else if (front <= THRESHOLD_FRONT && left > THRESHOLD_SIDE && right > THRESHOLD_SIDE) {
    // Obstacle at the front, but left and right are clear; prioritize left turn
    Serial.println("Obstacle at Front, turning Left");
    stopMotors();
    delay(200);
    turnLeft();
    updateDirection('L');
  } else if (front > THRESHOLD_FRONT && left <= THRESHOLD_SIDE && right <= THRESHOLD_SIDE) {
    // Obstacles on both left and right; move forward
    Serial.println("Obstacles on Left and Right, moving Forward");
    moveForward(80, 90);
    updateDirection('F');
  } else if (front <= THRESHOLD_FRONT && left <= THRESHOLD_SIDE && right > THRESHOLD_SIDE) {
    // Obstacle at Front and Left; turn Right
    Serial.println("Obstacle at Front and Left, turning Right");
    stopMotors();
    delay(200);
    turnRight();
    updateDirection('R');
  } else if (front <= THRESHOLD_FRONT && right <= THRESHOLD_SIDE && left > THRESHOLD_SIDE) {
    // Obstacle at Front and Right; turn Left
    Serial.println("Obstacle at Front and Right, turning Left");
    stopMotors();
    delay(200);
    turnLeft();
    updateDirection('L');
  } else {
    // Default case: No clear path; move backward
    Serial.println("No clear path, moving Backward");
    stopMotors();
    delay(200);
    moveBackwardAvoidingPath();
  }

  // Small delay for stability
  delay(100);
}

// Measure distance from an ultrasonic sensor
int measureDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(1);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration / 29 / 2;
  return distance;
}

// Stop motors
void stopMotors() {
  analogWrite(vel_motor_esq, 0);
  analogWrite(vel_motor_dir, 0);
  digitalWrite(e1, LOW);
  digitalWrite(e2, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
}

// Move forward
void moveForward(int leftSpeed, int rightSpeed) {
  analogWrite(vel_motor_esq, leftSpeed);
  analogWrite(vel_motor_dir, rightSpeed);
  digitalWrite(e1, HIGH);
  digitalWrite(e2, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  delay(100);
}

// Turn left
void turnLeft() {
  analogWrite(vel_motor_esq, 100);
  analogWrite(vel_motor_dir, 100);
  digitalWrite(e1, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  delay(700); // Adjusted delay for 90-degree turn
}

// Turn right
void turnRight() {
  analogWrite(vel_motor_esq, 100);
  analogWrite(vel_motor_dir, 100);
  digitalWrite(e1, HIGH);
  digitalWrite(e2, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  delay(700); // Adjusted delay for 90-degree turn
}

// Move backward and avoid revisiting the same path
void moveBackwardAvoidingPath() {
  moveBackward();
  delay(1200);
  // After moving back, turn in a different direction to avoid previous path
  if (currentDirection == NORTH) {
    turnLeft();
    updateDirection('L');
  } else if (currentDirection == EAST) {
    turnRight();
    updateDirection('R');
  } else if (currentDirection == SOUTH) {
    turnLeft();
    updateDirection('L');
  } else if (currentDirection == WEST) {
    turnRight();
    updateDirection('R');
  }
}

// Move backward
void moveBackward() {
  analogWrite(vel_motor_esq, 100);
  analogWrite(vel_motor_dir, 100);
  digitalWrite(e1, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  delay(1200);
}

// Update the current direction of the robot
void updateDirection(char movement) {
  if (movement == 'L') {
    currentDirection = static_cast<Direction>((currentDirection + 3) % 4);
  } else if (movement == 'R') {
    currentDirection = static_cast<Direction>((currentDirection + 1) % 4);
  } else if (movement == 'F') {
    // Forward maintains the current direction
  }
}