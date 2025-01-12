#include "pico/stdlib.h"

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

// Define the delay for the LED in milliseconds if not already defined
#ifndef LED_DELAY_MS
#define LED_DELAY_MS 125
#endif

// Define the default LED pin for the Pico device
#define PICO_DEFAULT_LED_PIN 13

// Define the timing for Morse code elements in milliseconds
#define MORSE_DOT_MS 200
#define MORSE_DASH_MS 800
#define MORSE_SPACE_MS 250
#define MORSE_REPEAT_MS 3000

// Perform initialisation of the LED
int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
}

// Turn the LED on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

// Function to blink a Morse code dot
void pico_morse_dot() {
    pico_set_led(true);
    sleep_ms(MORSE_DOT_MS);
    pico_set_led(false);
    sleep_ms(MORSE_DOT_MS);
}

// Function to blink a Morse code dash
void pico_morse_dash() {
    pico_set_led(true);
    sleep_ms(MORSE_DASH_MS);
    pico_set_led(false);
    sleep_ms(MORSE_DOT_MS);
}

// Function to blink SOS in Morse code
void pico_sos() {
    pico_morse_dot();
    sleep_ms(LED_DELAY_MS);
    pico_morse_dot();
    sleep_ms(LED_DELAY_MS);
    pico_morse_dot();

    sleep_ms(MORSE_SPACE_MS);
    pico_morse_dash();
    sleep_ms(LED_DELAY_MS);
    pico_morse_dash();
    sleep_ms(LED_DELAY_MS);
    pico_morse_dash();

    sleep_ms(MORSE_SPACE_MS);
    pico_morse_dot();
    sleep_ms(LED_DELAY_MS);
    pico_morse_dot();
    sleep_ms(LED_DELAY_MS);
    pico_morse_dot();
    sleep_ms(MORSE_SPACE_MS);

    sleep_ms(MORSE_REPEAT_MS);
}

// Main function to initialize the LED and blink SOS in an infinite loop
int main() {
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);
    while (true) {
        pico_sos();
    }
}