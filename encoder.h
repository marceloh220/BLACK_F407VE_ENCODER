/**  
* @file encoder.h  
* @brief Hardware encoder to STM32F407VE.
*  
* @author Marcelo H Moraes 
* 
* @date 09/18/2021
* Copyright (c) 2021, Marcelo H Moraes
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
*
* You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
* either express or implied.
*
* See the License for the specific language governing permissions and limitations under the License.
*/

#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <cstdint>
#include <stdint.h>

#include "mbed.h"
#include "channels_pair.h"

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
	uint8_t buttonLock;
	uint8_t buttonState;
    uint32_t buttonTime;
} encoder_t;

class Encoder
{

private:

	DigitalIn _button;
	encoder_t encoder;

	void begin(uint8_t timer);
	void write(uint16_t value);
	uint16_t read();
	uint8_t overflow();
	uint32_t buttonTime();

public:

	Encoder(ENCODERName_t encoderName, PinName button, PinMode buttonMode = PullUp);

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
	uint8_t button();

};

#endif
