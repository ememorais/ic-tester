#include "timer.h"

// -----------------------------------------------------------------------------
// FunÃ§Ã£o Timer_Init
//--------------------------------
// Inicializa Timer 0 no modo A (32 bits) e com interrupÃ§Ã£o a cada 200 us.
// -----------------------------------------------------------------------------
void Timer_Init(void)
{
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;

    while ((SYSCTL_RCGCTIMER_R & SYSCTL_RCGCTIMER_R0) != SYSCTL_RCGCTIMER_R0){};

    TIMER0_CTL_R &= ~0x01;

    TIMER0_CFG_R = 0x00;

    TIMER0_TAMR_R &= ~0x03;
    TIMER0_TAMR_R |= 0x02;

    //TIMER0_TAILR_R  = 0x00013880; //= 1ms * 80e6hz

    TIMER0_TAILR_R = 0x00003E80; //=200us * 80e6hz

    TIMER0_ICR_R |= 0x01;

    TIMER0_IMR_R |= 0x01;

    NVIC_PRI4_R &= ~0xE0000000;

    NVIC_EN0_R |= 0x80000;

    TIMER0_CTL_R |= 0x01;
}

// -----------------------------------------------------------------------------
// Função Timer0A_Handler
//--------------------------------
// Interrupção gerada pelo Timer 0
// -----------------------------------------------------------------------------
void Timer0A_Handler(void)
{
		TIMER0_ICR_R |= 0x01;
}
