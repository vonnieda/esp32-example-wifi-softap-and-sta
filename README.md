# ESP32 WiFi SoftAP + Station Example

This example shows how to use the Wi-Fi SoftAP functionality of the Wi-Fi driver of ESP for serving as an Access Point and how to use the Wi-Fi Station functionality of the Wi-Fi driver of ESP for connecting to an Access Point at the same time.

## How to use example

Use menuconfig to set Example configuration SSID and password for each of STA and AP.

### Configure the project

Open the project configuration menu (`idf.py menuconfig`). 

In the `Example Configuration` menu:

* Set the Wi-Fi configuration.
    * Set `WiFi AP SSID`.
    * Set `WiFi AP Password`.
    * Set `WiFi STA SSID`.
    * Set `WiFi STA Password`.

Optional: If you need, change the other options according to your requirements.

### Build and Flash

Build the project and flash it to the board, then run the monitor tool to view the serial output:

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for all the steps to configure and use the ESP-IDF to build projects.

* [ESP-IDF Getting Started Guide on ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)
* [ESP-IDF Getting Started Guide on ESP32-S2](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/get-started/index.html)
* [ESP-IDF Getting Started Guide on ESP32-C3](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/get-started/index.html)

## Example Output
Note that the output, in particular the order of the output, may vary depending on the environment.

Console output shows connection to AP and connection from client to ESP32 SoftAP.
```
I (1543) wifi-softap+sta: Station connected with IP: 192.168.1.168, GW: 192.168.1.1, Mask: 255.255.255.0.
I (15363) wifi-softap+sta: SoftAP client connected with IP: 192.168.4.2.
```


## Troubleshooting

For any technical queries, please open an [issue](https://github.com/vonnieda/esp32-example-wifi-softap-and-sta/issues) on GitHub.