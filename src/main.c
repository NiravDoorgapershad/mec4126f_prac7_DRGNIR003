// Written by: Nirav Doorgapershad
// Date created: 22/04/24
// Programmed in: STM32CubeIDE
// Target: STM32F051
// Description: Practical 7

// DEFINES AND INCLUDES
#include "stm32f0xx.h"
#define TRUE 1
#define FALSE 0

// GLOBAL VARIABLES
_Bool flag = TRUE;

// FUNCTION DECLARATIONS
void ResetClockTo48Mhz(void);
void main(void);

// MAIN FUNCTION
void main(void)
{
  	ResetClockTo48Mhz();

  	while(1)
	{

	}
}

// OTHER FUNCTIONS
/* Description:
* This function resets the STM32 Clocks to 48 MHz
*
*/


void init_Timer14(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	TIM14->PSC = 47999;
	TIM14->ARR = 100;
	TIM14->DIER |= TIM_DIER_UIE;
	TIM14-> CR1 |= TIM_CR1_CEN;
	Nvic_EnableIRQ(TIM14_IRQn);
}

void TIM14_IRQHandler(void){
	TIM14->SR &= ~TIM_SR_UIF;
}

void ResetClockTo48Mhz(void)
{
    if ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL)
    {
        RCC->CFGR &= (uint32_t) (~RCC_CFGR_SW);
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
    }
    RCC->CR &= (uint32_t)(~RCC_CR_PLLON);
    while ((RCC->CR & RCC_CR_PLLRDY) != 0);
    RCC->CFGR = ((RCC->CFGR & (~0x003C0000)) | 0x00280000);
    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0);
    RCC->CFGR |= (uint32_t) (RCC_CFGR_SW_PLL);
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

// INTERRUPT HANDLERS --------------------------------------------------------|
