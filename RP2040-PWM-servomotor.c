#include <stdio.h>
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#define SERVO_PIN 18

const uint32_t PWM_WRAP_VALUE = 62500;
const float PWM_CLOCK_DIVIDER = 40.0f;

void initialize_pwm_servo();

int main(void)
{
    stdio_init_all();

    // Inicializa PWM para controle do servo
    initialize_pwm_servo();
}

void initialize_pwm_servo()
{
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_set_clkdiv(slice_num, PWM_CLOCK_DIVIDER);
    pwm_set_wrap(slice_num, PWM_WRAP_VALUE);
    pwm_set_enabled(slice_num, true);
}