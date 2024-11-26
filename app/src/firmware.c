#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "core/system.h"

#define LED_PORT   (GPIOA)
#define LED_PIN    (GPIO5)
#define BLINK_FREQ (100)

static void gpio_setup(void){
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

int main(void){
  system_setup();
  gpio_setup();

  uint64_t start_time = system_get_ticks();
  uint64_t last_blink = start_time;
  
  while(1){
    if (system_get_ticks() - last_blink >= BLINK_FREQ) {
      gpio_toggle(LED_PORT, LED_PIN);
      last_blink = system_get_ticks();
    }

  }

  // never return
  return 0;
}