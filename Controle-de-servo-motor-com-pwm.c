#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

/* 
 * Este exemplo configura o PWM para 50 Hz na GPIO 22,
 * com pulso entre ~500 us (0°) e ~2400 us (180°).
 * Período = 20 ms => wrap_value = 20000, clk_div = 125 (1 MHz).
 */

// GPIO do servo
#define SERVO_GPIO       22
// Período de 20 ms (50 Hz) => 20000 us
#define SERVO_PERIOD_US  20000
// Divisor de clock para ficar em 1 MHz (125 MHz / 125)
#define SERVO_CLK_DIV    125.0f

// Ajustes de pulso típicos (podem variar de servo para servo)
#define SERVO_MIN_US     500   // ~0°
#define SERVO_MID_US     1500  // ~90° (alterei de 1470 para 1500)
#define SERVO_MAX_US     2400  // ~180°

#define SWEEP_DELAY_MS   10    // Atraso no sweep
#define SWEEP_STEP_US    5     // Incremento no pulso para varredura suave

static inline uint16_t servo_calc_level(uint32_t us) {
    /*
     * Converte microsegundos (us) em "nível" (0..wrap_value).
     * wrap_value = SERVO_PERIOD_US, e cada passo = 1 µs (pois clk = 1 MHz).
     */
    if (us > SERVO_PERIOD_US) {
        us = SERVO_PERIOD_US; // Limita para evitar estourar o período
    }
    return (uint16_t)us;
}

/**
 * Configura GPIO, wrap e clk_div para PWM a 50 Hz.
 */
void servo_pwm_init(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    // Obtém slice do PWM correspondente ao GPIO
    uint slice_num = pwm_gpio_to_slice_num(gpio);

    // Desabilita enquanto configuramos
    pwm_set_enabled(slice_num, false);

    // Carrega configuração padrão
    pwm_config config = pwm_get_default_config();
    // Ajusta o divisor para diminuir clock de 125 MHz → 1 MHz
    pwm_config_set_clkdiv(&config, SERVO_CLK_DIV);
    // Ajusta o "top" do contador => 20000 (para 20000 µs)
    pwm_config_set_wrap(&config, SERVO_PERIOD_US);

    // Aplica e habilita PWM
    pwm_init(slice_num, &config, true);
}

/**
 * Ajusta o pulso do servo em microssegundos.
 */
void servo_write_us(uint gpio, uint32_t pulse_us) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint16_t level = servo_calc_level(pulse_us);
    pwm_set_gpio_level(gpio, level);
}

int main() {
    stdio_init_all();
    sleep_ms(2000); // Espera 2s antes de iniciar

    // Configura GPIO 22 como PWM para servo
    servo_pwm_init(SERVO_GPIO);

    // 1) 180° - 2400 us
    servo_write_us(SERVO_GPIO, SERVO_MAX_US);
    sleep_ms(5000);

    // 2) 90° - 1500 us
    servo_write_us(SERVO_GPIO, SERVO_MID_US);
    sleep_ms(5000);

    // 3) 0° - 500 us
    servo_write_us(SERVO_GPIO, SERVO_MIN_US);
    sleep_ms(5000);

    // 4) Varredura suave 0° <--> 180°
    while (true) {
        // Sobe de 0° para 180°
        for (uint16_t us = SERVO_MIN_US; us <= SERVO_MAX_US; us += SWEEP_STEP_US) {
            servo_write_us(SERVO_GPIO, us);
            sleep_ms(SWEEP_DELAY_MS);
        }
        // Desce de 180° para 0°
        for (uint16_t us = SERVO_MAX_US; us >= SERVO_MIN_US; us -= SWEEP_STEP_US) {
            servo_write_us(SERVO_GPIO, us);
            sleep_ms(SWEEP_DELAY_MS);
        }
    }

    return 0;
}
