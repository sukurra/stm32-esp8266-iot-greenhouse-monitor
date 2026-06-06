#ifndef _ADC_H
#define _ADC_H


#include "includes.h"

extern u8 light_value,soil_value;

extern u8 light_flag ,soil_flag;

void ADC1_Init(void);
u16 get_Adc_Value(u8 ch);//通道一采样值
void Get_light_Value(void);//获取光照强度
void Get_soil_Value(void);//获取土壤湿度




#endif

