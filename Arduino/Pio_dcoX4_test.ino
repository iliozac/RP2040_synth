#include <Arduino.h>
#include "hardware/pio.h"

#define PIN0 0
#define PIN1 1

const uint16_t pio_code[] = {
    0x8080, // pull noblock
    0xa027, // mov x, osr
    0xa041, // mov y, x
    0xe001, // set pins, 0
    0x0083, // jmp y--, 3
    0xa041, // mov y, x
    0xe000, // set pins, 1
    0x0086, // jmp y--, 6
    0x0000  // jmp 0
};

const struct pio_program prog = {
    .instructions = pio_code,
    .length = 9,
    .origin = -1,
};

PIO pio = pio0;
uint sm0, sm1;
uint offset;
float clkdiv = 1000.0f;
bool counting_up = true;
unsigned long last_update = 0;

void setup() {
    pinMode(PIN0, INPUT);
    pinMode(PIN1, INPUT);
    gpio_set_function(PIN0, GPIO_FUNC_PIO0);
    gpio_set_function(PIN1, GPIO_FUNC_PIO0);
    
    pio = pio0;
    offset = pio_add_program(pio, &prog);
    
    // SM0 per GP0
    sm0 = 0;
    pio_sm_config c0 = pio_get_default_sm_config();
    sm_config_set_wrap(&c0, offset, offset + 8);
    sm_config_set_set_pins(&c0, PIN0, 1);
    pio_sm_set_consecutive_pindirs(pio, sm0, PIN0, 1, true);
    sm_config_set_clkdiv(&c0, clkdiv);
    
    pio_sm_init(pio, sm0, offset, &c0);
    pio_sm_put_blocking(pio, sm0, 25);
    pio_sm_set_enabled(pio, sm0, true);
    
    delay(10);
    
    // SM1 per GP1  
    sm1 = 1;
    pio_sm_config c1 = pio_get_default_sm_config();
    sm_config_set_wrap(&c1, offset, offset + 8);
    sm_config_set_set_pins(&c1, PIN1, 1);
    pio_sm_set_consecutive_pindirs(pio, sm1, PIN1, 1, true);
    sm_config_set_clkdiv(&c1, clkdiv);
    
    pio_sm_init(pio, sm1, offset, &c1);
    pio_sm_put_blocking(pio, sm1, 25);
    pio_sm_set_enabled(pio, sm1, true);
    
    last_update = millis();
}

void loop() {
    unsigned long current_time = millis();
    
    if (current_time - last_update >= 50) {
        last_update = current_time;
        
        // Varia clkdiv tra 1000 e 3000
        if (counting_up) {
            clkdiv += 100.0f;
            if (clkdiv >= 3000.0f) counting_up = false;
        } else {
            clkdiv -= 100.0f;
            if (clkdiv <= 1000.0f) counting_up = true;
        }
        
        // CAMBIA CLOCK DIVIDER SENZA FERMARE LE SM
        // Usa pio_sm_set_clkdiv() che cambia a runtime
        pio_sm_set_clkdiv(pio, sm0, clkdiv);
        pio_sm_set_clkdiv(pio, sm1, clkdiv);
        
        // Non serve reinviare il delay, rimane 25
    }
    
    delay(1);
}