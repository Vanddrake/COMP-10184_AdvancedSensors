// I, Robert Zaranek, 001161598 certify that this material is my original work.
// No other person's work has been used without due acknowledgement.

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>
// Pin that the DS18B20 is connected to
const int oneWireBus = D3;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);
// DS18B20 sensor serial address
DeviceAddress sensor;
// Error message printed flag
bool errorMessagePrinted = false;

void setup() {
  // configure the USB serial monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  DS18B20.begin();
  
  if (!DS18B20.getAddress(sensor, 0))
  {
    Serial.println("\n\nNo DS18B20 temperature sensor installed!");
    errorMessagePrinted = true;
  } else {
    Serial.print("\n\nFound DS18B20 sensor with address: ");
    for (uint8_t i = 0; i < 8; i++)
    {
      Serial.print(sensor[i], HEX);
    }
    Serial.println();
  }
}

void loop() {
  if (!errorMessagePrinted && !DS18B20.getAddress(sensor, 0)){
    Serial.println("No DS18B20 temperature sensor installed!");
    errorMessagePrinted = true;
  }

  if (DS18B20.getAddress(sensor, 0))
  {
    errorMessagePrinted = false;
    float fTemp;
    String tempJudgement;
    // ask DS18B20 for the current temperature
    DS18B20.requestTemperatures();
    // fetch the temperature. We only have 1 sensor, so the index is 0.
    fTemp = DS18B20.getTempCByIndex(0);
    // make judgement based on tempurature calculation
    if (fTemp < 10) {
      tempJudgement = "Cold!";
    } else if (fTemp >= 10 && fTemp <= 15) {
      tempJudgement = "Cool";
    } else if (fTemp >= 15 && fTemp <= 25) {
      tempJudgement = "Perfect";
    } else if (fTemp >= 25 && fTemp <= 30) {
      tempJudgement = "Warm";
    } else if (fTemp >= 30 && fTemp <= 35) {
      tempJudgement = "Hot";
    } else if (fTemp > 35) {
      tempJudgement = "Too Hot!";
    }
    // print the temp to the USB serial monitor
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + tempJudgement);
  }
  // wait 2s (2000ms) before doing this again
  delay(2000);
}