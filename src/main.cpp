#include <Arduino.h>
#include <GyverBME280.h>
#include <Wire.h>
  
unsigned long lastDataTime = 0;
const int samplingInterval = 1000;

GyverBME280 bme;
bool sensorOK = false;

void initBME280() {
  sensorOK = bme.begin();
  if (sensorOK) {
    Serial.println("Đã khởi tạo BME280 thành công!");
    bme.setHumOversampling(MODULE_DISABLE);
    bme.setStandbyTime(STANDBY_1000MS);
  }
  else {
    Serial.println("Không tìm thấy BME280!");
  }
}

void setup(){
  Serial.begin(115200);
  Wire.begin();

  initBME280();
}

void loop() {
  if (!sensorOK) {
    initBME280();
    delay(1000);
    return;
}

  unsigned long currentTime = millis();

  if (currentTime - lastDataTime >= samplingInterval) {
    lastDataTime = currentTime;

    float temp = bme.readTemperature();
    float hum = bme.readHumidity();
    float press = bme.readPressure();

    if(temp == 0 && hum == 0 && press == 0) {
      Serial.println("Cảm biến mất kết nối!");
      sensorOK = false;
      return;
    }

    Serial.print("Temperature: ");
    Serial.print(bme.readTemperature());      
    Serial.println(" *C");
  
    Serial.print("Pressure: ");
    Serial.print(bme.readPressure());
    Serial.println(" Pa");

    Serial.print("Humidity: ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    Serial.println("------------------------");
  }
}