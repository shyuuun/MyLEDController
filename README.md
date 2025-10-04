# LED Controller

-   I have this WS2812b LED strip laying around and I wanted to use it in my room. The problem is I don't have a controller for it yet
    So I decided to make one myself using an ESP32 S2 mini.

-   TODO:
-   [ ] Add more effects
-   [ ] Add a web interface to control the effects
-   [ ] Consider implement using IR remote control

## Project Details

-   Microcontroller: ESP32 S2 Mini
-   LED Strip: WS2812b (60 LEDs)
-   Currently configured for a 5x5 matrix, but can be adjusted in the code
-   Power Supply: 5V 10A
-   Libraries Used: FastLED, Arduino

## Note

-   Make sure your wiring is correct before powering up. Incorrect wiring can damage your components and also you may have experience weird behavior on the LED strip.

### My led looks weird and flicker randomly

-   Make sure you have a common ground between the power supply and the ESP32 S2 Mini
-   Make sure you have a capacitor (1000uF 6.3V or higher) across the +5V and GND of the LED strip
