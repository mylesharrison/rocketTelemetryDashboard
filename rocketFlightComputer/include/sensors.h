#include <Arduino.h>
#ifndef SENSORS_H
#define SENSORS_H

bool setupMPU();
bool setupBME();

String getTelemetryCSV();

void printMPUData();
void printBMEData();

#endif