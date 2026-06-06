#include "dht11.h"
/*******************************************************	

函数名：
函数功能：温湿度初始化
形参：void
返回值：void
DHT11_DATA --- PB14 --- 通用开漏输出 --- 需要关闭JTAG调试 
--- 等待1s以越过不稳定状态（1s延时） --- DATA线拉高


********************************************************/ 	
u8 DHT11_Temp,DHT11_Hum;
//复位DHT11
void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//SET OUTPUT
    DHT11_DQ_OUT=0; 	//拉低DQ
    delay_ms(20);    	//拉低至少18ms
    DHT11_DQ_OUT=1; 	//DQ=1 
	delay_us(30);     	//主机拉高20~40us
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 判断方向，也可以用等待高电平结束
    while (DHT11_DQ_IN&&retry<100)//DHT11会拉低40~80us，等待低电平结束
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;//等待超时
	else retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us，等待高电平结束
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//从DHT11读取一个位
//返回值：1/0
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//等待40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT11_Read_Data(float *temp,float *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			
			*temp=buf[2]*1.0f +	buf[3]/10.0f;//存储温度
			*humi=buf[0]*1.0f +	buf[1]/10.0f;//存储湿度
		}
	}else return 1;
	return 0;	    
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
u8 DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = DHT11_PIN;				 //PG11端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DHT11_IO, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_SetBits(DHT11_IO,DHT11_PIN);						 //PG11 输出高
			    
	DHT11_Rst();  //复位DHT11
	return DHT11_Check();//等待DHT11的回应
} 

/***********************
函数名：Dht11_GetValue
函数功能：DHT11温湿度显示
形参：void
返回值：void
函数说明：

温度：tempeature
湿度：humidity
************************/
float temp ,humi;
u8 buf1[20];
u8 buf2[20];
u8 DHT11=0;
//u8 DHT11=0;
void Dht11_GetValue(void)
{
	//printf("a\r\n");
	
	if(DHT11_Read_Data(&temp, &humi)==0)
	{
		
//		printf("温度：%.1f℃\r\n",temp);
//		printf("湿度：%.1f%%RH\r\n",hum);
		sprintf((char *)buf1,"温度:%.1f℃",temp);
		sprintf((char *)buf2,"湿度:%.1f%%RH",humi);	
		if(DHT11==0)
		{
		Oled_ShowAll(0,0,buf1);//显示中英字符串
		Oled_ShowAll(2,0,buf2);//显示中英字符串	
		}
	}


}

