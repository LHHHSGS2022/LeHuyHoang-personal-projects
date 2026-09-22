#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// MQ Sensors
#define MQ1_PIN 32
#define MQ2_PIN 33
#define MQ3_PIN 25

// DHT22
#define DHTPIN 26
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // OLED INIT
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed!");
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  
  dht.begin();
}

void loop() {

  // Đọc MQ sensors (ADC 0–4095 → ESP32)
  int mq1 = analogRead(MQ1_PIN);
  int mq2 = analogRead(MQ2_PIN);
  int mq3 = analogRead(MQ3_PIN);

  // Đọc DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  display.clearDisplay();
  display.setCursor(0, 0);

  display.println("   ESP32 SENSOR DATA");
  display.println("-----------------------");

  // MQ values
  display.print("MQ1 (A32): ");
  display.println(mq1);

  display.print("MQ2 (A33): ");
  display.println(mq2);

  display.print("MQ3 (A25): ");
  display.println(mq3);

  // DHT22 values
  if (isnan(h) || isnan(t)) {
    display.println("DHT22 ERROR!");
  } else {
    display.print("Temp: ");
    display.print(t);
    display.println(" C");

    display.print("Humi: ");
    display.print(h);
    display.println(" %");
  }

  display.display();

  delay(1000);
}
