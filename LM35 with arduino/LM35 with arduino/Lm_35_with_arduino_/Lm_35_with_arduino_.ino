// ====================================================
// LM35 Temperature Monitor with LED and Buzzer Control
// Arduino Uno IDE Version
// ====================================================
//
// Hardware Connections:
// ----------------------------------------------------
// LM35 Temperature Sensor:
//   VCC  -> Arduino 5V
//   OUT  -> Arduino A5
//   GND  -> Arduino GND
//
// LEDs (with 220Ω resistors):
//   Red LED   -> Pin 10
//   Green LED -> Pin 11
//
// Buzzer:
//   Positive (+) -> Pin 8
//   Negative (-) -> GND
//
// Serial Communication: 9600 baud
// ====================================================

// Pin Definitions
const int LM35_PIN = A5;        // LM35 connected to analog pin A5
const int RED_LED = 10;         // Red LED on pin 10
const int GREEN_LED = 11;       // Green LED on pin 11
const int BUZZER = 8;           // Buzzer on pin 8

// Constants
const float VOLTAGE_REF = 5.0;  // Arduino reference voltage
const int ADC_MAX = 1023;       // Maximum ADC value (10-bit)
const float LM35_SCALE = 0.01;  // LM35: 10mV per °C (0.01V/°C)

// Variables
float temperature = 0.0;        // Current temperature
float alarmThreshold = 60.0;    // Default alarm threshold

// Timing variables
unsigned long lastReadTime = 0;
const long READ_INTERVAL = 100; // Read every 100ms (10Hz)

// For temperature smoothing
const int SMOOTHING_SIZE = 5;
float tempHistory[SMOOTHING_SIZE];
int smoothIndex = 0;
float tempSum = 0;

// For buzzer pulsing
unsigned long lastBuzzerTime = 0;
const long BUZZER_INTERVAL = 500; // Buzzer pulse every 500ms
bool buzzerState = false;

// Serial command buffer
String commandBuffer = "";

// ====================================================
// SETUP FUNCTION - RUNS ONCE AT STARTUP
// ====================================================
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Turn off all outputs
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER, LOW);
  
  // Initialize temperature history
  for (int i = 0; i < SMOOTHING_SIZE; i++) {
    tempHistory[i] = 0.0;
  }
  
  // Wait for serial to initialize (for Arduino Leonardo/Micro)
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  // Startup message
  Serial.println("========================================");
  Serial.println("LM35 Temperature Monitor v1.0");
  Serial.println("========================================");
  Serial.print("Alarm Threshold: ");
  Serial.print(alarmThreshold, 1);
  Serial.println("°C");
  Serial.println("Ready...");
  Serial.println("========================================");
  delay(1000); // Short delay for stability
}

// ====================================================
// MAIN LOOP - RUNS REPEATEDLY
// ====================================================
void loop() {
  unsigned long currentTime = millis();
  
  // 1. Check for serial commands
  checkSerial();
  
  // 2. Read temperature at regular intervals
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;
    
    // Read and process temperature
    readTemperature();
    
    // Send temperature to serial monitor
    Serial.println(temperature, 2);
    
    // Update outputs (LEDs and buzzer)
    updateOutputs();
  }
  
  // 3. Handle buzzer pulsing (if in alarm state)
  if (temperature >= alarmThreshold) {
    handleBuzzer(currentTime);
  }
}

// ====================================================
// READ TEMPERATURE FROM LM35 SENSOR
// ====================================================
void readTemperature() {
  // Read raw analog value (0-1023)
  int rawValue = analogRead(LM35_PIN);
  
  // Convert to voltage (0-5V)
  float voltage = (rawValue * VOLTAGE_REF) / ADC_MAX;
  
  // Convert voltage to temperature (LM35: 10mV per °C)
  float currentTemp = voltage / LM35_SCALE;
  
  // Alternative calculation (faster):
  // float currentTemp = rawValue * 0.48828125; // (5000/1024)/10
  
  // Apply simple moving average for smoothing
  tempSum -= tempHistory[smoothIndex];
  tempHistory[smoothIndex] = currentTemp;
  tempSum += currentTemp;
  smoothIndex = (smoothIndex + 1) % SMOOTHING_SIZE;
  
  // Calculate smoothed temperature
  temperature = tempSum / SMOOTHING_SIZE;
}

// ====================================================
// UPDATE LEDS BASED ON TEMPERATURE
// ====================================================
void updateOutputs() {
  if (temperature >= alarmThreshold) {
    // ALARM STATE - Temperature is too high
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  } else {
    // NORMAL STATE - Temperature is okay
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    buzzerState = false;
  }
}

// ====================================================
// HANDLE BUZZER WITH PULSING EFFECT
// ====================================================
void handleBuzzer(unsigned long currentTime) {
  if (temperature >= alarmThreshold + 10) {
    // EXTREME HEAT - Continuous buzzer
    digitalWrite(BUZZER, HIGH);
    buzzerState = true;
  } else if (currentTime - lastBuzzerTime >= BUZZER_INTERVAL) {
    // MODERATE HEAT - Pulsing buzzer
    lastBuzzerTime = currentTime;
    buzzerState = !buzzerState;
    digitalWrite(BUZZER, buzzerState ? HIGH : LOW);
  }
}

// ====================================================
// CHECK FOR SERIAL COMMANDS FROM PYTHON
// ====================================================
void checkSerial() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    if (c == '\n' || c == '\r') {
      // End of command received
      if (commandBuffer.length() > 0) {
        processCommand(commandBuffer);
        commandBuffer = "";
      }
    } else {
      // Add character to buffer
      commandBuffer += c;
    }
  }
}

