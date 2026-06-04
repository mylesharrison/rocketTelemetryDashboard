#include<Arduino.h>
#ifndef LOGGER_H
#define LOGGER_H

void setupLogger();
void logTelemetryCSV(String row);

#endif