// main.c
// Desenvolvido para a placa EK-TM4C1294XL
// Inicializa periféricos e faz um loop de polling
// e atualização do funcionamento do motor.
// Marcelo Fernandes e Bruno Colombo

#include "main.h"

char invert = 0;

int main(void)
{
    int contrast = 0;
    PLL_Init();
    SysTick_Init();
    GPIO_Init();
    Keyboard_Init();
    Timer_Init();
    I2C_Init();
    I2C_Oled_Init();

    while(1)
    {
        uint8_t key = Keyboard_Poll();
        if(key == 'A')
        {
            I2C_Oled_send(SSD1306_COMMAND, 0xAE);
        }
        else if(key == 'B')
        {
            I2C_Oled_send(SSD1306_COMMAND, 0xAF);
        }
        else if(key == 'C') 
        {
            //memset(buffer, 0x00, SSD1306_BUFFER_SIZE);
            for(int i = 0; i < 30; i++)
            {
                memset(buffer, invert? 0xFF : 0x00, SSD1306_BUFFER_SIZE);
                I2C_Oled_Draw_Screen(buffer);
                invert = !invert;
            }
        }        
        else if(key == 'D') 
        {
            for(int i = 0; i < 30; i++)
            {
                SysTick_Wait1ms(20);
                memset(buffer, invert? 0x00 : 0xFF, SSD1306_BUFFER_SIZE);
                I2C_Oled_Draw_Screen(buffer);
                invert = !invert;
            }
        }
        else if(key == 0) 
        {
            I2C_Oled_Set_Contrast(contrast);
            contrast += 10;
        }
        else if(key == 1) 
        {
            I2C_Oled_Set_Contrast(0x00);
        }
        else if(key == 2) 
        {
            I2C_Oled_Set_Contrast(0xFF);
        }
        
            
    }
}
                   
