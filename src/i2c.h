#if !defined(__I2C_H__)
#define __I2C_H__

#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "ssd1306.h"


void I2C_Init(void);
void I2C_Oled_command(uint8_t command);
void I2C_Oled_Init(void);
void I2C_Oled_Draw(uint8_t byte);
void i2c_check_transmission(void);

#endif // __I2C_H__
