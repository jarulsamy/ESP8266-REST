#ifndef EEPROM_LOADER_H
#define EEPROM_LOADER_H

#include <EEPROM.h>

struct EEPROM_DATA
{
    char ssid[50];
    char password[50];
    char host[250];
};

EEPROM_DATA EEPROM_LOAD()
{
    EEPROM.begin(512);
    EEPROM_DATA data;
    EEPROM.get(0, data);
    return data;
}

#endif
