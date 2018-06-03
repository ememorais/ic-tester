#if !defined(__I2C_H__)
#define __I2C_H__

#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "ssd1306.h"
#include "utils.h"
#include <string.h>

extern uint8_t buffer[SSD1306_BUFFER_SIZE];
extern uint8_t buffer2[SSD1306_BUFFER_SIZE];

void I2C_Init(void);
void I2C_Oled_send(uint8_t type, uint8_t command);
void I2C_Oled_Init(void);
void I2C_Oled_Draw_Screen(uint8_t* buffer_pointer);
void I2C_Oled_Set_Contrast(uint8_t contrast_level);

#endif // __I2C_H__
