#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

class EEPROMManager {
public:
  EEPROMManager();

  // Functions to read and write float values
  float readFloat(int index);
  void writeFloat(int index, float value);

  // Functions to read and write int values
  int readInt(int index);
  void writeInt(int index, int value);

private:
  int address;
};

#endif  // EEPROM_MANAGER_H
