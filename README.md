# LED Controller

-   I have this WS2812b LED strip laying around and I wanted to use it in my room. The problem is I don't have a controller for it yet
    So I decided to make one myself using an ESP32 S2 mini.

## Features to be planned

-   Please refer to the (docs/features-to-be-planned.md)[docs/features-to-be-planned.md] file for the features that are planned for this project.

## Project Details

### Hardware

-   Microcontroller: ESP32 S2 Mini
-   LED Strip: WS2812b (60 LEDs)
-   Currently configured 10 LEDs, but can be adjusted in the code
-   Power Supply: 5V 10A
-   Libraries:
    -   Arduino Framework
    -   AsyncTCP, ESPAsyncWebServer
    -   FastLED

### Web Interface

-   Libraries used:
    -   AlpineJS
    -   PicoCSS

## Notes

-   Make sure your wiring is correct before powering up. Incorrect wiring can damage your components and also you may have experience weird behavior on the LED strip.
