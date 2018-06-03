#if !defined(__I2C_H__)
#define __I2C_H__

#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "ssd1306.h"
#include "utils.h"

#define OLED_COMMAND 0x00
#define OLED_DATA   0x40


void I2C_Init(void);
void I2C_Oled_send(uint8_t type, uint8_t command);
void I2C_Oled_Init(void);
void I2C_Oled_Draw(uint8_t byte);

#endif // __I2C_H__
