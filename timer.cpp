/*
 * timer.cpp
 *
 *  Created on: 3 de mai de 2021
 *      Author: Marcelo
 *
 *  Timers backend for STM32
 *  Dependence CMSIS and HAL library
 *
 *  Copyright 2021 Marcelo H Moraes
 *
 *  Permission is hereby granted, free of charge,
 *  to any person obtaining a copy of this software and associated
 *  documentation files (the "Software"), to deal in the Software
 *  without restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom
 *  the Software is furnished to do so, subject to the following conditions:
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 *
 */

#include <timer.h>
#include "timer_mapping.cpp" /* Keep your variable near and your vector closer */

#ifdef __cplusplus
extern "C" {
#endif

TIM_TypeDef* timerAddr(timerHW_t timer) {
	return (TIM_TypeDef*)timer_mapping[timer].addr;
}

uint16_t timerFunction(timerHW_t timer) {
	return timer_mapping[timer].function;
}

#if defined STM32F722xx || defined STM32F407xx
alternative_t timerAF(timerHW_t timer) {
	return timer_mapping[timer].af;
}
#endif

gpioPIN_t timerChannel1(timerHW_t timer) {
	return timer_mapping[timer].channel1;
}

gpioPIN_t timerChannel2(timerHW_t timer) {
	return timer_mapping[timer].channel2;
}

gpioPIN_t timerChannel3(timerHW_t timer) {
	return timer_mapping[timer].channel3;
}

gpioPIN_t timerChannel4(timerHW_t timer) {
	return timer_mapping[timer].channel4;
}

gpioPIN_t timerChannel1n(timerHW_t timer) {
	return timer_mapping[timer].channel1n;
}

gpioPIN_t timerChannel2n(timerHW_t timer) {
	return timer_mapping[timer].channel2n;
}

gpioPIN_t timerChannel3n(timerHW_t timer) {
	return timer_mapping[timer].channel3n;
}

uint8_t timerEnable(timerHW_t timer, timerINT_t interrupt) {
	uint8_t timerClockDiv = 0;
	switch(timer) {
#ifdef TIM1_BASE
	case TIMER1:
		__HAL_RCC_TIM1_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 0;
#endif
		if(interrupt == interruptENABLE) {
#ifdef STM32F103xB
		HAL_NVIC_SetPriority(TIM1_UP_IRQn, 4, 1);
		HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
#endif
#if defined STM32F722xx || defined STM32F407xx
			HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
#endif
		}
		break;
#endif
#ifdef TIM2_BASE
	case TIMER2:
		__HAL_RCC_TIM2_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 1;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM2_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM2_IRQn);
		}
		break;
#endif
#ifdef TIM3_BASE
	case TIMER3:
		__HAL_RCC_TIM3_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 1;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM3_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM3_IRQn);
		}
		break;
#endif
#ifdef TIM4_BASE
	case TIMER4:
		__HAL_RCC_TIM4_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 1;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM4_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM4_IRQn);
		}
		break;
#endif
#ifdef TIM5_BASE
	case TIMER5:
		__HAL_RCC_TIM5_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 1;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM5_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM5_IRQn);
		}
		break;
#endif
#ifdef TIM6_BASE
	case TIMER6:
		__HAL_RCC_TIM6_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 1;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
		}
		break;
#endif
#ifdef TIM7_BASE
	case TIMER7:
		__HAL_RCC_TIM7_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 1;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM7_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM7_IRQn);
		}
		break;
#endif
#ifdef TIM8_BASE
	case TIMER8:
		__HAL_RCC_TIM8_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 0;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
		}
		break;
#endif
#ifdef TIM9_BASE
	case TIMER9:
		__HAL_RCC_TIM9_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 0;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);
		}
		break;
#endif
#ifdef TIM10_BASE
	case TIMER10:
		__HAL_RCC_TIM10_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 0;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
		}
		break;
#endif
#ifdef TIM11_BASE
	case TIMER11:
		__HAL_RCC_TIM11_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 0;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
		}
		break;
#endif
#ifdef TIM12_BASE
	case TIMER12:
		__HAL_RCC_TIM12_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 1;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
		}
		break;
#endif
#ifdef TIM13_BASE
	case TIMER13:
		__HAL_RCC_TIM13_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 1;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM8_UP_TIM13_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
		}
		break;
#endif
#ifdef TIM14_BASE
	case TIMER14:
		__HAL_RCC_TIM14_CLK_ENABLE();
#ifdef STM32F103xB
		timerClockDiv = 0;
#endif
#ifdef STM32F407xx
		timerClockDiv = 0;
#endif
#ifdef STM32F722xx
		timerClockDiv = 1;
#endif
		if(interrupt == interruptENABLE) {
			HAL_NVIC_SetPriority(TIM8_TRG_COM_TIM14_IRQn, 4, 1);
			HAL_NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);
		}
		break;
#endif
	}
	return timerClockDiv;
}

void timerDisable(timerHW_t timer) {
	switch(timer) {
#ifdef TIM1_BASE
	case TIMER1:
#ifdef STM32F103xB
		HAL_NVIC_DisableIRQ(TIM1_UP_IRQn);
		__HAL_RCC_TIM1_CLK_DISABLE();
#endif
#if defined STM32F722xx || defined STM32F407xx
		HAL_NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
		__HAL_RCC_TIM1_CLK_DISABLE();
#endif
		break;
#endif
#ifdef TIM2_BASE
	case TIMER2:
		__HAL_RCC_TIM2_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM2_IRQn);
		break;
#endif
#ifdef TIM3_BASE
	case TIMER3:
		__HAL_RCC_TIM3_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM3_IRQn);
		break;
#endif
#ifdef TIM4_BASE
	case TIMER4:
		__HAL_RCC_TIM4_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM4_IRQn);
		break;
#endif
#ifdef TIM5_BASE
	case TIMER5:
		__HAL_RCC_TIM5_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM5_IRQn);
		break;
#endif
#ifdef TIM6_BASE
	case TIMER6:
		__HAL_RCC_TIM6_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
		break;
#endif
#ifdef TIM7_BASE
	case TIMER7:
		__HAL_RCC_TIM7_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM7_IRQn);
		break;
#endif
#ifdef TIM8_BASE
	case TIMER8:
		__HAL_RCC_TIM8_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM8_UP_TIM13_IRQn);
		break;
#endif
#ifdef TIM9_BASE
	case TIMER9:
		__HAL_RCC_TIM9_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM1_BRK_TIM9_IRQn);
		break;
#endif
#ifdef TIM10_BASE
	case TIMER10:
		__HAL_RCC_TIM10_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
		break;
#endif
#ifdef TIM11_BASE
	case TIMER11:
		__HAL_RCC_TIM11_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM1_TRG_COM_TIM11_IRQn);
		break;
#endif
#ifdef TIM12_BASE
	case TIMER12:
		__HAL_RCC_TIM12_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM8_BRK_TIM12_IRQn);
		break;
#endif
#ifdef TIM13_BASE
	case TIMER13:
		__HAL_RCC_TIM13_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM8_UP_TIM13_IRQn);
		break;
#endif
#ifdef TIM14_BASE
	case TIMER14:
		__HAL_RCC_TIM14_CLK_DISABLE();
		HAL_NVIC_DisableIRQ(TIM8_TRG_COM_TIM14_IRQn);
		break;
#endif
	}
}

#ifdef __cplusplus
}
#endif
