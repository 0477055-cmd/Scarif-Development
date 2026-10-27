/*
This file contains the communication logic for the development module, including MQTT setup, message handling, and periodic updates.

DO NOT CHANGE ANYTHING IN THIS FILE UNLESS YOU KNOW WHAT YOU ARE DOING, AS THIS FILE CONTAINS THE CORE COMMUNICATION LOGIC FOR THE MODULE.
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include "sensitiveInformation.h" // ENSURE WIFI & MQTT IS CONFIGURED CORRECTLY

// MQTT client setup
WiFiClient espClient;
PubSubClient client(espClient);

// MQTT topic is now a String, which safely stores dynamically created topics
String mqttTopic;

// Replace with the MQTT broker IP address and port
// Default MQTT port is normally 1883
const char* mqttServer = "192.168.1.116";
const int mqttPort = 5883;

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 5000; // Time between periodic updates: 5 seconds

void performActionBasedOnPayload(String payload);

void wifiSetup()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println();
    Serial.print("Connected to WiFi. IP address: ");
    Serial.println(WiFi.localIP());
}

/*
  Use this to send data back to the MQTT broker.
  Example usage: sendDataToServer("challenges/Status", "Task Completed");
*/
void sendDataToServer(String topic, String message)
{
    if (client.connected())
    {
        Serial.print("Sending message to topic [");
        Serial.print(topic);
        Serial.print("]: ");
        Serial.println(message);

        client.publish(topic.c_str(), message.c_str());
    }
    else
    {
        Serial.println("Send failed: MQTT not connected.");
    }
}

void sendPeriodicUpdate(String topic, String dataToSend)
{
    // Only send once every updateInterval milliseconds
    unsigned long now = millis();

    if (now - lastUpdate >= updateInterval)
    {
        lastUpdate = now;

        // Construct the special update topic
        String updateTopic = topic + "/" + String(mqttClient);

        // Send the data to the broker
        sendDataToServer(updateTopic, dataToSend);
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String message = "";

    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    String internalPrefix = "__INTERNAL__";

    if (message.startsWith(internalPrefix))
    {
        message = message.substring(internalPrefix.length());
    }

    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println(message);

    performActionBasedOnPayload(message);
}

void mqttConnect()
{
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");

        if (client.connect(mqttClient))
        {
            Serial.println("Connected to MQTT");

            // Subscribe to this ESP32's command topic
            client.subscribe(mqttTopic.c_str());

            // Send an online message to the event log
            String eventTopic = "EventLog/" + String(mqttClient);
            sendDataToServer(eventTopic, String(mqttClient) + " is online.");
        }
        else
        {
            Serial.print("Failed with state ");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

void mqttSetup()
{
    // Construct the MQTT topic dynamically
    mqttTopic = "devicePayload/" + String(mqttClient);

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    mqttConnect();
}