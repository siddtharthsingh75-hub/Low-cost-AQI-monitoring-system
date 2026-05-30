#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define MQ135_PIN   A0
#define DHT_PIN     4
#define DHT_TYPE    DHT11
#define BUZZER_PIN  8
#define LED_GREEN   9
#define LED_YELLOW  10
#define LED_RED     11

#define AQ_SAFE      300
#define AQ_MODERATE  500
#define TEMP_HIGH    35.0

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHT_TYPE);

float lastTemp = 0;
float lastHumidity = 0;
int lastAlertLevel = -1;

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED,    OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_GREEN,  LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED,    LOW);

  Wire.begin();
  delay(100);
  lcd.init();
  delay(100);
  lcd.backlight();
  delay(100);

  lcd.setCursor(0, 0);
  lcd.print("Air Quality Mon.");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  dht.begin();
  delay(3000);
  lcd.clear();
}

void setAlert(int level) {
  digitalWrite(LED_GREEN,  LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED,    LOW);
  digitalWrite(BUZZER_PIN, LOW);

  if (level == 0) {
    digitalWrite(LED_GREEN, HIGH);
  } else if (level == 1) {
    digitalWrite(LED_YELLOW, HIGH);
  } else {
    digitalWrite(LED_RED,    HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  }
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(t) && !isnan(h)) {
    lastTemp     = t;
    lastHumidity = h;
  }

  int aqRaw = analogRead(MQ135_PIN);

  int alertLevel;
  String aqStatus;

  if (aqRaw < AQ_SAFE) {
    alertLevel = 0;
    aqStatus   = "SAFE    ";
  } else if (aqRaw < AQ_MODERATE) {
    alertLevel = 1;
    aqStatus   = "MODERATE";
  } else {
    alertLevel = 2;
    aqStatus   = "DANGER! ";
  }

  if (lastTemp > TEMP_HIGH && alertLevel < 2) {
    alertLevel = 2;
    aqStatus   = "HOT!    ";
  }

  setAlert(alertLevel);

  // Only clear LCD when alert level changes to avoid flicker
  if (alertLevel != lastAlertLevel) {
    lcd.clear();
    lastAlertLevel = alertLevel;
  }

  lcd.setCursor(0, 0);
  lcd.print("AQ:");
  lcd.print(aqRaw);
  lcd.print(" ");
  lcd.print(aqStatus);

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(lastTemp, 1);
  lcd.print("C H:");
  lcd.print(lastHumidity, 0);
  lcd.print("%  ");

  Serial.print("AQ: ");        Serial.print(aqRaw);
  Serial.print(" | Temp: ");   Serial.print(lastTemp);
  Serial.print("C | Hum: ");   Serial.print(lastHumidity);
  Serial.println("%");

  delay(2500);
}