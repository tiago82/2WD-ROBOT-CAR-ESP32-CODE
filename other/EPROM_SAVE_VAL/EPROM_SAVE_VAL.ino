#include <EEPROM.h>

const int EEPROM_SIZE = 512; // Adjust this based on your requirements
const int KP_ADDRESS = 0;     // Address in EEPROM for kp
const int KI_ADDRESS = 4;     // Address in EEPROM for ki
const int KD_ADDRESS = 8;     // Address in EEPROM for kd
const int SETPOINT_ADDRESS = 12; // Address in EEPROM for setpoint

double kp, ki, kd, setpoint;

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Failed to initialize EEPROM");
    while (1);
  }

  // Uncomment the next line to clear EEPROM (for testing purposes)
  // EEPROM.convert(true);

  // Read initial values from EEPROM
  EEPROM.get(KP_ADDRESS, kp);
  EEPROM.get(KI_ADDRESS, ki);
  EEPROM.get(KD_ADDRESS, kd);
  EEPROM.get(SETPOINT_ADDRESS, setpoint);

  Serial.println("Initial values:");
  Serial.print("kp: "); Serial.println(kp);
  Serial.print("ki: "); Serial.println(ki);
  Serial.print("kd: "); Serial.println(kd);
  Serial.print("setpoint: "); Serial.println(setpoint);
}

void loop() {
  // Check if there is any incoming data
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');

    // Check if the input starts with a specific command
    if (input.startsWith("kp")) {
      kp = input.substring(2).toDouble();
      EEPROM.put(KP_ADDRESS, kp);
      EEPROM.commit();
      Serial.println("kp updated.");
    } 
    else if (input.startsWith("ki")) {
      ki = input.substring(2).toDouble();
      EEPROM.put(KI_ADDRESS, ki);
      EEPROM.commit();
      Serial.println("ki updated.");
    } 
    else if (input.startsWith("kd")) {
      kd = input.substring(2).toDouble();
      EEPROM.put(KD_ADDRESS, kd);
      EEPROM.commit();
      Serial.println("kd updated.");
    } 
    else if (input.startsWith("setpoint")) {
      setpoint = input.substring(8).toDouble();
      EEPROM.put(SETPOINT_ADDRESS, setpoint);
      EEPROM.commit();
      Serial.println("setpoint updated.");
    } 
    else {
      Serial.println("Invalid command.");
    }
  }

  // Print the values every 5 seconds
  static unsigned long lastPrintTime = 0;
  if (millis() - lastPrintTime >= 5000) {
    Serial.println("Current values:");
    Serial.print("kp: "); Serial.println(kp);
    Serial.print("ki: "); Serial.println(ki);
    Serial.print("kd: "); Serial.println(kd);
    Serial.print("setpoint: "); Serial.println(setpoint);

    lastPrintTime = millis();
  }

  // Your main loop code here
}
