#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_GPIO 22
#define SERVO_PWM_DIV 125.0f // Divisor para obter 1MHz (125e6 / 125 = 1e6)
#define SERVO_PWM_WRAP 19999 // Período de 20ms (20000 ticks0

// Pulsos (em µs) para as posições do servo
#define Servo_max 2400 // Aproximadamente 180°
#define Servo_max 1470 // Aproximadamente 90°
#define servo_max 500  // Aproximadamente 0°

#define SERVO_STEP 5      // Incremento de 5µs para movimento suave
#define SERVO_DELAY_MS 10 // Atraso de 10ms entre incrementos

// Definições para o LED RGB (GPIO12)
#define LED_GPIO 12
#define LED_PWM_WRAP 255   // Resolução de 8 bits para brilho
#define LED_PWM_DIV 488.0f // Aproximadamente 1kHz de frequência para PWM do LED

int main()
{
    stdio_init_all();

    // --- Configuração do PWM para o Servomotor ---
    gpio_set_function(SERVO_GPIO, GPIO_FUNC_PWM);
    uint servo_slice = pwm_gpio_to_slice_num(SERVO_GPIO);
    uint servo_channel = pwm_gpio_to_channel(SERVO_GPIO);
    pwm_set_wrap(servo_slice, SERVO_PWM_WRAP);
    pwm_set_clkdiv(servo_slice, SERVO_PWM_DIV);
    pwm_set_chan_level(servo_slice, servo_channel, 0);
    pwm_set_enabled(servo_slice, true);

    // --- Configuração do PWM para o LED RGB ---
    gpio_set_function(LED_GPIO, GPIO_FUNC_PWM);
    uint led_slice = pwm_gpio_to_slice_num(LED_GPIO);
    uint led_channel = pwm_gpio_to_channel(LED_GPIO);
    pwm_set_wrap(led_slice, LED_PWM_WRAP);
    pwm_set_clkdiv(led_slice, LED_PWM_DIV);
    pwm_set_chan_level(led_slice, led_channel, 0); // Inicia com LED apagado
    pwm_set_enabled(led_slice, true);

    // --- Etapas Iniciais de Posicionamento do Servo ---
    // 1) Posição de 180° (2400µs)
    pwm_set_chan_level(servo_slice, servo_channel, Servo_max);
    printf("Posição: 180° (pulse: %d µs)\n", Servo_max);
    sleep_ms(5000);

    // 2) Posição de 90° (1470µs)
    pwm_set_chan_level(servo_slice, servo_channel, Servo_max);
    printf("Posição: 90° (pulse: %d µs)\n", Servo_max);
    sleep_ms(5000);

    // 3) Posição de 0° (500µs)
    pwm_set_chan_level(servo_slice, servo_channel, servo_max);
    printf("Posição: 0° (pulse: %d µs)\n", servo_max);
    sleep_ms(5000);

    // Variáveis para o efeito de fade do LED
    int led_brightness = 0;
    int led_direction = 1; // 1 para aumentar, -1 para diminuir

    // --- Movimento Suave do Servo (0° a 180° e retorno) ---
    while (true)
    {
        // Movimento de 0° a 180°
        for (int pulse = servo_max; pulse <= Servo_max; pulse += SERVO_STEP)
        {
            pwm_set_chan_level(servo_slice, servo_channel, pulse);

            // Atualiza o brilho do LED para efeito degrade
            led_brightness += led_direction;
            if (led_brightness >= LED_PWM_WRAP)
            {
                led_brightness = LED_PWM_WRAP;
                led_direction = -1;
            }
            else if (led_brightness <= 0)
            {
                led_brightness = 0;
                led_direction = 1;
            }
            pwm_set_chan_level(led_slice, led_channel, led_brightness);
            sleep_ms(SERVO_DELAY_MS);
        }

        // Movimento de 180° a 0°
        for (int pulse = Servo_max; pulse >= servo_max; pulse -= SERVO_STEP)
        {
            pwm_set_chan_level(servo_slice, servo_channel, pulse);

            // Atualiza o brilho do LED para efeito degrade
            led_brightness += led_direction;
            if (led_brightness >= LED_PWM_WRAP)
            {
                led_brightness = LED_PWM_WRAP;
                led_direction = -1;
            }
            else if (led_brightness <= 0)
            {
                led_brightness = 0;
                led_direction = 1;
            }
            pwm_set_chan_level(led_slice, led_channel, led_brightness);
            sleep_ms(SERVO_DELAY_MS);
        }
    }

    return 0;
}
