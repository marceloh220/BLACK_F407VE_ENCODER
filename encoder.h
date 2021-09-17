/*
MIT License

Copyright (c) 2019 Marcelo Henrique Moraes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <stdint.h>

#include <gpio.h>
#include <utils.h>

#ifdef STM32F103xE
#include "stm32f1xx.h"
#endif
#ifdef STM32F407xx
#include "stm32f4xx_hal_tim.h"
#endif
#ifdef STM32F722xx
#include "stm32f7xx_hal_tim.h"
#endif

typedef enum {
	UNLOCK,
	LOCK,
	NOACTION,
	ACTION,
	LOCK_OTHER_ID,
} encoderState_t;

typedef struct {
	TIM_TypeDef* timer;
	uint8_t id;
	uint16_t value;
	uint8_t encoderSTATE;
	gpioPIN_t button;
	uint8_t buttonLock;
	uint8_t buttonState;
} encoder_t;

class Encoder
{

private:

	encoder_t encoder;

	void begin(uint8_t timer);
	void write(uint16_t value);
	uint16_t read();
	uint8_t overflow();
	uint32_t buttonTime();

public:

	Encoder(timerHW_t timer, gpioPIN_t pin);

	/* Once a variable read they are attached to encoder
	 * To release the encoder to be attached to another variable
	 * is necessary use the method   void detached(void) */
	encoderState_t read(uint8_t *val, uint8_t min, uint8_t max, uint8_t id);
	encoderState_t read(uint16_t *val, uint16_t min, uint16_t max, uint8_t id);
	encoderState_t read(float *val, float max, uint8_t id);
	void detached();

	/* Once read the button will do only one action until be released
	 * This method have software debounce without delay loops
	 * Using the systick timer to avoid dead time in cpu */
	uint8_t button(uint32_t debounce);
	/* Read the button pin directly without any other software interferences */
	uint8_t buttonPin();

};

#endif
