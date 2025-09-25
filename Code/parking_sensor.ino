#include "DHT.h"
#include <Wire.h>         // Bibliothèque pour la communication I2C
#include <LiquidCrystal_I2C.h> // Bibliothèque pour l'écran LCD i2C

// Configuration du capteur DHT11
#define DHTPIN 2          // Pin connectée à la broche DATA du capteur
#define DHTTYPE DHT11     // Type de capteur : DHT11

DHT dht(DHTPIN, DHTTYPE); // Initialisation de l'objet DHT

// Configuration de l'écran LCD (adresse i2C, colonnes, lignes)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);      // Initialisation de la communication série
  dht.begin();             // Initialisation du capteur DHT11
  lcd.init();              // Initialisation de l'écran LCD
  lcd.backlight();         // Activer le rétroéclairage de l'écran
  lcd.setCursor(0, 0);     // Positionnement du curseur sur la première ligne
  lcd.print("Initialisation"); 
  delay(2000);             // Pause pour afficher le message d'accueil
  lcd.clear();             // Efface l'écran avant le début des mesures
}

void loop() {
  // Lecture des données du capteur
  float temp = dht.readTemperature(); // Lecture de la température en Celsius
  float hum = dht.readHumidity();     // Lecture de l'humidité en %

  // Vérification des erreurs
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Erreur : Données invalides du capteur !");
    lcd.setCursor(0, 0);
    lcd.print("Erreur capteur !");
    lcd.setCursor(0, 1);
    lcd.print("Verifiez liaison");
  } else {
    // Affichage des mesures sur le Moniteur Série
    Serial.println("Température : " + String(temp) + " °C");
    Serial.println("Humidité : " + String(hum) + " %");

    // Affichage des mesures sur l'écran LCD
    lcd.setCursor(0, 0); // Position sur la première ligne
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print(" C");
    lcd.setCursor(0, 1); // Position sur la deuxième ligne
    lcd.print("Hum: ");
    lcd.print(hum);
    lcd.print(" %");
  }

  // Pause de 10 secondes avant la prochaine lecture
  delay(10000);
}

