#include "i2c.h"

//#define DEBUG_I2C_LOOPBACK

volatile uint32_t error = 0xF0;
volatile uint32_t busy = 0xF0;
volatile uint8_t check = 0;

#ifdef DEBUG_I2C_LOOPBACK
volatile uint8_t debug_i2c_received[12];
#endif

volatile uint8_t debug_i2c_iterator = 0;
#define OLED_ADDRESS 0x33
#define OLED_CONTROL_COMMAND_BYTE 0x00
#define OLED_CONTROL_DATA_BYTE 0x40

void I2C_Init(void)
{

#ifdef DEBUG_I2C_LOOPBACK
    for (int i = 0; i < 30; i++)
    {
        debug_i2c_received[i] = 0;
    }
#endif

    //Ativa clock do módulo I2C 0
    SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0;

    //Espera até módulo 0 estar pronto para uso
    while ((SYSCTL_RCGCI2C_R & SYSCTL_RCGCI2C_R0) != SYSCTL_RCGCI2C_R0)
    {
    };

#ifdef DEBUG_I2C_LOOPBACK
    //DEBUG: Ativa função de loopback (TODO: Remover)
    I2C0_MCR_R |= I2C_MCR_LPBK;

    //DEBUG: Ativa função de slave para teste (TODO: Remover)
    I2C0_MCR_R |= I2C_MCR_SFE;

    //DEBUG: Ativa slave (TODO: Remover)
    I2C0_SCSR_R |= I2C_SCSR_DA;

    //DEBUG: Escolhe endereço de slave (TODO: Remover)
    I2C0_SOAR_R = 0xA1;
#endif

    //2*(TPR+1)*10*12,5ns = 10us -> TPR = 39 (100kbps)
    //I2C0_MTPR_R &= ~I2C_MTPR_TPR_M;
    I2C0_MTPR_R = 39;

    //Ativa função de master no módulo 0
    I2C0_MCR_R |= I2C_MCR_MFE;
}

void I2C_Oled_send_command(uint8_t command_byte)
{

    //--------Transmission of CONTROL byte--------

    //Puts address and transmit bit on the Master Slave Address Register
    I2C0_MSA_R = (OLED_ADDRESS << 1) | 0x00;

    //Writes control byte
    I2C0_MDR_R = OLED_CONTROL_COMMAND_BYTE;

    if (I2C0_MCS_R & I2C_MCS_BUSBSY)
    {
        busy++;
    }

    //Writes ---0-011 to Master Control/Status register
    I2C0_MCS_R = (I2C_MCS_ACK | I2C_MCS_START | I2C_MCS_RUN);

#ifdef DEBUG_I2C_LOOPBACK
    // while((I2C0_SCSR_R & I2C_SCSR_RREQ) != I2C_SCSR_RREQ);

    //Checks Master Control/Status register BUSY bit
    while (((check = I2C0_MCS_R) & I2C_MCS_BUSY) == I2C_MCS_BUSY)
    {
        if ((check & I2C_MCS_ADRACK) == I2C_MCS_ADRACK)
            error++;

        if ((check & I2C_MCS_DATACK) == I2C_MCS_DATACK)
            error++;
    }

    if ((check & I2C_MCS_ADRACK) == I2C_MCS_ADRACK)
        error++;

    if ((check & I2C_MCS_DATACK) == I2C_MCS_DATACK)
        error++;

    if ((check & I2C_MCS_ERROR) == I2C_MCS_ERROR)
        error++;

    debug_i2c_received[debug_i2c_iterator] = I2C0_SDR_R;

    debug_i2c_iterator++;
#else
    //Checks Master Control/Status register BUSY bit
    while (((check = I2C0_MCS_R) & I2C_MCS_BUSY) == I2C_MCS_BUSY)
    {
        if ((check & I2C_MCS_ADRACK) == I2C_MCS_ADRACK)
            error++;

        if ((check & I2C_MCS_DATACK) == I2C_MCS_DATACK)
            error++;
    }

    if ((check & I2C_MCS_ADRACK) == I2C_MCS_ADRACK)
        error++;

    if ((check & I2C_MCS_DATACK) == I2C_MCS_DATACK)
        error++;

    if ((check & I2C_MCS_ERROR) == I2C_MCS_ERROR)
        error++;

#endif

    //--------Transmission of COMMAND byte--------

    //Writes command byte
    I2C0_MDR_R = command_byte;

    //Writes  ---0-101 to Master Control/Status register
    I2C0_MCS_R = (I2C_MCS_ACK | I2C_MCS_STOP | I2C_MCS_RUN);

#ifdef DEBUG_I2C_LOOPBACK
    //while((I2C0_SCSR_R & I2C_SCSR_RREQ) != I2C_SCSR_RREQ);

    //Checks Master Control/Status register BUSY bit
    while ((check = I2C0_MCS_R & I2C_MCS_BUSY) == I2C_MCS_BUSY)
    {
        if ((check & I2C_MCS_ERROR) == I2C_MCS_ERROR)
            error++;

        if ((check & I2C_MCS_ADRACK) == I2C_MCS_ADRACK)
            error++;

        if ((check & I2C_MCS_DATACK) == I2C_MCS_DATACK)
            error++;
    }

    debug_i2c_received[debug_i2c_iterator] = I2C0_SDR_R;

    debug_i2c_iterator++;
#else
    //Checks Master Control/Status register BUSY bit
    while (((check = I2C0_MCS_R) & I2C_MCS_BUSY) == I2C_MCS_BUSY)
    {
        if ((check & I2C_MCS_ADRACK) == I2C_MCS_ADRACK)
            error++;

        if ((check & I2C_MCS_DATACK) == I2C_MCS_DATACK)
            error++;
    }

    if ((check & I2C_MCS_ADRACK) == I2C_MCS_ADRACK)
        error++;

    if ((check & I2C_MCS_DATACK) == I2C_MCS_DATACK)
        error++;

    if ((check & I2C_MCS_ERROR) == I2C_MCS_ERROR)
        error++;

#endif
}

