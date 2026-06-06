#include<Arduino.h>
#ifndef LOGGER_H
#define LOGGER_H

bool setupLogger();
void logTelemetryCSV(const String& row);

#endif