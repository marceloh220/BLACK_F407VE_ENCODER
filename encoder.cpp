/**  
* @file encoder.cpp 
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

#include "encoder.h"
#include "encoder_mapping.cpp"
#include <cstdint>

static void encoderTIMER_Init(uint32_t timer);

/*---Constructor---*/
Encoder::Encoder(ENCODERName_t encoderName, PinName button, PinMode buttonMode): _button(button, buttonMode)
{
    ENCODERChannels_t encoderChannels = encoderPins[encoderName];
    PinMap channel1 = PinMap_ENCODER[encoderChannels.channel1];
    PinMap channel2 = PinMap_ENCODER[encoderChannels.channel2];
	encoder.timer =  (TIM_TypeDef*)channel1.peripheral;
    // Enable TIM clock
    encoderTIMER_Init(channel1.peripheral);
    pin_function(channel1.pin, channel1.function);
    pin_function(channel2.pin, channel2.function);
}

/*-----Privates------*/
inline void Encoder::write(uint16_t value)
{
	encoder.timer->CNT = value << 2;
}

inline uint16_t Encoder::read()
{
	return (int16_t)encoder.timer->CNT >> 2;
}

uint8_t Encoder::overflow()
{
	return (encoder.timer->CNT > (uint16_t)65000U) ? 1 : 0;
}

uint32_t Encoder::buttonTime()
{
	return HAL_GetTick() - encoder.buttonTime;
}

/*---Read methods---*/
encoderState_t Encoder::read(uint8_t *value, uint8_t min, uint8_t max, uint8_t id)
{
	uint8_t temp;
	if(this->encoder.encoderSTATE == UNLOCK)
	{
		this->write(*value);
		this->encoder.id = id;
		this->encoder.encoderSTATE = LOCK;
	}
	else if(this->encoder.encoderSTATE == LOCK)
	{
		if(this->encoder.id != id) {
			return LOCK_OTHER_ID;
		}
		else {
			temp = this->read();
			if (temp < min || this->overflow())
			{
				temp = max;
				this->write(max);
			}
			else if (temp > max)
			{
				temp = min;
				this->write(min);
			}
			if(*value != temp) {
				*value = temp;
				return ACTION;
			}
			else {
				return NOACTION;
			}
		}
	}
	return NOACTION;
}

encoderState_t Encoder::read(uint16_t *value, uint16_t min, uint16_t max, uint8_t id)
{
	uint16_t temp;
	if (this->encoder.encoderSTATE == UNLOCK)
	{
		this->write(*value);
		this->encoder.id = id;
		this->encoder.encoderSTATE = LOCK;
	}
	if (this->encoder.encoderSTATE == LOCK)
	{
		if(this->encoder.id != id) {
			return LOCK_OTHER_ID;
		}
		else {
			temp = read();
			if (temp < min || overflow())
			{
				temp = max;
				write(max);
			}
			else if (temp > max)
			{
				temp = min;
				write(min);
			}
			if(*value != temp) {
				*value = temp;
				return ACTION;
			}
			else {
				return NOACTION;
			}
		}
	}
	return NOACTION;
}

encoderState_t Encoder::read(float *value, float max, uint8_t id)
{
	volatile float ant;
	volatile int16_t decimal;
	volatile int32_t inteiro;

	inteiro = (int32_t)*value;
	ant = *value - inteiro;
	decimal = (int16_t)(ant * 1000.0F);
	if (decimal % 10 > 5)
	{
		decimal /= 10.0f;
		decimal++;
	}
	else
	{
		decimal /= 10.0f;
	}

	ant = *value;

	if (this->encoder.encoderSTATE == UNLOCK)
	{
		write(decimal);
		this->encoder.id = id;
		this->encoder.encoderSTATE = LOCK;
	}
	if (this->encoder.id == id)
	{
		decimal = read();

		if (decimal > 99)
		{
			inteiro++;
			decimal = 0;
			write((uint16_t)decimal);
		}
		else if (decimal < 0)
		{
			inteiro--;
			decimal = 99;
			if(inteiro < 0) {
				inteiro = (int32_t)max;
				decimal = (int32_t)((max - inteiro) * 100.0F);
			}
			write((uint16_t)decimal);
		}

		*value = (inteiro + (decimal / 100.0F));
		if (*value > max)
		{
			inteiro = 0;
			decimal = 0;
			write(0);
			*value = 0;
		}

		return *value != ant ? ACTION : NOACTION;
	}
	else
		return NOACTION;
}


