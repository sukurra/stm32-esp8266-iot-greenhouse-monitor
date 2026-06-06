#include "led.h"


/***********************
函数名：Led_Init
函数功能：LED初始化,光照补光
形参：void
返回值：void
函数说明：
LED --- PB1 --- 通用推挽输出

软件设计：
1、	打开时钟（GPIOB）
2、	初始化PB0
3、	LED默认灭状态 --- 高电平
4、	点灯
5、延时函数
************************/

void Led_Init(void)
{
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIOB时钟
//	
//	GPIO_InitTypeDef GPIO_InitStruct={0};//定义结构体变量名
//	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//配置为通用推挽输出模式
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;//配置第0号管脚
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度为50Mhz
//	GPIO_Init(GPIOB,&GPIO_InitStruct);
//	

	//LED默认熄灭 --- 高电平
//	LED_OFF;
	TIM3_Init();//定时器3初始化
}
void TIM3_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//打开AFIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//打开TIM3时钟
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//完全关闭JTAG-DP  开启SW-DP
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//TIM3部分重映像
	
	GPIO_InitTypeDef GPIO_InitStruct={0};//定义结构体变量名
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//配置为复用推挽输出模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;//配置管脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//速度为50Mhz
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//配置TIM3时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct={0};
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;//预分频数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	//配置输出比较
	TIM_OCInitTypeDef TIM_OCInitStruct={0};
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//配置PWM1模式
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//高电平有效
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//输出比较使能
	TIM_OCInitStruct.TIM_Pulse = 0;//比较值初始值
	TIM_OC3Init(TIM3,&TIM_OCInitStruct);
	
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能通道1影子寄存器
	TIM_SetCompare3(TIM3,1000);   
	TIM_Cmd(TIM3,ENABLE);//使能TIM3

}