void I2C_Oled_send_double_command(uint8_t command_byte1, uint8_t command_byte2)
{

    //--------Transmission of CONTROL byte--------

    //Puts address and transmit bit on the Master Slave Address Register
    I2C0_MSA_R = (OLED_ADDRESS << 1) | 0x00;

    //Writes control byte
    I2C0_MDR_R = OLED_CONTROL_COMMAND_BYTE;

    //Writes ---0-011 to Master Control/Status register
    I2C0_MCS_R = (I2C_MCS_START | I2C_MCS_RUN);

#ifdef DEBUG_I2C_LOOPBACK
    while ((I2C0_SCSR_R & I2C_SCSR_RREQ) != I2C_SCSR_RREQ)
        ;

    debug_i2c_received[debug_i2c_iterator] = I2C0_SDR_R;

    debug_i2c_iterator++;
#else
    //Checks Master Control/Status register BUSY bit
    while ((I2C0_MCS_R & I2C_MCS_BUSY) == I2C_MCS_BUSY)
        ;

    if ((I2C0_MCS_R & I2C_MCS_ERROR) == I2C_MCS_ERROR)
        error++;
#endif

    //--------Transmission of COMMAND byte--------

    //Writes command byte
    I2C0_MDR_R = command_byte1;

    //Writes  ---0-101 to Master Control/Status register
    I2C0_MCS_R = (I2C_MCS_RUN);

#ifdef DEBUG_I2C_LOOPBACK
    while ((I2C0_SCSR_R & I2C_SCSR_RREQ) != I2C_SCSR_RREQ)
        ;

    debug_i2c_received[debug_i2c_iterator] = I2C0_SDR_R;

    debug_i2c_iterator++;
#else
    //Checks Master Control/Status register BUSY bit
    while ((I2C0_MCS_R & I2C_MCS_BUSY) == I2C_MCS_BUSY)
        ;

    if ((I2C0_MCS_R & I2C_MCS_ERROR) == I2C_MCS_ERROR)
        error++;
#endif

    //--------Transmission of CONTROL byte 2--------

    //Writes control byte
    I2C0_MDR_R = OLED_CONTROL_COMMAND_BYTE;

    //Writes ---0-011 to Master Control/Status register
    I2C0_MCS_R = (I2C_MCS_RUN);

#ifdef DEBUG_I2C_LOOPBACK
    while ((I2C0_SCSR_R & I2C_SCSR_RREQ) != I2C_SCSR_RREQ)
        ;

    debug_i2c_received[debug_i2c_iterator] = I2C0_SDR_R;

    debug_i2c_iterator++;
#else
    //Checks Master Control/Status register BUSY bit
    while ((I2C0_MCS_R & I2C_MCS_BUSY) == I2C_MCS_BUSY)
        ;

    if ((I2C0_MCS_R & I2C_MCS_ERROR) == I2C_MCS_ERROR)
        error++;
#endif

    //--------Transmission of COMMAND byte--------

    //Writes command byte
    I2C0_MDR_R = command_byte2;

    //Writes  ---0-101 to Master Control/Status register
    I2C0_MCS_R = (I2C_MCS_STOP | I2C_MCS_RUN);

#ifdef DEBUG_I2C_LOOPBACK
    while ((I2C0_SCSR_R & I2C_SCSR_RREQ) != I2C_SCSR_RREQ)
        ;

    debug_i2c_received[debug_i2c_iterator] = I2C0_SDR_R;

    debug_i2c_iterator++;
#else
    //Checks Master Control/Status register BUSY bit
    while ((I2C0_MCS_R & I2C_MCS_BUSY) == I2C_MCS_BUSY)
        ;

    if ((I2C0_MCS_R & I2C_MCS_ERROR) == I2C_MCS_ERROR)
        error++;
#endif
}

