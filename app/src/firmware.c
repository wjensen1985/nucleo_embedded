#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/scb.h>

#include "core/system.h"
#include "timer.h"

#define BOOTLOADER_SIZE (0x8000U)

#define LED_PORT   (GPIOA)
#define LED_PIN    (GPIO5)

static void vector_setup(void){
  SCB_VTOR = BOOTLOADER_SIZE;
}

static void gpio_setup(void){
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(LED_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LED_PIN);
  gpio_set_af(LED_PORT, GPIO_AF1, LED_PIN);
}

int main(void){
  vector_setup();
  system_setup();
  gpio_setup();
  timer_setup();

  uint64_t start_time = system_get_ticks();
  uint64_t last_blink = start_time;

  float duty_cycle = 0.0f;
  timer_pwm_set_duty_cycle(duty_cycle);
  
  while(1){

    // led blink check
    if (system_get_ticks() - last_blink >= 10) {
      duty_cycle += 1.0f;
      if (duty_cycle > 100.0f){
        duty_cycle = 0.0f;
      }
      timer_pwm_set_duty_cycle(duty_cycle);
      
      last_blink = system_get_ticks();
    }



  }

  // never return
  return 0;
}