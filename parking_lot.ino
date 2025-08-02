#include <Servo.h>

// Pins for sensors and LEDs
#define ENTRY_SENSOR 2
#define EXIT_SENSOR 3
#define RED_LIGHT 4
#define YELLOW_LIGHT 5
#define GREEN_LIGHT 6
#define GATE_SERVO_PIN 9

// Parking capacity
const int totalSlots = 3;
int availableSlots = totalSlots;

Servo gate;

void setup() {
  Serial.begin(9600);

  // Input pins
  pinMode(ENTRY_SENSOR, INPUT);
  pinMode(EXIT_SENSOR, INPUT);

  // Traffic Light LEDs
  pinMode(RED_LIGHT, OUTPUT);
  pinMode(YELLOW_LIGHT, OUTPUT);
  pinMode(GREEN_LIGHT, OUTPUT);

  gate.attach(GATE_SERVO_PIN);
  gate.write(0); // Initial gate closed

  updateTrafficLight();
}

void loop() {
  // Detect car at entry
  if (digitalRead(ENTRY_SENSOR) == HIGH && availableSlots > 0) {
    Serial.println("Car detected at entry");
    openGate();
    delay(2000); // Simulate car passing
    closeGate();
    availableSlots--;
    updateTrafficLight();
  }

  // Detect car at exit
  if (digitalRead(EXIT_SENSOR) == HIGH && availableSlots < totalSlots) {
    Serial.println("Car detected at exit");
    openGate();
    delay(2000); // Simulate car exiting
    closeGate();
    availableSlots++;
    updateTrafficLight();
  }

  delay(300);
}

void openGate() {
  gate.write(90); // Open position
  Serial.println("Gate opened");
}

void closeGate() {
  gate.write(0); // Closed position
  Serial.println("Gate closed");
}

void updateTrafficLight() {
  if (availableSlots == 0) {
    digitalWrite(RED_LIGHT, HIGH);
    digitalWrite(YELLOW_LIGHT, LOW);
    digitalWrite(GREEN_LIGHT, LOW);
    Serial.println("Parking Full - RED Light");
  } else if (availableSlots == 1) {
    digitalWrite(RED_LIGHT, LOW);
    digitalWrite(YELLOW_LIGHT, HIGH);
    digitalWrite(GREEN_LIGHT, LOW);
    Serial.println("Limited Space - YELLOW Light");
  } else {
    digitalWrite(RED_LIGHT, LOW);
    digitalWrite(YELLOW_LIGHT, LOW);
    digitalWrite(GREEN_LIGHT, HIGH);
    Serial.println("Slots Available - GREEN Light");
  }
}