void I2C_Oled_send_data(uint8_t data_byte)
{

    //--------Transmission of CONTROL byte--------

    I2C0_MSA_R = (OLED_ADDRESS << 1) | 0x00;

    I2C0_MDR_R = OLED_CONTROL_DATA_BYTE;

    I2C0_MCS_R = (I2C_MCS_START | I2C_MCS_RUN);

#ifdef DEBUG_I2C_LOOPBACK
    while ((I2C0_SCSR_R & I2C_SCSR_RREQ) != I2C_SCSR_RREQ)
        ;

    debug_i2c_received[debug_i2c_iterator] = I2C0_SDR_R;

    debug_i2c_iterator++;
#else
    //Checks Master Control/Status register BUSY bit
    while ((I2C0_MCS_R & I2C_MCS_BUSY) == I2C_MCS_BUSY)
        ;

    if ((I2C0_MCS_R & I2C_MCS_ERROR) == I2C_MCS_ERROR)
        error++;
#endif

    //--------Transmission of DATA byte--------

    I2C0_MDR_R = data_byte;

    I2C0_MCS_R = (I2C_MCS_STOP | I2C_MCS_RUN);

#ifdef DEBUG_I2C_LOOPBACK
    while ((I2C0_SCSR_R & I2C_SCSR_RREQ) != I2C_SCSR_RREQ)
        ;

    debug_i2c_received[debug_i2c_iterator] = I2C0_SDR_R;

    debug_i2c_iterator++;
#else
    //Checks Master Control/Status register BUSY bit
    while ((I2C0_MCS_R & I2C_MCS_BUSY) == I2C_MCS_BUSY)
        ;

    if ((I2C0_MCS_R & I2C_MCS_ERROR) == I2C_MCS_ERROR)
        error++;
#endif
}

void I2C_Oled_Init(void)
{
    // I2C_Oled_send_command(0xAE); // Set display OFF

    // I2C_Oled_send_double_command(0xD5, 0x80);
    // // I2C_Oled_send_command(0xD5); // Set Display Clock Divide Ratio / OSC Frequency
    // // I2C_Oled_send_command(0x80); // Display Clock Divide Ratio / OSC Frequency

    // I2C_Oled_send_double_command(0xA8, 0x3F);
    // I2C_Oled_send_command(0xA8); // Set Multiplex Ratio
    // I2C_Oled_send_command(0x3F); // Multiplex Ratio for 128x64 (64-1)

    // I2C_Oled_send_double_command(0xD3, 0x00);
    // // I2C_Oled_send_command(0xD3); // Set Display Offset
    // // I2C_Oled_send_command(0x00); // Display Offset

    // I2C_Oled_send_command(0x40); // Set Display Start Line

    //  I2C_Oled_send_double_command(0x8D, 0x14);
    // // I2C_Oled_send_command(0x8D); // Set Charge Pump
    // // I2C_Oled_send_command(0x14); // Charge Pump (0x10 External, 0x14 Internal DC/DC)

    //  I2C_Oled_send_double_command(0xA1, 0xC8);
    // // I2C_Oled_send_command(0xA1); // Set Segment Re-Map
    // // I2C_Oled_send_command(0xC8); // Set Com Output Scan Direction

    //  I2C_Oled_send_double_command(0xDA, 0x12);
    // // I2C_Oled_send_command(0xDA); // Set COM Hardware Configuration
    // // I2C_Oled_send_command(0x12); // COM Hardware Configuration

    //  I2C_Oled_send_double_command(0x81, 0xCF);
    // // I2C_Oled_send_command(0x81); // Set Contrast
    // // I2C_Oled_send_command(0xCF); // Contrast

    // I2C_Oled_send_double_command(0xD9, 0xF1);
    // // I2C_Oled_send_command(0xD9); // Set Pre-Charge Period
    // // I2C_Oled_send_command(0xF1); // Set Pre-Charge Period (0x22 External, 0xF1 Internal)

    // I2C_Oled_send_double_command(0xDB, 0x40);
    // // I2C_Oled_send_command(0xDB); // Set VCOMH Deselect Level
    // // I2C_Oled_send_command(0x40); // VCOMH Deselect Level

    // I2C_Oled_send_command(0xA5); // Set all pixels ON!!!!

    // I2C_Oled_send_command(0xA6); // Set display not inverted

    I2C_Oled_send_command(0xAF); // Set display On

    I2C_Oled_send_command(0xA5); // Set all pixels ON!!!!
}

void I2C_Oled_Draw(uint8_t byte)
{
    I2C_Oled_send_command(SSD1306_COLUMNADDR);
    I2C_Oled_send_command(15);
    I2C_Oled_send_command(30);

    I2C_Oled_send_command(SSD1306_PAGEADDR);
    I2C_Oled_send_command(3);
    I2C_Oled_send_command(6);

    I2C_Oled_send_data(byte);
    I2C_Oled_send_data(byte);
    I2C_Oled_send_data(byte);
    I2C_Oled_send_data(byte);
    I2C_Oled_send_data(byte);
    I2C_Oled_send_data(byte);
    I2C_Oled_send_data(byte);
    I2C_Oled_send_data(byte);
    I2C_Oled_send_data(byte);
    I2C_Oled_send_data(byte);
}
