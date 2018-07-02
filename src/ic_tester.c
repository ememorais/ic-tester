#include "ic_tester.h"

char selected_ic[4] = {'`', '`', '`', '\0'};

uint8_t testing_state = 0;
uint8_t testing_progression = 0;

uint8_t testing_active = 0;
uint8_t testing_progression_current = 0;

uint8_t test_result = 0;

enum Tester_State
{
    INIT,
    POLLING,
    SELECTING,
    TESTING,
    RESULTS
} tester_state = INIT;

uint8_t current_digit = 0;

void IC_Tester_Run(void)
{

    switch (tester_state)
    {
    case INIT:
        IC_Tester_Init();
        break;
    case POLLING:
        IC_Tester_Poll();
        break;
    case SELECTING:
        IC_Tester_Select();
        break;
    case TESTING:
        IC_Tester_Test();
        break;
    case RESULTS:
        IC_Tester_Results();
        break;
    default:
        break;
    }
}

void IC_Tester_Init(void)
{
    current_digit = 0;
    strcpy(selected_ic, "```");

    I2C_OLED_Clear();
    I2C_OLED_Move_Cursor(0, 0);
    I2C_OLED_Print(" Selecione o CI:");
    I2C_OLED_Move_Cursor(3, 36);
    I2C_OLED_Print("74LS");
    I2C_OLED_Print(selected_ic);

    tester_state = POLLING;
}

void IC_Tester_Poll(void)
{
    uint8_t key = Keyboard_Poll();

    if (current_digit < 3 && (key >= '0' && key <= '9'))
    {
        selected_ic[current_digit] = key;

        current_digit++;

        I2C_OLED_Move_Cursor(3, 68);
        I2C_OLED_Print(selected_ic);
    }
    if (key != 0xFF && key != selected_ic[current_digit] && current_digit > 0)
    {
        I2C_OLED_Move_Cursor(7, 0);
        I2C_OLED_Print("* APAGAR");
    }
    if (key == '*')
    {
        if (current_digit > 0)
            current_digit--;

        selected_ic[current_digit] = '`';

        I2C_OLED_Move_Cursor(3, 68);
        I2C_OLED_Print(selected_ic);
    }
    if (key != 0xFF && key != selected_ic[current_digit] && current_digit > 0)
    {
        I2C_OLED_Move_Cursor(6, 40);
        I2C_OLED_Print("CONFIRMAR #");
    }
    if (key == '#')
    {
        tester_state = SELECTING;
    }
}

void IC_Tester_Select(void)
{
    I2C_OLED_Clear();
    if (strcmp(selected_ic, "00`") == 0)
    {
        I2C_OLED_Move_Cursor(0, center_string_position("74LS00"));
        I2C_OLED_Print("74LS00");
        I2C_OLED_Move_Cursor(1, center_string_position("encontrado"));
        I2C_OLED_Print("encontrado");
        I2C_OLED_Move_Cursor(2, 0);
        I2C_OLED_Draw(BMP_74LS00, 768);
        SysTick_Wait1ms(2000);
        tester_state = TESTING;
    }
    else if (strcmp(selected_ic, "08`") == 0)
    {
        I2C_OLED_Move_Cursor(0, center_string_position("74LS08"));
        I2C_OLED_Print("74LS08");
        I2C_OLED_Move_Cursor(1, center_string_position("encontrado"));
        I2C_OLED_Print("encontrado");
        I2C_OLED_Move_Cursor(2, 0);
        I2C_OLED_Draw(BMP_74LS08, 768);
        SysTick_Wait1ms(2000);
        tester_state = TESTING;
    }
    else
    {
        if (IC_Tester_Available())
        {
            char name[10];
            strcpy(name, "74LS");
            strcat(name, selected_ic);
            if (name[6] == '`')
                name[6] = ' ';
            I2C_OLED_Move_Cursor(0, center_string_position("74LS08"));
            I2C_OLED_Print(name);
            I2C_OLED_Move_Cursor(1, center_string_position("encontrado"));
            I2C_OLED_Print("encontrado");
            I2C_OLED_Move_Cursor(2, 0);
            I2C_OLED_Draw(BMP_74LSXX, 768);
            SysTick_Wait1ms(2000);
            tester_state = TESTING;
        }
        else
        {
            I2C_OLED_Move_Cursor(0, center_string_position("CI não"));
            I2C_OLED_Print("CI nao");
            I2C_OLED_Move_Cursor(1, center_string_position("encontrado"));
            I2C_OLED_Print("encontrado");
            SysTick_Wait1ms(2000);
            tester_state = INIT;
        }
    }
}

uint8_t IC_Tester_Available(void)
{
    //!!MUDAR!! chama função que verifica vetor e vê se valor existe
    //          só precisa dizer se existe ou não (1 ou 0)
    return 1;
}

void IC_Tester_Test(void)
{
    test_result = 0x20; // !!MUDAR!! chama função que faz o teste aqui
    if (!testing_active)
    {
        I2C_OLED_Move_Cursor(1, 0);
        I2C_OLED_Draw(BMP_LOADING_EMPTY, 128);
        I2C_OLED_Move_Cursor(1, 0);
        testing_active = 1;
    }
    else
    {
        if (testing_progression > testing_progression_current)
        {
            I2C_OLED_Draw(BMP_LOADING_FULL, 1);
            testing_progression_current++;
            if (testing_progression > 127)
            {
                testing_active = 0;
                testing_progression = testing_progression_current = 0;
                tester_state = RESULTS;
            }
        }
    }
}

void IC_Tester_Results(void)
{
    if (test_result)
    {
        uint32_t dec = 0;

        for (uint8_t i = 0; i < 16; i++)
        {
            if (test_result & (1 << i))
            {
                dec = i+1;
                i = 16;
            }
        }
        uint8_t ascii_dec[2];

        ascii_dec[0] = dec / 10 + '0';
        ascii_dec[1] = dec % 10 + '0';

        char problem_string[16] = "  XX detectado  ";
        problem_string[3] = ascii_dec[1];
        problem_string[2] = ascii_dec[0];
        I2C_OLED_Move_Cursor(3, 0);
        I2C_OLED_Print("                ");
        I2C_OLED_Print("Problema no pino");
        I2C_OLED_Print(problem_string);
        I2C_OLED_Print("                ");
        SysTick_Wait1ms(5000);
    }
    else
    {

        I2C_OLED_Move_Cursor(3, 0);
        I2C_OLED_Print("                ");
        I2C_OLED_Print("Nenhum problema ");
        I2C_OLED_Print("   detectado    ");
        I2C_OLED_Print("                ");
        SysTick_Wait1ms(5000);
    }
    tester_state = INIT;
}
