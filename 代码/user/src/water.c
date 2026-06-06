#include "water.h"


/***********************
函数名：Water_Init
函数功能：水泵初始化
形参：void
返回值：void
函数说明：
水泵 --- PA11 --- 通用推挽输出

软件设计：

************************/

void Water_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPIOB时钟
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//定义结构体变量名
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//配置为通用推挽输出模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;//配置第11号管脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度为50Mhz
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	//水泵默认熄灭 --- 低电平
	Water_OFF;

}

