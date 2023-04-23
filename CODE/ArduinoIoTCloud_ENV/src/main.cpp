#include "thingProperties.h"
#include <Adafruit_BMP280.h>
#include <Adafruit_SHT31.h>

Adafruit_BMP280 bmp;
Adafruit_SHT31 sht;

#define FLASH_EN_PIN 25

float LED_POWER = 0;

void unit_flash_set_brightness(float brightness)
{
  if ((brightness >= 1) && (brightness <= 16))
  {
    for (int i = 0; i < brightness; i++)
    {
      digitalWrite(FLASH_EN_PIN, LOW);
      delayMicroseconds(4);
      digitalWrite(FLASH_EN_PIN, HIGH);
      delayMicroseconds(4);
    }
  }
  else
  {
    digitalWrite(FLASH_EN_PIN, LOW);
  }
}

void setup()
{
  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  Wire.begin(25, 26); // Inialize I2C Hardware

  if (!bmp.begin(0x76))
  {
    Serial.println("ENV: Could not find a valid BMP280 sensor, check wiring!");
  }
  if (!sht.begin(0x44))
  {
    Serial.println("ENV2: Could not find a valid SHT3X sensor, check wiring!");
  }
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  // pinMode(FLASH_EN_PIN, OUTPUT);
  // digitalWrite(FLASH_EN_PIN, LOW);
  // pwmの設定。最初の引数がchannel,次が周波数,最後が解像度（ここでは8bit = 256段階）
  ledcSetup(0, 12800, 8);
  // ピンをチャンネルに接続
  ledcAttachPin(FLASH_EN_PIN, 0);
}

void loop()
{
  ArduinoCloud.update();
  // Your code here
  Serial.println(LED_POWER);
  PRESS = bmp.readPressure() / 100;
  TEMP = sht.readTemperature();
  HUM = sht.readHumidity();

  Serial.print(TEMP);
  Serial.print("\t");
  Serial.print(HUM);
  Serial.print("\t");
  Serial.println(PRESS);

  delay(100);
}

void onTEMPChange()
{
  // Add your code here to act upon TEMP change
}

/*
  Since HUM is READ_WRITE variable, onHUMChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHUMChange()
{
  // Add your code here to act upon HUM change
}

/*
  Since PRESS is READ_WRITE variable, onPRESSChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPRESSChange()
{
  // Add your code here to act upon PRESS change
}
