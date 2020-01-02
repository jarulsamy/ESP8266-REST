/*
 * Write WiFi data to EEPROM
 *
 */

#include <Arduino.h>
#include <EEPROM.h>
#include <EEPROM-Loader.h>

/*
EEPROM_DATA data = {"WIFI_SSID",
                    "WIFI_PASSWORD",
                    "REST_API_ENDPOINT"
                   };
*/

const int writeAddress = 0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.begin(9600);
    Serial.println("");
    EEPROM.begin(512);

    // Actually write to EEPROM
    EEPROM.put(writeAddress, data);
    EEPROM.commit();

    // Display confirmation
    Serial.println("Written custom data!");
    digitalWrite(LED_BUILTIN, HIGH);
    return;
}

void loop()
{
}
