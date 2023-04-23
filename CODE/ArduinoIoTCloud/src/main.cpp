#include "thingProperties.h"

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
  ledcWrite(0, LED_POWER);
  delay(10);
}

void onLEDSWITCHChange()
{
  // Add your code here to act upon LEDSWITCH change
}

void onLEDTEST2Change()
{
  // Add your code here to act upon LEDTEST2 change
  // digitalWrite(FLASH_EN_PIN, LED_TEST2);
  LED_POWER = LED_TEST2;
}
