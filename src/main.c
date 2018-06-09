// main.c
// Desenvolvido para a placa EK-TM4C1294XL
// Inicializa periféricos e faz um loop de polling
// e atualização do funcionamento do motor.
// Marcelo Fernandes e Bruno Colombo

#include "main.h"

char invert = 0;

int main(void)
{
    //int contrast = 0;
    PLL_Init();
    SysTick_Init();
    GPIO_Init();
    Keyboard_Init();
    Timer_Init();
    I2C_Init();
    I2C_OLED_Init();
    I2C_OLED_Sequence_Init();


    while (1)
    {
        IC_Tester_Run();
    }
}
