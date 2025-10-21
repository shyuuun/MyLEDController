# Troubleshooting

## My led looks weird and flicker randomly

-   Make sure you have a common ground between the power supply and the ESP32 S2 Mini
-   Make sure you have a capacitor (currenly mine is 100uF 16V) across the +5V and GND of the LED strip

## LittleFS always fail to initialize

-   Check your platformio.ini file to ensure your environment is configured to use LittleFS. The board_build.filesystem option should be set to littlefs, as in the example below:

```ini
[env:lolin_s2_mini]
platform = espressif32
board = lolin_s2_mini
framework = arduino
lib_deps =
	fastled/FastLED@^3.10.3
	esp32async/ESPAsyncWebServer@^3.8.1
	esp32async/AsyncTCP@3.4.8
monitor_speed = 115200

board_build.usb_cdc_on_boot = 1
board_build.filesystem = littlefs
```

-   Confirm that the `data` folder is located in the root directory of your project.

-   If the configuration is correct, use the PlatformIO tasks to first run `Build Filesystem Image` and then `Upload Filesystem Image` to transfer the files to the ESP32 S2 Mini.

## mDNS not resolving (can't access esp32.local) or what mDNS name to use

### Symptoms

-   Unable to ping `esp32.local` or access the web interface using the mDNS name.

### Solution

#### For Linux Users

**Option 1: Enable mDNS in systemd-resolved**

Edit the resolved configuration:

```bash
sudo nano /etc/systemd/resolved.conf
```

Add or uncomment these lines:

```ini
[Resolve]
MulticastDNS=yes
LLMNR=yes
```

Restart the service:

```bash
sudo systemctl restart systemd-resolved
```

### Verify mDNS Configuration

1. **Check the hostname in your code:**

    ```cpp
    if (!MDNS.begin("esp32")) {  // Hostname is "esp32"
    ```

    Access at: `http://esp32.local`

2. **Ensure ESP32 and PC are on the same network:**

    - **AP mode**: Connect your PC to the ESP32's WiFi network
    - **Station mode**: Both ESP32 and PC must be on the same WiFi network

3. **Check serial monitor output:**

    ```
    mDNS responder started
    Station IP: 192.168.1.xxx
    ```

4. **Test with direct IP first:**
   If `esp32.local` doesn't work, try the IP address shown in serial monitor to verify network connectivity.

### Change mDNS Hostname

To use a custom hostname (e.g., `myled.local`), modify `src/main.cpp`:

```cpp
if (!MDNS.begin("myled")) {  // Change "esp32" to your preferred name
  Serial.println("Error setting up MDNS responder!");
  while (1) {
    delay(1000);
  }
}
Serial.println("Access at: http://myled.local");
```

Then reflash the firmware and access at `http://myled.local`.
