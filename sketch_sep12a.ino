#include <Arduino.h>

class RFIDVehicleDetector {
private:
    int maxSpeedLimit;
    bool running;

public:
    // Constructor
    RFIDVehicleDetector(int speedLimit) {
        maxSpeedLimit = speedLimit;
        running = true;
    }

    // Read RFID function
    void readRFID() {
        String rfidData = getRandomRFID();
        if (rfidData == "INVALID_RFID") {
            Serial.println("Error: Invalid RFID read");
        } else {
            log("RFID Read: " + rfidData);
            processVehicle(rfidData);
        }
    }

    // Measure speed function
    void measureSpeed() {
        int speed = getRandomSpeed();
        log("Measured Speed: " + String(speed) + " km/h");
        if (checkSpeed(speed)) {
            handleViolation("VALID_RFID", speed);
        }
    }

    // Check if speed exceeds limit
    bool checkSpeed(int speed) {
        if (speed > maxSpeedLimit) {
            log("Speed violation detected: " + String(speed) + " km/h over limit of " + String(maxSpeedLimit) + " km/h");
            return true;
        }
        return false;
    }

    // Stop the detector
    void stop() {
        running = false;
    }

    // Check if detector is running
    bool isRunning() {
        return running;
    }

    // Log messages with timestamp
    void log(String message) {
        Serial.println(getCurrentTime() + ": " + message);
    }

    // Process vehicle after RFID read
    void processVehicle(String rfid) {
        measureSpeed();
    }

    // Handle speed violations
    void handleViolation(String rfid, int speed) {
        log("Vehicle with RFID " + rfid + " exceeded speed limit. Speed: " + String(speed) + " km/h");
    }

    // Generate random RFID (simulation)
    String getRandomRFID() {
        int randomValue = random(0, 2);
        if (randomValue == 0) {
            return "VALID_RFID";
        } else {
            return "INVALID_RFID";
        }
    }

    // Generate random speed between 30-100 km/h
    int getRandomSpeed() {
        return random(30, 101);
    }

    // Get current time in seconds
    String getCurrentTime() {
        return String(millis() / 1000) + "s";
    }
};

// Create detector instance with 60 km/h speed limit
RFIDVehicleDetector detector(60);

void setup() {
    // Initialize Serial communication
    Serial.begin(9600);
    delay(2000);
    Serial.println("Vehicle detection system started.");
    
    // Initialize random seed
    randomSeed(analogRead(0));
}

void loop() {
    if (detector.isRunning()) {
        detector.readRFID();
        delay(1000);  // Wait 1 second
    }
}