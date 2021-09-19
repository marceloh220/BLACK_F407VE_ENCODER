/**  
* @file encoder_types.h  
* @brief Some types for encoder, make the files more clean.
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

#ifndef _ENCODER_TYPES_H_
#define _ENCODER_TYPES_H_

#include <cstdint>
#include <stdint.h>

#include "mbed.h"

typedef struct {
    uint8_t channel1;
    uint8_t channel2;
} ENCODERChannels_t;

typedef enum {
    ENCODER_1  = (int)TIM1_BASE,
#if defined TIM2_BASE
    ENCODER_2  = (int)TIM2_BASE,
#endif
#if defined TIM3_BASE
    ENCODER_3  = (int)TIM3_BASE,
#endif
#if defined TIM4_BASE
    ENCODER_4  = (int)TIM4_BASE,
#endif
#if defined TIM5_BASE
    ENCODER_5  = (int)TIM5_BASE,
#endif
#if defined TIM8_BASE
    ENCODER_8  = (int)TIM8_BASE,
#endif
#if defined TIM9_BASE
    ENCODER_9  = (int)TIM9_BASE,
#endif
#if defined TIM10_BASE
    ENCODER_10 = (int)TIM10_BASE,
#endif
#if defined TIM11_BASE
    ENCODER_11 = (int)TIM11_BASE,
#endif
#if defined TIM12_BASE
    ENCODER_12 = (int)TIM12_BASE,
#endif
#if defined TIM13_BASE
    ENCODER_13 = (int)TIM13_BASE,
#endif
#if defined TIM14_BASE
    ENCODER_14 = (int)TIM14_BASE
#endif
#if defined TIM15_BASE
    ENCODER_15 = (int)TIM15_BASE
#endif
#if defined TIM16_BASE
    ENCODER_16 = (int)TIM16_BASE
#endif
#if defined TIM17_BASE
    ENCODER_17 = (int)TIM17_BASE
#endif
#if defined TIM18_BASE
    ENCODER_18 = (int)TIM18_BASE
#endif
#if defined TIM19_BASE
    ENCODER_19 = (int)TIM19_BASE
#endif
#if defined TIM20_BASE
    ENCODER_20 = (int)TIM20_BASE
#endif
#if defined TIM21_BASE
    ENCODER_21 = (int)TIM21_BASE
#endif
#if defined TIM22_BASE
    ENCODER_22 = (int)TIM22_BASE
#endif
} ENCODERHw_t;

#endif