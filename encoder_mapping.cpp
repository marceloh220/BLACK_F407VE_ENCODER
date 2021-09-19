/**  
* @file encoder_mapping.h  
* @brief Mapping for encoder timer in STM32F407VE, suddenly it will be moved to target BLACK_F407VE.
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

#include "PeripheralPins.h"
#include "mbed_toolchain.h"
#include "encoder.h"
#include "encoder_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The map for the treasure of Timer
 * Every Timer have they function and every function have they pins
 * This map is for STM32F407VE mcu.
 * I will do it, I swear. Or maybe you can do this! */
// TIM5 cannot be used because already used by the us_ticker
// (update us_ticker_data.h file if another timer is chosen)
// This map will be pair used
const PinMap PinMap_ENCODER[] = {
    {PA_8, ENCODER_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM1, 1, 0)}, // TIM1_CH1 0
    {PA_9, ENCODER_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM1, 2, 0)}, // TIM1_CH2 1
 
    {PA_0, ENCODER_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2, 1, 0)}, // TIM2_CH1 2
    {PA_1, ENCODER_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2, 2, 0)}, // TIM2_CH2 3

    {PA_6, ENCODER_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 1, 0)}, // TIM3_CH1 4
    {PA_7, ENCODER_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 2, 0)}, // TIM3_CH2 5

    {PB_4, ENCODER_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 1, 0)}, // TIM3_CH1 6
    {PB_5, ENCODER_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 2, 0)}, // TIM3_CH2 7

    {PC_6, ENCODER_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 1, 0)}, // TIM3_CH1 8
    {PC_7, ENCODER_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 2, 0)}, // TIM3_CH2 9

    {PB_6, ENCODER_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM4, 1, 0)}, // TIM4_CH1 10
    {PB_7, ENCODER_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM4, 2, 0)}, // TIM4_CH2 11

    {PD_12, ENCODER_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM4, 1, 0)}, // TIM4_CH1 12
    {PD_13, ENCODER_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM4, 2, 0)}, // TIM4_CH2 13

//  {PA_0, ENCODER_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM5, 1, 0)}, // TIM5_CH1 14
//  {PA_1, ENCODER_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM5, 2, 0)}, // TIM5_CH2 15

    {PC_6, ENCODER_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF3_TIM8, 1, 0)}, // TIM8_CH1 16
    {PC_7, ENCODER_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF3_TIM8, 2, 0)}, // TIM8_CH2 17
};

const ENCODERChannels_t encoderChannels[] = {
    {0,1}, /*TIMER1*/
    {2,3}, /*TIMER2*/
    {4,5}, {4,7}, {4,9}, {6, 5}, {6,7}, {6,9}, {8,5}, {8,7}, {8,9}, /*TIMER3 have a lot of possibilities*/
    {10,11}, {10,13}, {12,11}, {12,13}, /*TIMER4*/
//  {14,15}, /*TIMER5*/
    {16,17}, /*TIMER8*/
};

#ifdef __cplusplus
}
#endif
