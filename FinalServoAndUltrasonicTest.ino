#include <Servo.h>

// Define pins
const int trigPin = 7;
const int echoPin = 6;
const int servoPin = 9;

// Set up servo and distance threshold
Servo trashServo;
const int distanceThreshold = 20;  // Distance in cm to detect a person

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);
  
  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Attach servo motor
  trashServo.attach(servoPin);
  trashServo.write(90); // Start with the lid closed
}

void loop() {
  // Measure distance from ultrasonic sensor
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  // If distance is below threshold, open the lid
  if (distance > 0 && distance <= distanceThreshold) {
    trashServo.write(180); // Open the lid
    delay(3000);          // Wait for 3 seconds (lid open duration)
    trashServo.write(90);   // Close the lid
  }
  
  delay(100); // Small delay for stability
}

// Function to measure distance
long getDistance() {
  // Send a pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin response
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;  // Convert duration to distance

  return distance;
}
