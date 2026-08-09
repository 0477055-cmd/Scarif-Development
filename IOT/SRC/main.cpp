#include <Arduino.h>

// Set a unique identifier for your device before importing comms.h
const char *mqttClient = "ESP32_Michael_L"; // EDIT THIS FIELD

const char *mqttTopic;

#include <Arduino.h>
#include "comms.h"

void performActionBasedOnPayload(String payload)
{
    Serial.print("Payload received: ");
    Serial.println(payload);

    // Turn built-in LED ON if payload starts with '1', else OFF
    if (payload.length() > 0 && payload[0] == '1')
    {
        Serial.println("Action: LED ON");
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        Serial.println("Action: LED OFF");
        digitalWrite(LED_BUILTIN, LOW);
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    
    wifiSetup();
    mqttSetup();

    while (!Serial)
    {
        delay(10);
    }
    delay(1000);

    randomSeed(analogread(a0)); // seed using an unconnected analog pin for real random
}

void loop()
{
    // 1. Maintain connection to the broker
    mqttConnect();

    // 2. Transmit periodic telemetry (if required by design specification)
   int randomNumber = random(1, 10001);
   sendPeriodicUpdate("sensorData", String(randomNumber));

    client.loop(); // Check for incomign messages and keep the connection alive
    delay(100);
}