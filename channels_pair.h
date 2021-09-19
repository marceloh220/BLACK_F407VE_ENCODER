/**  
* @file channels_pair.h  
* @brief Encoder's channels pair to STM32F407VE.
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

/*Channels pair for BLACK_F407xx target*/
typedef enum {
    ENCODER_PA8_PA9,     /*TIMER1*/

    ENCODER_PA0_PA1,     /*TIMER2*/
    
    ENCODER_PA6_PA7,     /*TIMER3*/
    ENCODER_PA6_PB5,     /*TIMER3*/
    ENCODER_PA6_PC7,     /*TIMER3*/
    ENCODER_PB4_PA7,     /*TIMER3*/
    ENCODER_PB4_PB5,     /*TIMER3*/
    ENCODER_PB4_PC7,     /*TIMER3*/
    ENCODER_PC6_PA7,     /*TIMER3*/
    ENCODER_PC6_PB5,     /*TIMER3*/
    ENCODER_PC6_PC7,     /*TIMER3*/
    
    ENCODER_PB6_PB7,     /*TIMER4*/
    ENCODER_PB6_PD13,    /*TIMER4*/
    ENCODER_PD12_PB7,    /*TIMER4*/
    ENCODER_PD12_PD13,   /*TIMER4*/

//  ENCODER_PA0_PA1_ALT, /*TIMER5, in mbed this timer is used to us ticker*/

    ENCODER_PC6_PC7_ALT, /*TIMER8*/

} ENCODERName_t;

#ifndef _CHALLELS_PAIR_H_
#define _CHALLELS_PAIR_H_


#endif
