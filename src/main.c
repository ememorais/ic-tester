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
                I2C_Oled_Draw_Screen(buffer, 1024);
                invert = !invert;
            }
        }        
        else if(key == 'D') 
        {
            I2C_Oled_Draw_Screen(buffer,1024);
        }
        else if(key == 0) 
        {
            I2C_Oled_Set_Contrast(contrast);
            contrast += 10;
        }
        else if(key == 9) 
        {
            if(invert)
                I2C_Oled_send(SSD1306_COMMAND, SSD1306_INVERTDISPLAY);
            else
                I2C_Oled_send(SSD1306_COMMAND, SSD1306_NORMALDISPLAY);
            invert = !invert;
        }
        else if(key == 8) 
        {
            memcpy(buffer, ic_clean, SSD1306_BUFFER_SIZE);
            I2C_Oled_Draw_Screen(((uint8_t*)buffer), SSD1306_BUFFER_SIZE);
        }
        else if(key == 7) 
        {
            memcpy(buffer, utfpr_bar, 512);
            I2C_Oled_Draw_Screen(((uint8_t*)buffer), 512);
        }
        else if(key == 6) 
        {
            memcpy(buffer, ic_and, SSD1306_BUFFER_SIZE);
            I2C_Oled_Draw_Screen(((uint8_t*)buffer), SSD1306_BUFFER_SIZE);
        }
        else if(key == 5) 
        {
            I2C_Oled_Draw_Screen(((uint8_t*)font_A), 8);
        }
        else if(key == 1) 
        {
            I2C_Oled_Set_Contrast(0x00);
        }
        else if(key == 2) 
        {
            I2C_Oled_Set_Contrast(0xFF);
        }
        else if (key == '*')
        {
                memset(buffer, 0x00, SSD1306_BUFFER_SIZE);
                I2C_Oled_Draw_Screen(buffer,1024);
        }
        
        
            
    }
}
                   
