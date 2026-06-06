#include<Arduino.h>
#ifndef LORA_RADIO_H
#define LORA_RADIO_H

bool initLoRa();
bool sendLoRaPacket(const String& message);

#endif