// ====================================================
// PROCESS SERIAL COMMANDS
// ====================================================
void processCommand(String cmd) {
  cmd.trim(); // Remove whitespace
  
  // Convert to uppercase for case-insensitive comparison
  String upperCmd = cmd;
  upperCmd.toUpperCase();
  
  // Debug: Uncomment to see received commands
  // Serial.print("CMD: ");
  // Serial.println(cmd);
  
  // --- SET THRESHOLD COMMAND ---
  if (upperCmd.startsWith("THRESHOLD=")) {
    String valueStr = cmd.substring(10);
    valueStr.trim();
    
    float newThreshold = valueStr.toFloat();
    
    if (newThreshold >= 0 && newThreshold <= 100) {
      alarmThreshold = newThreshold;
      
      Serial.print("OK - Threshold set to ");
      Serial.print(alarmThreshold, 1);
      Serial.println("°C");
      
      Serial.print("Current: ");
      Serial.print(temperature, 1);
      Serial.print("°C - ");
      Serial.println(temperature >= alarmThreshold ? "ALARM" : "NORMAL");
    } else {
      Serial.println("ERROR - Threshold must be 0-100°C");
    }
  }
  
  // --- GET TEMPERATURE COMMAND ---
  else if (upperCmd == "TEMP?" || upperCmd == "TEMP") {
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.println(" °C");
  }
  
  // --- GET THRESHOLD COMMAND ---
  else if (upperCmd == "THRESHOLD?" || upperCmd == "THRESHOLD") {
    Serial.print("Alarm Threshold: ");
    Serial.print(alarmThreshold, 1);
    Serial.println(" °C");
  }
  
  // --- GET STATUS COMMAND ---
  else if (upperCmd == "STATUS") {
    Serial.println("=== SYSTEM STATUS ===");
    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.println("°C");
    
    Serial.print("Threshold:  ");
    Serial.print(alarmThreshold, 1);
    Serial.println("°C");
    
    Serial.print("State:      ");
    if (temperature >= alarmThreshold) {
      Serial.print("ALARM");
      if (temperature >= alarmThreshold + 10) {
        Serial.println(" (SEVERE)");
      } else {
        Serial.println(" (MODERATE)");
      }
    } else {
      Serial.println("NORMAL");
    }
    
    Serial.print("LEDs:       Green=");
    Serial.print(digitalRead(GREEN_LED) ? "ON" : "OFF");
    Serial.print(", Red=");
    Serial.println(digitalRead(RED_LED) ? "ON" : "OFF");
    
    Serial.print("Buzzer:     ");
    Serial.println(digitalRead(BUZZER) ? "ON" : "OFF");
    Serial.println("=====================");
  }
  
  // --- HELP COMMAND ---
  else if (upperCmd == "HELP" || upperCmd == "?") {
    Serial.println("=== AVAILABLE COMMANDS ===");
    Serial.println("THRESHOLD=XX.X  Set alarm (0-100°C)");
    Serial.println("TEMP?           Get temperature");
    Serial.println("THRESHOLD?      Get alarm threshold");
    Serial.println("STATUS          Get full system status");
    Serial.println("HELP            Show this help");
    Serial.println("TEST            Test LEDs & buzzer");
    Serial.println("RESET           Reset to defaults");
    Serial.println("==========================");
  }
  
  // --- TEST COMMAND ---
  else if (upperCmd == "TEST") {
    Serial.println("Testing hardware...");
    
    // Test sequence
    Serial.println("1. Green LED ON");
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    delay(1000);
    
    Serial.println("2. Red LED ON");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    delay(1000);
    
    Serial.println("3. Buzzer ON");
    digitalWrite(BUZZER, HIGH);
    delay(500);
    
    Serial.println("4. Buzzer OFF");
    digitalWrite(BUZZER, LOW);
    delay(500);
    
    Serial.println("5. All OFF");
    digitalWrite(RED_LED, LOW);
    delay(500);
    
    Serial.println("6. Normal state");
    digitalWrite(GREEN_LED, HIGH);
    Serial.println("Test complete!");
  }
  
  // --- RESET COMMAND ---
  else if (upperCmd == "RESET") {
    alarmThreshold = 60.0;
    Serial.println("System reset to defaults");
    Serial.print("Alarm threshold: ");
    Serial.print(alarmThreshold, 1);
    Serial.println("°C");
  }
  
  // --- UNKNOWN COMMAND ---
  else if (cmd.length() > 0) {
    Serial.print("Unknown command: ");
    Serial.println(cmd);
    Serial.println("Type 'HELP' for command list");
  }
}

// ====================================================
// ADDITIONAL UTILITY FUNCTIONS (Optional)
// ====================================================

// Function to get raw sensor reading (no smoothing)
float getRawTemperature() {
  int raw = analogRead(LM35_PIN);
  return raw * 0.48828125;
}

// Function to convert Celsius to Fahrenheit
float celsiusToFahrenheit(float celsius) {
  return (celsius * 9.0 / 5.0) + 32.0;
}

// Function to print sensor calibration info
void printCalibration() {
  Serial.println("=== Calibration Info ===");
  Serial.print("Room Temp (approx): ");
  Serial.print(temperature, 1);
  Serial.println("°C");
  
  Serial.print("Raw ADC Value: ");
  Serial.println(analogRead(LM35_PIN));
  
  float voltage = (analogRead(LM35_PIN) * 5.0) / 1023.0;
  Serial.print("Voltage: ");
  Serial.print(voltage, 3);
  Serial.println("V");
  Serial.println("======================");
}

// ====================================================
// END OF CODE
// ====================================================