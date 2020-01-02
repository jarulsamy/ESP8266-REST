# ESP8266-REST

This software uses REST POST to send data from a temperature sensor to a REST server. A secondary computer hosts a REST API using python. In this example, the ESP8266 grabs some data from a a TMP36 temperature sensor and writes that data to the REST API using JSON.

## Setup

Wire the TMP36 sensor using the following pinouts.

| TMP-36 | PIN |
| :----: | :-: |
|  LEFT  |  3v |
| CENTER |  A0 |
|  RIGHT | GND |

![alt text](http://www.esp8266learning.com/wp-content/uploads/2016/08/wemos-and-tmp36_bb.png)

The center pin can be changed if you edit the `SENSOR_PIN` in `Temp-Sensor`.

```cpp
#define SENSOR_PIN A0
```

### ESP8266

Install the following dependencies using the built-in arduino package manager.

-   ArduinoJson - Version 5.13.5
-   EEPROM-Loader \*Included with this repository.

To install the EEPROM-Loader library, symlink the `EEPROM-Loader` directory to your Arduino libraries folder. You could copy the `EEPROM-Loader` folder instead if you would like to avoid symbolic links.

This repository is organized as a series of arduino project directories. To ensure the security of WiFi credentials and the REST API URL, all of this data is written to the onboard EEPROM.

Use `EEPROM-Write` to save your credentials to the EEPROM.
Edit the `EEPROM-Write.ino` file, substituting in your own values.

```cpp
EEPROM_DATA data = {"WIFI_SSID",
                    "WIFI_PASSWORD",
                    "REST_API_ENDPOINT"
                   };
```

For example:

```cpp
EEPROM_DATA data = {"Super-Dope-Wifi-Network",
                    "passwords-are-lame",
                    "http://server/api/v1.0/temps"
                   };
```

Upload this to your ESP8266 and open the serial monitor. Reset the controller and wait for the output:

    "Written custom data!"

Now you are ready to upload the main `Temp-Sensor` project. It should work without any changes.

If you need to debug for some reason, define DEBUG by uncommenting line 9:

```cpp
#define DEBUG
```

This will print more verbose information to the serial
monitor.

> The TMP36 sensor is capable of running at several voltages. Change `line 7` of `Temp-Sensor` to fit whatever voltage you are using.

### Server

Flask is utilized to host a REST API.

This software requires **Python 3.6+**.

Install the dependencies with pip:

```bash
pip install -r requirements.txt
```

> This is just a demo/development script for hosting a REST API endpoint. It should **NOT** be used in an official deployment without a standalone [webserver](https://www.e-tinkers.com/2018/08/how-to-properly-host-flask-application-with-nginx-and-guincorn/).

### Other Arduinos

These programs should be fully portable to other arduinos if you modify the wifi config headers and HTTP client.

## Support

Reach out to me at one of the following places!

-   Email (Best) at joshua.gf.arul@gmail.com
-   Twitter at <a href="http://twitter.com/joshuaa9088" target="_blank">`@joshuaa9088`</a>

* * *
