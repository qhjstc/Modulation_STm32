//
// Created by QHJSTC on 2020/12/1.
//

#ifndef MODULATION_CACULATION_H
#define MODULATION_CACULATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "usart.h"
#include "tim.h"
#include "adc.h"
#include "dac.h"
#include "math.h"

void Modulation_Init(void);
void LED_Inverse();
double env_full(double in);
u32 filter(u32 x);
#ifdef __cplusplus
}
#endif


#endif //MODULATION_CACULATION_H



