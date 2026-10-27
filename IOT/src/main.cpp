// MQTT client name
// TODO - Change the name to the specific module name.
const char *mqttClient = "ESP32-Michael.l"; // Must be unique for each ESP32

#include <Arduino.h>
#include "comms.h"

#include <Wire.h>
#include "Adafruit_ADT7410.h"

// Create the ADT7410 temperature sensor object
Adafruit_ADT7410 tempsensor = Adafruit_ADT7410();

#define ledRed 13
#define ledYellow 12
#define ledGreen 27

void performActionBasedOnPayload(String payload)
{
    Serial.print("Payload: ");
    Serial.println(payload);

    if (payload.charAt(0) == '1')
    {
        Serial.println("LED ON");

        digitalWrite(ledRed, HIGH);
        delay(10000);

        digitalWrite(ledGreen, HIGH);
        delay(10000);

        digitalWrite(ledYellow, HIGH);
        delay(2000);
    }
    else
    {
        digitalWrite(ledRed, LOW);
        digitalWrite(ledYellow, LOW);
        digitalWrite(ledGreen, LOW);
    }
}

void setup()
{
    pinMode(ledRed, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    pinMode(ledGreen, OUTPUT);

    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);

    Serial.begin(9600);

    while (!Serial)
    {
        delay(10);
    }

    Serial.println("Starting ESP32...");

    wifiSetup();
    mqttSetup();

    delay(1000);

    // Seed the random number generator
    randomSeed(esp_random());

    // Make sure the ADT7410 temperature sensor is found
    // Use tempsensor.begin(0x49) if your sensor uses a different I2C address
    if (!tempsensor.begin())
    {
        Serial.println("Couldn't find ADT7410!");
        while (1)
        {
            delay(1000);
        }
    }

    // Give the sensor time to take its first measurement
    delay(250);

    Serial.println("ADT7410 initialised.");
}

void loop()
{
    // Keep the MQTT connection alive and process incoming messages
    mqttConnect();
    client.loop();

    // sendPeriodicUpdate() only sends once every 5 seconds
    int randomNumber = random(1, 100001);
    sendPeriodicUpdate(String("sensorData"), String(randomNumber));

    // Read the temperature sensor
    float tempInC = tempsensor.readTempC();

    Serial.print("Temperature: ");
    Serial.print(tempInC);
    Serial.println(" C");

    // Send temperature using the same 5-second periodic update system
    sendPeriodicUpdate(String("temperature"), String(tempInC, 2));

    delay(100);
}