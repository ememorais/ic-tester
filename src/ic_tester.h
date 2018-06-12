#ifndef __IC_TESTER_H__
#define __IC_TESTER_H__

#include <stdint.h>
#include "keyboard.h"
#include "i2c.h"

extern char selected_ic[4];

void IC_Tester_Run(void);
void IC_Tester_Poll(void);
void IC_Tester_Init(void);

#endif