/*---Release encoder from a variable---*/
void Encoder::detached()
{
	encoder.timer->CNT = 0;
	encoder.timer->ARR = 0xFFFF;
	encoder.encoderSTATE = UNLOCK;
	encoder.id = 0;
}

uint8_t Encoder::button(uint32_t debounce)
{
	if (encoder.buttonLock == UNLOCK)
	{
		if(_button) {
			encoder.buttonTime = HAL_GetTick();
			encoder.buttonLock = LOCK;
			return 1;
		}
	}
	else if(buttonTime() > debounce && !_button) {
		encoder.buttonLock = 0;
	}
	return 0;
}

uint8_t Encoder::button() {
	return _button;
}

void encoderTIMER_Init(uint32_t timer) {
#if defined(TIM1_BASE)
    if (timer == ENCODER_1) {
        __HAL_RCC_TIM1_CLK_ENABLE();
    }
#endif
#if defined(TIM2_BASE)
    else if (timer == ENCODER_2) {
        __HAL_RCC_TIM2_CLK_ENABLE();
    }
#endif
#if defined(TIM3_BASE)
    else if (timer == ENCODER_3) {
        __HAL_RCC_TIM3_CLK_ENABLE();
    }
#endif
#if defined(TIM4_BASE)
    else if (timer == ENCODER_4) {
        __HAL_RCC_TIM4_CLK_ENABLE();
    }
#endif
#if defined(TIM5_BASE)
    else if (timer == ENCODER_5) {
        __HAL_RCC_TIM5_CLK_ENABLE();
    }
#endif
#if defined(TIM8_BASE)
    else if (timer == ENCODER_8) {
        __HAL_RCC_TIM8_CLK_ENABLE();
    }
#endif
#if defined(TIM9_BASE)
    else if (timer == ENCODER_9) {
        __HAL_RCC_TIM9_CLK_ENABLE();
    }
#endif
#if defined(TIM10_BASE)
    else if (timer == ENCODER_10) {
        __HAL_RCC_TIM10_CLK_ENABLE();
    }
#endif
#if defined(TIM11_BASE)
    else if (timer == ENCODER_11) {
        __HAL_RCC_TIM11_CLK_ENABLE();
    }
#endif
#if defined(TIM12_BASE)
    else if (timer == ENCODER_12) {
        __HAL_RCC_TIM12_CLK_ENABLE();
    }
#endif
#if defined(TIM13_BASE)
    else if (timer == ENCODER_13) {
        __HAL_RCC_TIM13_CLK_ENABLE();
    }
#endif
#if defined(TIM14_BASE)
    else if (timer == ENCODER_14) {
        __HAL_RCC_TIM14_CLK_ENABLE();
    }
#endif
#if defined(TIM15_BASE)
    else if (timer == ENCODER_15) {
        __HAL_RCC_TIM15_CLK_ENABLE();
    }
#endif
#if defined(TIM16_BASE)
    else if (timer == ENCODER_16) {
        __HAL_RCC_TIM16_CLK_ENABLE();
    }
#endif
#if defined(TIM17_BASE)
    else if (timer == ENCODER_17) {
        __HAL_RCC_TIM17_CLK_ENABLE();
    }
#endif
#if defined(TIM18_BASE)
    else if (timer == ENCODER_18) {
        __HAL_RCC_TIM18_CLK_ENABLE();
    }
#endif
#if defined(TIM19_BASE)
    else if (timer == ENCODER_19) {
        __HAL_RCC_TIM19_CLK_ENABLE();
    }
#endif
#if defined(TIM20_BASE)
    else if (timer == ENCODER_20) {
        __HAL_RCC_TIM20_CLK_ENABLE();
    }
#endif
#if defined(TIM21_BASE)
    else if (timer == ENCODER_21) {
        __HAL_RCC_TIM21_CLK_ENABLE();
    }
#endif
#if defined(TIM22_BASE)
    else if (timer == ENCODER_22) {
        __HAL_RCC_TIM22_CLK_ENABLE();
    }
#endif
	TIM_TypeDef* htimer = (TIM_TypeDef*)timer;
	htimer->ARR = 0xFFFFFFFF;
	htimer->CCMR1 |= (TIM_CCMR1_CC1S_0|TIM_CCMR1_CC2S_0|
			(0xF<<TIM_CCMR1_IC1F_Pos)|(0xF<<TIM_CCMR1_IC2F_Pos));
	htimer->PSC = 0;
	htimer->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
	htimer->SMCR |= (TIM_SMCR_SMS_0|TIM_SMCR_SMS_1);
	htimer->CR1 |= TIM_CR1_CEN;
}
