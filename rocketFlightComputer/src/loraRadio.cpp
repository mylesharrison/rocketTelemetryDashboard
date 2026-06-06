#include <Arduino.h>
#include <RadioLib.h>
#include "loraRadio.h"

SX1262 radio = new Module(8, 14, 12, 13);

bool initLoRa(){
    int state = radio.begin(915.0);

    if (state == RADIOLIB_ERR_NONE){
        Serial.println("LoRa init success");
        return true;
    }

    Serial.print("LoRa init failed: ");
    Serial.println(state);
    return false;
}

bool sendLoRaPacket(const String& message){
    int state = radio.transmit(message.c_str());

    if (state == RADIOLIB_ERR_NONE){
        return true;
    }

    Serial.print("LoRa send failed: ");
    Serial.println(state);
    return false;
}