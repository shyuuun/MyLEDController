# LED Controller

-   I have this WS2812b LED strip laying around and I wanted to use it in my room. The problem is I don't have a controller for it yet
    So I decided to make one myself using an ESP32 S2 mini.

-   TODO:
-   [ ] Error codes in the 1st - 4th LEDs
-   [ ] Add led effects
-   [ ] Add a web interface to control the LEDs
-   [ ] Consider implement using IR remote control

## Project Details

-   Microcontroller: ESP32 S2 Mini
-   LED Strip: WS2812b (60 LEDs)
-   Currently configured for a 5x5 matrix, but can be adjusted in the code
-   Power Supply: 5V 10A
-   Libraries Used: FastLED, Arduino

## Notes

-   Make sure your wiring is correct before powering up. Incorrect wiring can damage your components and also you may have experience weird behavior on the LED strip.

### Troubleshooting

My led looks weird and flicker randomly

-   Make sure you have a common ground between the power supply and the ESP32 S2 Mini
-   Make sure you have a capacitor (currenly mine is 100uF 16V) across the +5V and GND of the LED strip

LittleFS always fail to initialize

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
