#include "adc.h"

/***********************
函数名：ADC1_Init
函数功能：模数转换初始化
形参：void
返回值：void
函数说明：
光敏电阻  ---PA5--ADC12_IN5
土壤湿度传感器--PA4---ADC12_IN4
************************/
void ADC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//使能ADC1
	
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_DeInit(ADC1);
	
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//连续转化模式设置
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//数据左对齐
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//软件触发
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;//独立模式
	ADC_InitStructure.ADC_NbrOfChannel=1;//通道数
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;//扫描模式禁止设置
	ADC_Init(ADC1,&ADC_InitStructure);
	
	//ADC_TempSensorVrefintCmd(ENABLE); //开启内部温度传感器
	
	ADC_Cmd(ADC1,ENABLE);//使能指定ADC外设
	
	ADC_ResetCalibration(ADC1);//使能复位校准
	while(ADC_GetResetCalibrationStatus(ADC1));//等待复位校准结束
	ADC_StartCalibration(ADC1);//开启AD校准
	ADC_GetCalibrationStatus(ADC1);//等待AD校准结束
}
/***********************
函数名：get_Adc_Value
函数功能：换取采样值
形参：u8 ch
返回值：u16
函数说明：
ch 转换通道   ADC_SampleTime_239Cycles5采样时间值    采样时间选择最长
1  采样通道数量
光敏电阻  ---PA5--ADC12_IN5
土壤湿度传感器--PA4---ADC12_IN4
************************/
u16 get_Adc_Value(u8 ch)//通道一采样值
{	
   ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_239Cycles5);//ADC匹配通道
	 ADC_SoftwareStartConvCmd(ADC1,ENABLE);//ADC软件转换启动
	 while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待采样结束
	 return ADC_GetConversionValue(ADC1);//放回采样值
}


/***********************
函数名：Get_light_Value
函数功能：光照强度
形参：void
返回值：void
函数说明：
光敏电阻  ---PA5--ADC12_IN5---0x05
土壤湿度传感器--PA4---ADC12_IN4--0x04
************************/
u8 light_value,soil_value;
u8 buf3[20];
u8 buf4[20];
u8 light_flag=0;
u8 soil_flag=0;
void Get_light_Value(void)
{
	light_value=0;
	u16 Rec=0;
	Rec=get_Adc_Value(0x05);//获取采样数值
	light_value = 100 - ((100 * Rec)/4096);//光照强度百分比

	sprintf((char *)buf3,"光照强度:%d%%LX",light_value);
	if(light_flag ==0)
	{
		Oled_ShowAll(4,0,buf3);//显示中英字符串
	}
	if(light_flag==1)
	{
		Oled_ShowAll(6,0,buf3);//显示中英字符串
	}
}
/***********************
函数名：Get_soil_Value
函数功能：土壤湿度
形参：void
返回值：void
函数说明：
光敏电阻  ---PA5--ADC12_IN5---0x05
土壤湿度传感器--PA4---ADC12_IN4--0x04
************************/
void Get_soil_Value(void)
{
	soil_value=0;
	u16 Rec=0;
	Rec=get_Adc_Value(0x04);//获取土壤采样数值
	soil_value = 100 - ((100 * Rec)/4096);//土壤强度百分比

	if(soil_flag==0)
	{
	sprintf((char *)buf4,"土壤湿度:%d%%",soil_value);
	Oled_ShowAll(4,0,buf4);//显示中英字符串
	}
	if(soil_flag == 1)
	{
		sprintf((char *)buf4,"soil:%d%%",soil_value);
		Oled_ShowAll(4,64,buf4);//显示中英字符串
	}
}

