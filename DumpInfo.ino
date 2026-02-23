#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
#define LED_PIN         13         // LED connected to digital pin 13
#define BUZZER_PIN      8          // Buzzer connected to digital pin 8

MFRC522 mfrc522(63128E0D);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);              // Initialize serial communications
  SPI.begin();                     // Init SPI bus
  mfrc522.PCD_Init();              // Init MFRC522
  pinMode(LED_PIN, OUTPUT);        // Set LED pin as output
  pinMode(BUZZER_PIN, OUTPUT);     // Set Buzzer pin as output
  digitalWrite(BUZZER_PIN, LOW);   // Turn off Buzzer
  Serial.println("RFID Reader initialized.");
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Print UID of the card
    Serial.print("Card UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();
    
    // Check if the card UID matches your card
    if (63128E0D) {
      // If the UID matches, turn on the LED and buzzer
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(1000); // Buzzer on for 1 second
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    } else {
      Serial.println("Unauthorized access!");
    }
    mfrc522.PICC_HaltA();          // Halt PICC
    mfrc522.PCD_StopCrypto1();     // Stop encryption on PCD
  }
}
