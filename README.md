# BLACK_F407VE_ENCODER
 
 Quadrature Wise Encoder Rotary Timer Yet (QWERTY), for people whose external interrupt is not enough!\
 The Hardware TIMER use a specific pair of pins to read the Quadrature Encoder.\
 The supported pairs are defined in [encoderPairs_t](https://github.com/marceloh220/BLACK_F407VE_ENCODER/blob/main/channels_pair.h)
 
 This library uses hardware timer to read a quadrature rotary encoder.\
 Using the revolutionary method ASSigned Variable Isolation Only Laterally ATtached Edit Deterministic (*ASSVIOLATED*)\
 to attach a variable at encoder using a unique ID
 - __encoderState_t read(uint8_t* var, uint8_t min, uint8_t max, encoderID_t ID)__
 - __encoderState_t read(uint16_t* var, uint16_t min, uint16_t max, encoderID_t ID)__
 - __encoderState_t read(float* var, float min, float max, encoderID_t ID)__
 
 Read method will return **ACTION** if variable in timer change and **LOCK_OTHER_ID** if other variable are attached\
 Once read, the variable stay attached at timer until be detached with **void detach(void)** method.
 
 This library provide a button read method for the Quadrature Encoder which have a button.\
 The method **uint8_t button(uint32_t debounce)** use a Button Unit Target Time Hysteresis Once Less Equivocate (*BUTTHOLE*)\
 This made the read of button once less equivocate using hysteresis time with unit target.\
 In other words, the reading of button will be executed one time pressed and no more, made the equivocals reading buttons be things of pass.
 
 Why to use:
 - Use a timer to read one quadrature encoder will be much more precise and have more confiabilitie
 - The CPU will not be interrupt-blocked as in traditional read using the external interrupt method
 - The attachment provided by the ASSVIOLATED method can be easily used to modify differents variables with a single quadrature encoder hardware
 - The BUTTHOLE method will read the button encoder precisely and be less equivocate
 
 Why NOT use:
 - The pins usable is hardware limited to defineds pairs
 - Using a timer some pins will be unavailable to be used as pwm generator or to input capture
 - For now only support STM32F407xx, for other STM's target support need change the 
 [encoder mapping](https://github.com/marceloh220/BLACK_F407VE_ENCODER/blob/main/encoder_mapping.cpp) and maybe 
 [channels pair](https://github.com/marceloh220/BLACK_F407VE_ENCODER/blob/main/channels_pair.h)
 
 The [EXAMPLE](https://github.com/marceloh220/BLACK_F407VE_ENCODER/blob/main/example/main.cpp) uses the [ILI9341](https://github.com/marceloh220/F407VE_Display_ILI9341_FSMC) library
 
 **The inputs of encoder are configurad in encoder mapping as __GPIO_NOPULL__, will be necessary external pull resistor or change the configuration to __GPIO_PULLUP__ or __GPIO_PULLDOWN__**
