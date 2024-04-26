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

void init_Timer3(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;//enable clock for PB
	GPIOB->MODER |= GPIO_MODER_MODER4_1|GPIO_MODER_MODER5_1|GPIO_MODER_MODER0_1|GPIO_MODER_MODER1_1;
	GPIOB->AFR[0] |= 0x01 <<(4*4);
	GPIOB->AFR[0] |= 0x01 <<(4*5);
	GPIOB->AFR[0] |= 0x01 <<(0*4);
	GPIOB->AFR[0] |= 0x01 <<(1*4);

	TIM3->PSC = 23;
	TIM3->ARR = 99;
	TIM3->CCR1 =50;
	TIM3->CCR2 = TIM3->CCR1;
	TIM3->CCR3 =50;
	TIM3->CCR4 = TIM3->CCR3;

	TIM3-> CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
	TIM3-> CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE|TIM_CCMR1_OC2M_0;
	TIM3-> CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE;
	TIM3-> CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE|TIM_CCMR2_OC4M_0;

	TIM3->CCER |= TIM_CCER_CC1E|TIM_CCER_CC2E|TIM_CCER_CC3E|TIM_CCER_CC4E;
	TIM3->CR1 |= TIM_CR1_CEN;

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
