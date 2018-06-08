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
    //     uint8_t key = Keyboard_Poll();
    //     if (key == 'A')
    //     {
    //         I2C_OLED_Send(SSD1306_COMMAND, 0xAE);
    //     }
    //     else if (key == 'B')
    //     {
    //         I2C_OLED_Send(SSD1306_COMMAND, 0xAF);
    //     }
    //     else if (key == 0)
    //     {
    //         I2C_OLED_Set_Contrast(contrast);
    //         contrast += 10;
    //     }
    //     else if (key == 9)
    //     {
    //         if (invert)
    //             I2C_OLED_Send(SSD1306_COMMAND, SSD1306_INVERTDISPLAY);
    //         else
    //             I2C_OLED_Send(SSD1306_COMMAND, SSD1306_NORMALDISPLAY);
    //         invert = !invert;
    //     }
    //     else if (key == 8)
    //     {
    //         I2C_OLED_Draw(((uint8_t *)ic_clean), SSD1306_BUFFER_SIZE);
    //     }
    //     else if (key == 7)
    //     {
    //         I2C_OLED_Move_Cursor(0, 0);
    //         I2C_OLED_Draw(((uint8_t *)utfpr_bar), 768);
    //     }
    //     else if (key == 6)
    //     {
    //         I2C_OLED_Move_Cursor(0, 0);
    //         I2C_OLED_Draw(((uint8_t *)ic_and), SSD1306_BUFFER_SIZE);
    //     }
    //     else if (key == 5)
    //     {
    //         I2C_OLED_Move_Cursor(0, 0);
    //         I2C_OLED_Print("IC TESTER - V0.1");
    //         I2C_OLED_Move_Cursor(1, 0);
    //         I2C_OLED_Print("MARCELO E BRUNO");
    //     }
    //     else if (key == 1)
    //     {
    //         I2C_OLED_Set_Contrast(0x00);
    //     }
    //     else if (key == 2)
    //     {
    //         I2C_OLED_Set_Contrast(0xFF);
    //     }
    //     else if (key == '*')
    //     {
    //         I2C_OLED_Clear();
    //     }
     }
}
