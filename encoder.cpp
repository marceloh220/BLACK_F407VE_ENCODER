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

#include <encoder.h>
#include <timer.h>
#include <gpio.h>

static uint32_t ENCODER_BUTTON_TIME = 0;

#define ENCODER_BUTTON_INPUT	(*encoder.button)

/*---Common functions---*/
#ifdef STM32F103xB
void encoderGPIO_Init(gpioPIN_t channel1, gpioPIN_t channel2, gpioPIN_t button);
#endif
#if defined STM32F722xx || defined STM32F407xx
void encoderGPIO_Init(gpioPIN_t channel1, gpioPIN_t channel2, gpioPIN_t button, alternative_t af);
#endif
static void encoderTIMER_Init(timerHW_t timer);

/*---Constructor---*/
Encoder::Encoder(timerHW_t timer, gpioPIN_t button)
{
	if(timerFunction(timer) & ENCODER) {
		encoder.timer =  timerAddr(timer);
		encoder.button = button;
		timerEnable(timer);
#ifdef STM32F103xB
		encoderGPIO_Init(timerChannel1(timer), timerChannel2(timer), encoder.button);
#endif
#if defined STM32F722xx || defined STM32F407xx
	encoderGPIO_Init(timerChannel1(timer), timerChannel2(timer), encoder.button, timerAF(timer));
#endif
		encoderTIMER_Init(timer);
	}
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
	return HAL_GetTick() - ENCODER_BUTTON_TIME;
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
		if(gpio.read(encoder.button)) {
			ENCODER_BUTTON_TIME = HAL_GetTick();
			encoder.buttonLock = LOCK;
			return 1;
		}
	}
	else if(buttonTime() > debounce && !gpio.read(encoder.button)) {
		encoder.buttonLock = 0;
	}
	return 0;
}

uint8_t Encoder::buttonPin() {
	return gpio.read(encoder.button);
}

#ifdef STM32F103xB
void encoderGPIO_Init(gpioPIN_t channel1, gpioPIN_t channel2, gpioPIN_t button_encoder) {
#endif
#if defined STM32F722xx || defined STM32F407xx
void encoderGPIO_Init(gpioPIN_t channel1, gpioPIN_t channel2, gpioPIN_t button_encoder, alternative_t af) {
#endif
	gpio.mode(button_encoder, INPUT_PULLUP);
#ifdef STM32F103xB
	gpio.mode(channel1, INPUT_PULLUP);
	gpio.mode(channel2, INPUT_PULLUP);
#endif
#if defined STM32F722xx || defined STM32F407xx
	gpio.mode(channel1, ALTERNATIVE_PULLUP, GPIO_FAST, af);
	gpio.mode(channel2, ALTERNATIVE_PULLUP, GPIO_FAST, af);
#endif
}

void encoderTIMER_Init(timerHW_t timer) {
	TIM_TypeDef* htimer = timerAddr(timer);
	htimer->ARR = 0xFFFFFFFF;
	htimer->CCMR1 |= (TIM_CCMR1_CC1S_0|TIM_CCMR1_CC2S_0|
			(0xF<<TIM_CCMR1_IC1F_Pos)|(0xF<<TIM_CCMR1_IC2F_Pos));
	htimer->PSC = 0;
	htimer->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
	htimer->SMCR |= (TIM_SMCR_SMS_0|TIM_SMCR_SMS_1);
	htimer->CR1 |= TIM_CR1_CEN;
}
