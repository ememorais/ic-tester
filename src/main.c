// main.c
// Desenvolvido para a placa EK-TM4C1294XL
// Inicializa periféricos e faz um loop de polling
// e atualização do funcionamento do motor.
// Marcelo Fernandes e Bruno Colombo

#include "main.h"

int main(void)
{
    PLL_Init();
    SysTick_Init();
    GPIO_Init();
    Keyboard_Init();
    Timer_Init();
    I2C_Init();
    I2C_Oled_Init();
    I2C_Oled_Draw(0x00);

    while(1)
    {
        uint8_t key = Keyboard_Poll();
        if(key == 'A')
            I2C_Oled_send(OLED_COMMAND, 0xAE);
        else if(key == 'B')
            I2C_Oled_send(OLED_COMMAND, 0xAF);
        else if (key != 0xFF)
        {
            for(int i = 0; i < (128 * 8); i++)
                I2C_Oled_send(SSD1306_DATA, key);
        }
    }
}
                   
