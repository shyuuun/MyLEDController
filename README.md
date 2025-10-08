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


