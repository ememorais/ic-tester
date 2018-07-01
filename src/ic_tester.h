#ifndef __IC_TESTER_H__
#define __IC_TESTER_H__

#include <stdint.h>
#include "../images/images.h"
#include "keyboard.h"
#include "i2c.h"

extern char selected_ic[4];

extern uint8_t testing_state;
extern uint8_t testing_progression;
extern uint8_t testing_active;

void IC_Tester_Run(void);
void IC_Tester_Poll(void);
void IC_Tester_Init(void);
void IC_Tester_Test(void);
void IC_Tester_Results(void);
uint8_t IC_Tester_Available(void);
#endif
