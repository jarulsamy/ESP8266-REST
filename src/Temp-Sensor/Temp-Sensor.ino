#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <EEPROM-Loader.h>

// #define DEBUG

void flashLED();
void flashLED(int pin);

EEPROM_DATA data = EEPROM_LOAD();
const char *ssid = data.ssid;
const char *password = data.password;
const char *host = data.host;

const int SENSOR_VOLTAGE = 3;
const int SENSOR_PIN = A0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(SENSOR_PIN, INPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // Setup serial
    Serial.begin(9600);
    // Print a blank line - esp8266 outputs some junk on reset.
    Serial.println("");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        // Keep the LED on while connecting to WiFi
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        Serial.print(".");
    }
    flashLED();

    Serial.println("");
    Serial.print("Wifi Connected: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    Serial.print("REST ENDPOINT: ");
    Serial.println(host);

    return;
}

void loop()
{
    // Read temp sensor value
    int reading = analogRead(SENSOR_PIN);
    // Converting that reading to voltage
    float voltage = reading * SENSOR_VOLTAGE;
    voltage /= 1024.0;
    // Convert to Celcius
    float temperatureC = (voltage - 0.5) * 100;
    // Convert to Fahrenheit
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

#ifdef DEBUG
    Serial.print(temperatureC);
    Serial.println(" Degrees C");

    Serial.print(temperatureF);
    Serial.println(" Degrees F");
    flashLED();
#endif

    if (WiFi.status() == WL_CONNECTED)
    {
        // REST API
        HTTPClient http;
        http.begin(host);
        http.addHeader("Content-Type", "application/json");

        StaticJsonBuffer<300> JSONBuffer;
        JsonObject &encoder = JSONBuffer.createObject();

        // Assemble the JSON Object
        encoder["celsius"] = JSONBuffer.createObject();
        encoder["fahrenheit"] = JSONBuffer.createObject();
        encoder["celsius"]["value"] = temperatureC;
        encoder["fahrenheit"]["value"] = temperatureF;

        char buff[300];
        encoder.prettyPrintTo(buff, sizeof(buff));
        // Post to server
        int httpCode = http.POST(buff);
        // If the POST is unsuccessful, flash the LED and wait
        // Prevents accidental DDOSing.
        if (httpCode != 201)
        {
            flashLED();
            delay(1000);
        }

        http.end();

#ifdef DEBUG
        Serial.println(buff);
        Serial.print("HTTP CODE: ");
        Serial.println(httpCode);
#endif
    }
    else
    {
        Serial.println("Error in Wifi");
    }

    delay(10000);
    return;
}

// Built in LED flips LOW and HIGH, thus overloaded function
void flashLED()
{
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    return;
}

void flashLED(int pin)
{
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    return;
}
