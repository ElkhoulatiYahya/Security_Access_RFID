#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void setup() {
  Serial.begin(9600);
  while (!Serial); // attendre l'ouverture du moniteur série (utile sur certains boards)
  SPI.begin();     // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

void loop() {
  // Look for new cards
  if (! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Construire l'UID sous forme "BD 31 15 2B" (2 hex par octet, majuscules, séparés par espaces)
  String uidStr = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) uidStr += "0"; // leading zero si nécessaire
    uidStr += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) uidStr += " ";
  }
  uidStr.toUpperCase();

  Serial.print("UID tag : ");
  Serial.println(uidStr);

  // Liste des UID autorisés (tu peux en ajouter d'autres)
  // Exemple : "BD 31 15 2B"
  const char* allowedUIDs[] = {
    "BD 31 15 2B",
    // "AA BB CC DD", // autre UID
  };
  const size_t allowedCount = sizeof(allowedUIDs) / sizeof(allowedUIDs[0]);

  bool authorized = false;
  for (size_t k = 0; k < allowedCount; ++k) {
    if (uidStr == String(allowedUIDs[k])) {
      authorized = true;
      break;
    }
  }

  if (authorized) {
    Serial.println("Authorized access");
    // ici : actions supplémentaires (ex: ouvrir relais)
  } else {
    Serial.println("Access denied");
  }

  Serial.println();
  delay(3000); // délai pour éviter multiple lectures rapides
}
