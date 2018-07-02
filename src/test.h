#ifndef __TEST_H__
#define __TEST_H__

#include "gpio.h"
#include <string.h>
#include "utils.h"

int32_t Verify_mem(char code_ic[]);

uint32_t GPIO_config(int pos);

uint32_t Char_toHex(int pos);

uint32_t Exec_teste(int pos);

#endif
