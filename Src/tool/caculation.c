//本文件用于信号的调制以及解调
// Created by QHJSTC on 2020/12/1.
//

#include "tool/caculation.h"
#include "string.h"

//调制部分
#define SINSIZE 20         //正弦波大小
#define PI 2*asin(1)
float Sin_Value[SINSIZE] = {0};
volatile u32 ADC_data[1] = {0};
u32 DAC_data[SINSIZE] = {0};


//测试函数
void LED_Inverse(){
    HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
}

//幅度调制初始化
void Modulation_Init(void) {
    u8 str[50] = {};

    memset(Sin_Value,0,sizeof (Sin_Value)); //初始化先设置为0
    for(int i = 0; i < SINSIZE; i++)
    {
      Sin_Value[i] = sin(2 * i * PI / SINSIZE);
      DAC_data[i] = (u32)((Sin_Value[i]+1.5) * 1024);
      sprintf((char*)str,"The [%d] sin signal is:%d\r\n",i,DAC_data[i]);
      printf(str);
    }

    //发送正弦波,调制部分
    HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(u32*)&DAC_data,SINSIZE,DAC_ALIGN_12B_R);
    HAL_ADC_Start_DMA(&hadc1,(u32*)&ADC_data,1);

    HAL_TIM_Base_Start(&htim2);
    HAL_TIM_Base_Start(&htim8);

    //解调部分
//    HAL_DAC_Start(&hdac,DAC_CHANNEL_2);
//    HAL_ADC_Start_DMA(&hadc2,(u32*)&ADC_data2,1);


}


u32 temp = 0;    //临时存储变量
u32 Value = 0;  //解调的存储值

//ADC中断函数
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
  if(hadc == &hadc1)
  {
      temp = HAL_ADC_GetValue(&hadc1);
  }
}

//DAC数据传输完成中断
void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac){
    for(int i = 0; i < SINSIZE; i++)
    {
        DAC_data[i] = (u32)((Sin_Value[i] * temp) + 2048);
    }
}





