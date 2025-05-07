#include <Arduino.h>
#include <GyverBME280.h>
#include <Wire.h>
  
unsigned long lastDataTime = 0;
const int samplingInterval = 1000;

GyverBME280 bme;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  bme.setHumOversampling(MODULE_DISABLE);       
  bme.setStandbyTime(STANDBY_1000MS);            
  bme.begin(); 
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastDataTime >= samplingInterval) {
    lastDataTime = currentTime;
    Serial.print("Temperature: ");
    Serial.print(bme.readTemperature());      
    Serial.println(" *C");
  
    Serial.print("Pressure: ");
    Serial.print(bme.readPressure());
    Serial.println(" Pa");
    Serial.println("");
  }
}