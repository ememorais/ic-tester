// gpio.h
// Desenvolvido para a placa EK-TM4C1294XL
// Marcelo Fernandes e Bruno Colombo

#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include <stdio.h>     
#include <stdlib.h> 
#include "tm4c1294ncpdt.h"

void GPIO_Init(void);

uint32_t PortD_Input(void);

void PortM_OutputKeyboard(uint32_t value);

void PortN_SetOutput(uint32_t pos);

void PortN_SetInput(uint32_t pos);

void PortK_SetOutput(uint32_t pos);

void PortK_SetInput(uint32_t pos);

void Set_Output(uint32_t pin);

void Set_Input(uint32_t pin);

uint32_t PortK_Input(void);

void PortK_Output(uint32_t value);

uint32_t PortN_Input(void);

void PortN_Output(uint32_t value);

#endif
