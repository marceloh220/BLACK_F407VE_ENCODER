/*
 * timer_mapping.cpp
 *
 *  Created on: 3 de mai de 2021
 *      Author: Marcelo
 *
 *  Timers mapping for STM32
 *  It has register address, pins IO's and function capabilities to each timer
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

#ifdef __cplusplus
extern "C" {
#endif

/* The map for the treasure of Timer
 * Every Timer have they function and every function have they pins
 * This map is for STM32F722ZE mcu, I need to make another map for mcu 103 and 407.
 * I will do it, I swear. Or maybe you can do this! */
const timerMAPPING_t timer_mapping[] {
#ifdef TIM1_BASE
		{
				TIM1_BASE,
				COUNTER|ENCODER|
				PWM_CHANNEL1|PWM_CHANNEL2|PWM_CHANNEL3|PWM_CHANNEL4|
				PWM_CHANNEL1N|PWM_CHANNEL2N|PWM_CHANNEL3N|
				CAPT_CHANNEL1|CAPT_CHANNEL2|CAPT_CHANNEL3|CAPT_CHANNEL4,
#ifndef STM32F103xB
				AF1_TIMER1,
#endif
#ifdef STM32F103xB
				PA8, PA9, PA10, PA11, PA7, PB0, PB1
#endif
#if defined STM32F722xx || defined STM32F407xx
				PE9, PE11, PE13, PE14, PA7, PB0, PB1
#endif
		},
#endif
#ifdef TIM2_BASE
		{
				TIM2_BASE,
				COUNTER|ENCODER|
				PWM_CHANNEL1|PWM_CHANNEL2|PWM_CHANNEL3|PWM_CHANNEL4|
				CAPT_CHANNEL1|CAPT_CHANNEL2|CAPT_CHANNEL3|CAPT_CHANNEL4,
#ifndef STM32F103xB
				AF1_TIMER2,
#endif
				PA0, PA1, PA2, PA3, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM3_BASE
		{
				TIM3_BASE,
				COUNTER|ENCODER|
				PWM_CHANNEL1|PWM_CHANNEL2|PWM_CHANNEL3|PWM_CHANNEL4|
				CAPT_CHANNEL1|CAPT_CHANNEL2|CAPT_CHANNEL3|CAPT_CHANNEL4,
#ifndef STM32F103xB
				AF2_TIMER3,
#endif
				PA6, PA7, PB0, PB1, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM4_BASE
		{
				TIM4_BASE,
				COUNTER|ENCODER|
				PWM_CHANNEL1|PWM_CHANNEL2|PWM_CHANNEL3|PWM_CHANNEL4|
				CAPT_CHANNEL1|CAPT_CHANNEL2|CAPT_CHANNEL3|CAPT_CHANNEL4,
#ifndef STM32F103xB
				AF2_TIMER4,
#endif
#ifdef STM32F103xB
				PB6, PB7, PB8, PB9, PNULL, PNULL, PNULL
#endif
#if defined STM32F722xx || defined STM32F407xx
				PD12, PD13, PD14, PD15, PNULL, PNULL, PNULL
#endif
		},
#endif
#ifdef TIM5_BASE
		{
				TIM5_BASE,
				COUNTER|ENCODER|
				PWM_CHANNEL1|PWM_CHANNEL2|PWM_CHANNEL3|PWM_CHANNEL4|
				CAPT_CHANNEL1|CAPT_CHANNEL2|CAPT_CHANNEL3|CAPT_CHANNEL4,
				AF2_TIMER5,
				PA0, PA1, PA2, PA3, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM6_BASE
		{
				TIM6_BASE,
				COUNTER,
				AFNULL,
				PNULL, PNULL, PNULL, PNULL, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM7_BASE
		{
				TIM7_BASE,
				COUNTER,
				AFNULL,
				PNULL, PNULL, PNULL, PNULL, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM8_BASE
		{
				TIM8_BASE,
				COUNTER|ENCODER|
				PWM_CHANNEL1|PWM_CHANNEL2|PWM_CHANNEL3|PWM_CHANNEL4|
				PWM_CHANNEL1N|PWM_CHANNEL2N|PWM_CHANNEL3N|
				CAPT_CHANNEL1|CAPT_CHANNEL2|CAPT_CHANNEL3|CAPT_CHANNEL4,
				AF3_TIMER8,
				PC6, PC7, PC8, PC9, PA5, PB0, PB1
		},
#endif
#ifdef TIM9_BASE
		{
				TIM9_BASE,
				COUNTER|
				PWM_CHANNEL1|PWM_CHANNEL2|
				CAPT_CHANNEL1|CAPT_CHANNEL2,
				AF3_TIMER9,
				PE5, PE6, PNULL, PNULL, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM10_BASE
		{
				TIM10_BASE,
				COUNTER|
				PWM_CHANNEL1|
				CAPT_CHANNEL1,
				AF3_TIMER10,
				PF6, PNULL, PNULL, PNULL, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM11_BASE
		{
				TIM11_BASE,
				COUNTER|
				PWM_CHANNEL1|
				CAPT_CHANNEL1,
				AF3_TIMER11,
				PF7, PNULL, PNULL, PNULL, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM12_BASE
		{
				TIM12_BASE,
				COUNTER|
				PWM_CHANNEL1|PWM_CHANNEL2|
				CAPT_CHANNEL1|CAPT_CHANNEL2,
				AF9_TIM12,
				PB14, PB15, PNULL, PNULL, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM13_BASE
		{
				TIM13_BASE,
				COUNTER|
				PWM_CHANNEL1|
				CAPT_CHANNEL1,
				AF9_TIM13,
				PF8, PNULL, PNULL, PNULL, PNULL, PNULL, PNULL
		},
#endif
#ifdef TIM14_BASE
		{
				TIM14_BASE,
				COUNTER|
				PWM_CHANNEL1|
				CAPT_CHANNEL1,
				AF9_TIM14,
				PF9, PNULL, PNULL, PNULL, PNULL, PNULL, PNULL
		},
#endif
};

#ifdef __cplusplus
}
#endif
