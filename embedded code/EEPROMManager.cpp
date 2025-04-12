#include "EEPROMManager.h"

EEPROMManager::EEPROMManager()
  : address(0) {}

float EEPROMManager::readFloat(int index) {
  float value = 0.0;
  byte* p = (byte*)(void*)&value;

  for (int i = 0; i < sizeof(value); i++) {
    *p = EEPROM.read(address + index * sizeof(float) + i);
    *p++;
  }
  return value;
}

void EEPROMManager::writeFloat(int index, float value) {
  byte* p = (byte*)(void*)&value;

  for (int i = 0; i < sizeof(value); i++) {
    EEPROM.write(address + index * sizeof(float) + i, *p);
    *p++;
  }
}

int EEPROMManager::readInt(int index) {
  int value = 0;
  byte* p = (byte*)(void*)&value;

  for (int i = 0; i < sizeof(value); i++) {
    *p = EEPROM.read(address + index * sizeof(int) + i);
    *p++;
  }
  return value;
}

void EEPROMManager::writeInt(int index, int value) {
  byte* p = (byte*)(void*)&value;

  for (int i = 0; i < sizeof(value); i++) {
    EEPROM.write(address + index * sizeof(int) + i, *p);
    *p++;
  }
}
