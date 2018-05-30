// globals.h
// Desenvolvido para a placa EK-TM4C1294XL
// Marcelo Fernandes e Bruno Colombo


#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <stdint.h>

extern volatile uint32_t    pwm_counter;
extern volatile uint8_t     pwm_bit;

extern volatile int32_t     motor_speed;
extern volatile uint32_t    motor_direction;
extern volatile uint32_t    motor_old_direction;

extern volatile uint32_t    timer_counter;
extern volatile uint32_t    smooth_counter;
extern volatile uint32_t    keyboard_counter;

extern volatile uint8_t     smooth_mode;
extern volatile int32_t     smooth_speed;
extern volatile uint8_t     smooth_swap;

extern volatile uint8_t			flag_uart;

#endif
