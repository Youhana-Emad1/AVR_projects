const int LM35_PIN = A5;        // LM35 connected to analog pin A5
const int RED_LED = 10;         // Red LED on pin 10
const int GREEN_LED = 11;       // Green LED on pin 11
const int BUZZER = 8;           // Buzzer on pin 8

// Temperature thresholds (adjust as needed)
float TEMP_LOW_THRESHOLD = 20.0;   // Below this is "cold"
float TEMP_HIGH_THRESHOLD = 30.0;  // Above this is "hot"
float TEMP_CRITICAL_THRESHOLD = 35.0; // Critical temperature

// Variables for serial communication
String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(115200);         // Higher baud rate for better communication
  pinMode(LM35_PIN, INPUT);     // LM35 is analog input
  pinMode(RED_LED, OUTPUT);     // Set red LED as output
  pinMode(GREEN_LED, OUTPUT);   // Set green LED as output
  pinMode(BUZZER, OUTPUT);      // Set buzzer as output
  
  // Turn off LEDs and buzzer initially
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER, LOW);
  
  // Reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  Serial.println("=== LM35 Temperature Monitoring System ===");
  Serial.println("Commands:");
  Serial.println("  THRESH:<low>:<high>:<critical> - Set thresholds");
  Serial.println("  STATUS - Get current status");
  Serial.println("  HELP - Show this help");
  Serial.println("===========================================");
  Serial.println();
}

void loop() {
  // Handle serial commands
  if (stringComplete) {
    processCommand(inputString);
    inputString = "";
    stringComplete = false;
  }
  
  // Read and process temperature
  readTemperature();
  
  delay(1000);  // Wait 1 second between readings
}

void readTemperature() {
  // Read LM35 sensor value (average of 10 readings for stability)
  long sensorValue = 0;
  for (int i = 0; i < 10; i++) {
    sensorValue += analogRead(LM35_PIN);
    delay(10);
  }
  sensorValue = sensorValue / 10;
  
  // Convert to voltage (assuming 5V reference)
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Convert voltage to temperature (10mV per °C)
  float temperature = voltage * 100;
  
  // Send temperature data to Serial
  Serial.print("TEMP:");
  Serial.print(temperature, 2);  // 2 decimal places
  Serial.print("|RAW:");
  Serial.print(sensorValue);
  Serial.print("|V:");
  Serial.print(voltage, 3);
  Serial.print("|LOW:");
  Serial.print(TEMP_LOW_THRESHOLD, 1);
  Serial.print("|HIGH:");
  Serial.print(TEMP_HIGH_THRESHOLD, 1);
  Serial.print("|CRIT:");
  Serial.print(TEMP_CRITICAL_THRESHOLD, 1);
  Serial.print("|LEDS:");
  
  // Control LEDs and buzzer based on temperature
  if (temperature < TEMP_LOW_THRESHOLD) {
    // Cold - Green LED ON, Red OFF, Buzzer OFF
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("GREEN");
  } 
  else if (temperature >= TEMP_LOW_THRESHOLD && temperature <= TEMP_HIGH_THRESHOLD) {
    // Normal - Both LEDs OFF, Buzzer OFF
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    Serial.print("OFF");
  }
  else if (temperature > TEMP_HIGH_THRESHOLD && temperature <= TEMP_CRITICAL_THRESHOLD) {
    // Hot - Red LED ON, Green OFF, Buzzer OFF
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, LOW);
    Serial.print("RED");
  }
  else {
    // Critical - Red LED blinking, Buzzer beeping
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Serial.print("RED-BLINK");
    
    // Buzzer beep pattern for critical temperature
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    delay(100);
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
  }
  
  Serial.print("|STATUS:");
  if (temperature < TEMP_LOW_THRESHOLD) {
    Serial.println("COLD");
  } else if (temperature <= TEMP_HIGH_THRESHOLD) {
    Serial.println("NORMAL");
  } else if (temperature <= TEMP_CRITICAL_THRESHOLD) {
    Serial.println("HOT");
  } else {
    Serial.println("CRITICAL!");
  }
}

void processCommand(String command) {
  command.trim();
  
  if (command == "STATUS") {
    Serial.println("=== SYSTEM STATUS ===");
    Serial.print("Low Threshold: "); Serial.println(TEMP_LOW_THRESHOLD);
    Serial.print("High Threshold: "); Serial.println(TEMP_HIGH_THRESHOLD);
    Serial.print("Critical Threshold: "); Serial.println(TEMP_CRITICAL_THRESHOLD);
    Serial.println("====================");
  }
  else if (command.startsWith("THRESH:")) {
    // Format: THRESH:low:high:critical
    int firstColon = command.indexOf(':');
    int secondColon = command.indexOf(':', firstColon + 1);
    int thirdColon = command.indexOf(':', secondColon + 1);
    
    if (firstColon != -1 && secondColon != -1 && thirdColon != -1) {
      float low = command.substring(firstColon + 1, secondColon).toFloat();
      float high = command.substring(secondColon + 1, thirdColon).toFloat();
      float critical = command.substring(thirdColon + 1).toFloat();
      
      if (low < high && high < critical) {
        TEMP_LOW_THRESHOLD = low;
        TEMP_HIGH_THRESHOLD = high;
        TEMP_CRITICAL_THRESHOLD = critical;
        Serial.print("Thresholds updated: LOW=");
        Serial.print(low);
        Serial.print(" HIGH=");
        Serial.print(high);
        Serial.print(" CRITICAL=");
        Serial.println(critical);
      } else {
        Serial.println("ERROR: Thresholds must be in order LOW < HIGH < CRITICAL");
      }
    } else {
      Serial.println("ERROR: Invalid THRESH command format");
      Serial.println("Use: THRESH:low:high:critical");
    }
  }
  else if (command == "HELP" || command == "?") {
    Serial.println("=== HELP ===");
    Serial.println("THRESH:<low>:<high>:<critical> - Set temperature thresholds");
    Serial.println("STATUS - Show current system status");
    Serial.println("HELP or ? - Show this help message");
    Serial.println("===========");
  }
  else if (command.length() > 0) {
    Serial.print("Unknown command: ");
    Serial.println(command);
    Serial.println("Type HELP for available commands");
  }
}

// Serial event for non-blocking command reading
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}