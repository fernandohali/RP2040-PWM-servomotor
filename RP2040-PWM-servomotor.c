#include <stdio.h>
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#define SERVO_PIN 18

const uint32_t PWM_WRAP_VALUE = 62500;
const float PWM_CLOCK_DIVIDER = 40.0f;

void initialize_pwm_servo();
void set_servo_angle(float duty_cycle, uint32_t duration_ms);

int main(void)
{
    // Movimento oscilatório do servo
    // Esse valores já estão no execicio,
    const float MIN_DUTY_CYCLE = 0.025f;
    const float MAX_DUTY_CYCLE = 0.12f;
    const float STEP_DUTY_CYCLE = 0.00025f;

    // Inicializa os pinos, a UART e o stdio
    stdio_init_all();

    // Inicializa PWM para controle do servo
    initialize_pwm_servo();

    // Define ângulos específicos para o servo
    set_servo_angle(0.12f, 5000);   // 180°
    set_servo_angle(0.0735f, 5000); // 90°
    set_servo_angle(0.025f, 5000);  // 0°

    while (true)
    {
        // Movimento oscilatório do servo
        // T = 1/50 Hz = 0.02 s = 20 ms
        /*
        Essa parte do for é para fazer o servo motor se movimentar de 0 a 180 graus
        e depois de 180 a 0 graus, com isso ele vai entrar na função com
        o duty_cycle de 0.025 e vai aumentar até 0.12, depois ele vai diminuir de 0.12 até 0.025
        */
        for (float duty = MIN_DUTY_CYCLE; duty <= MAX_DUTY_CYCLE; duty += STEP_DUTY_CYCLE)
        {
            set_servo_angle(duty, 10);
        }
        for (float duty = MAX_DUTY_CYCLE; duty >= MIN_DUTY_CYCLE; duty -= STEP_DUTY_CYCLE)
        {
            set_servo_angle(duty, 10);
        }
    }
    return 0;
}

void initialize_pwm_servo()
{
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);       // Habilita a função PWM no pino do servo
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o número do slice PWM associado ao pino do servo
    pwm_set_clkdiv(slice_num, PWM_CLOCK_DIVIDER);      // Define o divisor de clock para o PWM
    pwm_set_wrap(slice_num, PWM_WRAP_VALUE);           // Define o ciclo de trabalho máximo para o PWM

    pwm_set_enabled(slice_num, true);
}

void set_servo_angle(float duty_cycle, uint32_t duration_ms)
{
    pwm_set_gpio_level(SERVO_PIN, (uint32_t)(PWM_WRAP_VALUE * duty_cycle));
    sleep_ms(duration_ms);
}
