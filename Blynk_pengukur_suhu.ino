
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID           "TMPL3hpengtc"
#define BLYNK_DEVICE_NAME           "Pemantau 1"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
#define USE_WEMOS_D1_MINI

#define HIJAU 12
#define KUNING 13
#define MERAH 15

#include "BlynkEdgent.h"

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

BlynkTimer timer;

float temp, humid;

void setup()
{
  Serial.begin(115200);

  pinMode(HIJAU, OUTPUT);
  pinMode(KUNING, OUTPUT);
  pinMode(MERAH, OUTPUT);

  dht.begin();
  BlynkEdgent.begin();

  lcd.init();
  lcd.backlight();

  timer.setInterval(2000L, myTimerEvent);
  digitalWrite(HIJAU, 1);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}

void myTimerEvent()
{
  temp = dht.readTemperature();
  humid = dht.readHumidity();

  if (isnan(temp) || isnan(humid)) {
    Serial.println(F("Gagal Membaca Sensor!"));
    return;
  }

  Serial.print(F(" Temp: "));
  Serial.print(temp);
  Serial.print(F(" C  Humid: "));
  Serial.print(humid);
  Serial.print(F("%"));

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(6, 0);
  lcd.print(temp);
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.setCursor(7, 1);
  lcd.print(humid);

  if (temp > 32) {
    digitalWrite(MERAH, 1);
  } else {
    digitalWrite(MERAH, 0);
  }
  if (temp > 30) {
    digitalWrite(KUNING, 1);
  } else {
    digitalWrite(KUNING, 0);
  }

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, humid);
}
