#include "control.h"

void toggleLed()
{
    String ledTopic =
        "controller/" + String(config.code) + "/led/response";

    config.ledState = !config.ledState;
    digitalWrite(config.ledPin, config.ledState ? HIGH : LOW);
    Serial.print("LED: ");
    Serial.print(config.ledPin);
    Serial.print(" [");
    Serial.print(config.ledState ? "ON" : "OFF");
    Serial.println("]");
    mqttClient.publish(ledTopic.c_str(), config.ledState ? "turn on" : "turn off");
}