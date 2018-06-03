// gpio.c
// Marcelo Fernandes e Bruno Colombo


#include "gpio.h"

#define GPIO_PORT_A 0x0001
#define GPIO_PORT_B 0x0002
#define GPIO_PORT_C 0x0004
#define GPIO_PORT_D 0x0008
#define GPIO_PORT_E 0x0010
#define GPIO_PORT_F 0x0020
#define GPIO_PORT_G 0x0040
#define GPIO_PORT_H 0x0080
#define GPIO_PORT_J 0x0100
#define GPIO_PORT_K 0x0200
#define GPIO_PORT_L 0x0400
#define GPIO_PORT_M 0x0800
#define GPIO_PORT_N 0x1000

#define GPIO_PORTS (GPIO_PORT_B|GPIO_PORT_D|GPIO_PORT_M)

#define GPIO_PORTD_KB_ROWS      (*((volatile uint32_t *)0x4005B03C))
#define GPIO_PORTM_KB_COLUMNS   (*((volatile uint32_t *)0x400631E0))


 /*
  * Inicializa todas as portas de GPIO que serão utilizadas no projeto.
  */
void GPIO_Init(void)
{
    // 1a. Ativar o clock para a porta setando o bit correspondente no registrador RCGCGPIO
    SYSCTL_RCGCGPIO_R |= GPIO_PORTS;

    // 1b.   após isso verificar no PRGPIO se a porta está pronta para uso.
      while((SYSCTL_PRGPIO_R & (GPIO_PORTS) ) != (GPIO_PORTS) ){};

    // 2. Destravar a porta somente se for o pino PD7 e PE7

    // 3. Limpar o AMSEL para desabilitar a analógica
    GPIO_PORTB_AHB_AMSEL_R  = 0x00;
    GPIO_PORTD_AHB_AMSEL_R	= 0x00;
    GPIO_PORTM_AMSEL_R		= 0x00;

    // 4. Limpar PCTL para selecionar o GPIO
    GPIO_PORTB_AHB_PCTL_R   = 0x2200;
    GPIO_PORTD_AHB_PCTL_R	= 0x00;
    GPIO_PORTM_PCTL_R		= 0x00;

    // 5. DIR para 0 se for entrada, 1 se for saída
    GPIO_PORTD_AHB_DIR_R	= 0x00;
    GPIO_PORTM_DIR_R		= 0x7F;

    // 6. Limpar os bits AFSEL para 0 para selecionar GPIO sem função alternativa
    GPIO_PORTB_AHB_AFSEL_R  = 0x0C;
    GPIO_PORTD_AHB_AFSEL_R	= 0x00;
    GPIO_PORTM_AFSEL_R		= 0x00;


    // 7. Setar os bits de DEN para habilitar I/O digital
    GPIO_PORTB_AHB_DEN_R    = 0x04;
    GPIO_PORTD_AHB_DEN_R	= 0x0F;
    GPIO_PORTM_DEN_R		= 0x7F;

    // 8. Habilitar resistor de pull-up interno, setar PUR para 1
    GPIO_PORTD_AHB_PUR_R	= 0x0F;

    // 9. Registrador de Dreno Aberto
    GPIO_PORTB_AHB_ODR_R    = 0x08;
}

uint32_t PortD_Input(void)
{
    return GPIO_PORTD_KB_ROWS;
}

void PortM_OutputKeyboard(uint32_t value)
{
    GPIO_PORTM_KB_COLUMNS = value;
}
