#include "timer.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>

// 84 000 000
// freq = sys_freq / ((prescaler-1) + (auto_reload_reg-1))
#define PRESCALER   (84)
#define ARR_VALUE   (1000)

void timer_setup(void){
    rcc_periph_clock_enable(RCC_TIM2);

    // high lvl timer config
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    // set up pwm
    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);

    // enable pwm output
    timer_enable_counter(TIM2);
    timer_enable_oc_output(TIM2, TIM_OC1);

    // set up freq + resolution
    timer_set_prescaler(TIM2, PRESCALER-1);
    timer_set_period(TIM2, ARR_VALUE - 1);
}

void timer_pwm_set_duty_cycle(float duty_cycle){
    // duty_cycle = (cap_compare_reg / arr) * 100
    // you set ccr value in register;  ccr = (duty_cycle / 100) * arr
    const float raw_value = (float)ARR_VALUE * duty_cycle / 100.0f;
    timer_set_oc_value(TIM2, TIM_OC1, (uint32_t)raw_value);
}