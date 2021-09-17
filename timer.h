/*
 * timer.h
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

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <utils.h>
#include <gpio.h>

#ifdef __cplusplus
extern "C" {
#endif

TIM_TypeDef* timerAddr(timerHW_t timer); /* Get timer address */
uint16_t timerFunction(timerHW_t timer); /* Get timer functions available */
#if defined STM32F722xx || defined STM32F407xx
alternative_t timerAF(timerHW_t timer); /* In case of STM32F7 is need put the gpio in alternative function mode */
#endif
gpioPIN_t timerChannel1(timerHW_t timer); /* Say who is the channel one pin. Say mother [BEEP]! */
gpioPIN_t timerChannel2(timerHW_t timer); /* Get channel two pin */
gpioPIN_t timerChannel3(timerHW_t timer); /* Get channel three pin */
gpioPIN_t timerChannel4(timerHW_t timer); /* Get channel four pin */
gpioPIN_t timerChannel1n(timerHW_t timer); /* Get channel one inverted pin */
gpioPIN_t timerChannel2n(timerHW_t timer); /* Get channel two inverted pin */
gpioPIN_t timerChannel3n(timerHW_t timer); /* Get channel three inverted pin */
uint8_t timerEnable(timerHW_t timer, timerINT_t interrupt = interruptDISABLE); /* Disable timer clock timer */
void timerDisable(timerHW_t timer); /* Enable timer clock timer */
/* Ok this is just a joke
 * The timerEnable enable clock timer, enable, or not, the interrupt UP time and return if it have a clock divisor
 * The disable make a coffee, black, without sugar. The beverage not the musician. */

#ifdef __cplusplus
}
#endif

#endif /* INC_TIMER_H_ */
