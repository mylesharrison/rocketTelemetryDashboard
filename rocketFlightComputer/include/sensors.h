#include <Arduino.h>
#ifndef SENSORS_H
#define SENSORS_H

void setupMPU();
void setupBME();

String getTelemetryCSV();

void printMPUData();
void printBMEData();

#endif