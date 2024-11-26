#include <Servo.h>

const int entrySensor = 2;    // Pin for entry sensor
const int exitSensor = 3;     // Pin for exit sensor
const int servoPin = 9;       // Pin for servo motor

Servo gateServo;  // Servo object
int carCount = 0;  // Initialize car count

int maxCapacity = 5;  // Set maximum parking capacity

void setup() {
  pinMode(entrySensor, INPUT);   // Set entry sensor pin as input
  pinMode(exitSensor, INPUT);    // Set exit sensor pin as input
  gateServo.attach(servoPin);    // Attach servo to pin

  Serial.begin(9600);            // Start serial communication
  gateServo.write(0);            // Initial position (gate closed)
}

void loop() {
  // Check if a car enters (entry sensor triggered)
  if (digitalRead(entrySensor) == HIGH && carCount < maxCapacity) {
    carCount++;
    Serial.print("Car Entered. Count: ");
    Serial.println(carCount);
    gateServo.write(90); // Open gate
    delay(1000);          // Wait for a second to let the car pass
    gateServo.write(0);   // Close gate
    delay(1000);
  }

  // Check if a car exits (exit sensor triggered)
  if (digitalRead(exitSensor) == HIGH && carCount > 0) {
    carCount--;
    Serial.print("Car Exited. Count: ");
    Serial.println(carCount);
    delay(1000);  // Wait for the car to pass through
  }

  // If the parking lot is full, don't let more cars enter
  if (carCount >= maxCapacity) {
    Serial.println("Parking Full! No more cars allowed to enter.");
  }

  delay(100);  // Small delay to prevent sensor bounce
}
