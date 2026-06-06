#include "gizwits_protocol.h"
#include "gizwits_product.h"
#include "show.h"

extern const unsigned char pic1[];//温室大棚64
extern const unsigned char pic2[];//温室大棚64(苗)
extern const unsigned char pic3[];//温室大棚32(苗)
extern const unsigned char pic4[];//天气页面64
extern const unsigned char pic5[];//天气温度计64
extern const unsigned char pic6[];//天气烈日32
extern const unsigned char pic7[];//天气多云32
extern const unsigned char pic8[];//天气下雨32
extern const unsigned char pic9[];//天气页面32
extern const unsigned char pic10[];//土壤湿度64
extern const unsigned char pic11[];//土壤湿度32
extern const unsigned char pic12[];//土壤干旱32
extern const unsigned char pic13[];//土壤水资源达标32
extern const unsigned char pic14[];//光照强度32
extern const unsigned char pic15[];//光照强度62
extern const unsigned char pic16[];//光强足够32
extern const unsigned char pic17[];//光强不足32
extern const unsigned char Close_LED[];//关闭补光
extern const unsigned char Open_LED[];//开始LED补光
extern const unsigned char pic18[];//二氧化碳64
extern const unsigned char pic19[];//二氧化碳32
extern const unsigned char pic20[];//二氧化碳超标32
extern const unsigned char pic21[];//二氧化碳未超标32
extern const unsigned char pic22[];//风扇32
extern const unsigned char fan1[];//风扇转动32
extern const unsigned char fan2[];//风扇转动32
extern const unsigned char pic23[];//设置图标32
extern const unsigned char pic24[];//设置图标64
extern const unsigned char pic25[];//水泵关64
extern const unsigned char pic26[];//水泵开64
extern const unsigned char pic27[];//wifi开32
extern const unsigned char pic28[];//wifi开64
extern const unsigned char pic29[];//wifi开64


//机智云 接收数据包
void Wifi_date(void)
{
	gizwitsHandle(&currentDataPoint);//上报函数
	userHandle();	//数据发布
}

//主页面展示
void Show_Greenhouse(void)
{
	
	Oled_ShowPic(0,48,32,32,(u8*)pic3);//显示温室大棚图片
	Oled_ShowAll(4,44,(u8*)"Smart");//显示汉英字符串
	Oled_ShowAll(6,19,(u8*)"Greenhouse");//显示汉英字符串

}

//各大功能展示
void Admin_show(void)
{
	Oled_ShowPic(0,8,32,32,(u8*)pic9);//显示天气小图标
	Oled_ShowPic(0,48,32,32,(u8*)pic11);//土壤湿度小图标
	Oled_ShowPic(0,88,32,32,(u8*)pic14);//光照强度小图标
	Oled_ShowPic(4,8,32,32,(u8*)pic19);//二氧化碳浓度小图标
	Oled_ShowPic(4,48,32,32,(u8*)pic23);//设置小图标
	Oled_ShowPic(4,88,32,32,(u8 *)pic27);//wifi
}

//天气温湿度展示页面
void Weather_Show(void)
{
	u8 key;
	u8 flag=0;
	OLED_Clear(0x00);//清屏
	Oled_ShowPic(0,32,64,64,(u8 *)pic5);//温度计
	
	while(1)
	{
		
		Wifi_date();//机智云接收数据包
		key =key_scan();
		if(key==1)
		{
			OLED_Clear(0x00);//清屏
			while(1)
			{
				Wifi_date();//机智云接收数据包
				key =key_scan();
				if(Hot==1)
				{
					Oled_ShowAll(2,8,"the heater is ");//显示中英字符串
					Oled_ShowAll(4,46,"open ");//显示中英字符串
				}
				else if(Hot==0)
				{
					Oled_ShowAll(2,8,"the heater is ");//显示中英字符串
					Oled_ShowAll(4,46,"close");//显示中英字符串
				}
				if(key==1)
				{
					Hot_OFF;
				}
				if(key==2)
				{
					Hot_ON;
				}
				if(key==3)
				{
					flag=1;
					key=0;
					OLED_Clear(0x00);//清屏
					break;
				}
			
			}
		
		
		}
		if(key ==2)
		{
			//DHT11=1;
			flag=1;
		OLED_Clear(0x00);//清屏
		//Dht11_GetValue();//展示温度
		}
		if(flag==1)
		{
			delay_ms(50);
			Dht11_GetValue();//展示温度
		if(temp>=30)
		{
			Oled_ShowPic(4,32,32,32,(u8 *)pic6);//烈日
		  Oled_ShowAll(6,96,"烈日");//显示中英字符串

		}
		else if((temp>=20&&temp<30) && humi>=30 )
		{
			Oled_ShowPic(4,32,32,32,(u8 *)pic7);//多云
		  Oled_ShowAll(6,96,"多云");//显示中英字符串

		}
		else if(temp<=25&& humi>=60 )
		{
			Oled_ShowPic(4,32,32,32,(u8 *)pic8);//下雨
			Oled_ShowAll(6,96,"下雨");//显示中英字符串

		}
		
	
		
		
		
	}
		if(key == 3)
		{
			//DHT11=0;
			flag=0;
			OLED_Clear(0x00);//清屏
			break;
		}
	}
}

//土壤湿度展示
void Soil_Show(void)
{
	u8 key;
	OLED_Clear(0x00);//清屏	
	while(1)
	{
		Wifi_date();//机智云接收数据包
		key=key_scan();
		//Wifi_date();//机智云接收数据包
		delay_ms(100);
		Get_soil_Value();
		if(soil_value<=30)
		{
			Oled_ShowPic(0,48,32,32,(u8 *)pic12);//干旱	
		}
		else
		{
			Oled_ShowPic(0,48,32,32,(u8 *)pic13);//充足
		}
		Oled_ShowAll(6,0,"KEY2进入灌溉模式");//显示中英字符串
		if(key == 2)
		{
			OLED_Clear(0x00);//清屏	
			while(1)
			{
				Wifi_date();//机智云接收数据包
				key =key_scan();
					if(Water)
				{
					Oled_ShowPic(0,24,64,64,(u8 *)pic26);//水泵已打开
					Oled_ShowAll(4,88,"ON ");//显示中英字符串
				}
				else
				{
					Oled_ShowPic(0,24,64,64,(u8 *)pic25);//水泵未打开
					Oled_ShowAll(4,88,"OFF");//显示中英字符串
				}
				if(key ==1)
				{
					Water_OFF;
				}
				if(key ==2)
				{
					Water_ON;
				}
				if(key == 3)
				{
					key=0;
					OLED_Clear(0x00);//清屏	
					break;
				}
			}
		}
		if(key == 3)
		{
			//DHT11=0;
			OLED_Clear(0x00);//清屏
			break;
		}
	}


}
//光照强度显示
void Light_Show(void)
{
	static u8 flag=1;
	u8 key;
	u16 num=0;
	OLED_Clear(0x00);//清屏	
	u8 number=0;
	char buff[5]={0};
	while(1)
	{
			Wifi_date();//机智云接收数据包
			key=key_scan();
		//Wifi_date();//机智云接收数据包
		//delay_ms(200);
		Get_light_Value();
		num=light_value;
		if(num>=50)
		{
			Oled_ShowPic(0,48,32,32,(u8 *)pic16);//光强充足	
		}
		else
		{
			Oled_ShowPic(0,48,32,32,(u8 *)pic17);//光强不足
			
		}
		Oled_ShowAll(6,0,"KEY2进入补光模式");//显示中英字符串
		if(key==2)
		{
			OLED_Clear(0x00);//清屏	
			while(1)
			{
				Wifi_date();//机智云接收数据包
				key=key_scan();
				if(flag==0)
				{
					sprintf((char *)buff,"%d",number);
					Oled_ShowPic(0,48,32,32,(u8 *)Open_LED);//LED补光
					Oled_ShowAll(4,36,"LED ON ");//显示中英字符串
					Oled_ShowAll(6,52,(u8*)buff);//显示中英字符串
					Oled_ShowAll(6,61,"档");//显示中英字符串
				}
			else
			{
				Oled_ShowPic(0,48,32,32,(u8 *)Close_LED);//LED补光关闭
				Oled_ShowAll(4,36,"LED OFF");//显示中英字符串
				Oled_ShowAll(6,36,"       ");//显示中英字符串

				
				
			}
			if(key==1)
			{
				flag=1;
				TIM_SetCompare3(TIM3,1000);
			
				
			}
			if(key==2)
			{
				flag=0;
					if(number>3)
				{
					number=0;
				} 
				TIM_SetCompare3(TIM3,number*300);
				number++;
			 
			}
			if(key == 3)
			{
				OLED_Clear(0x00);//清屏	
				break;
			}
			
			
			}				
		}
		if(key == 3)
		{
			//DHT11=0;
			OLED_Clear(0x00);//清屏
			break;
		}
	}

}

//CO2浓度展示页面
void C02_Show(void)
{
	u8 key;
	u16 num=0;
	OLED_Clear(0x00);//清屏	
	static	u8 CO2=0;//放置二氧化碳浓度
	Act24_ContinueRead(&CO2,6,sizeof(CO2),6);
	while(1)
	{
		Wifi_date();//机智云接收数据包
		key=key_scan();
		Oled_ShowAll(6,0,"KEY2进入通风模式");//显示中英字符串
		//Wifi_date();//机智云接收数据包
		//delay_ms(200);
		CO2_Get();//OLED展示二氧化碳浓度
		num=CO2_PPM;//获取二氧化碳值

		if(num>=CO2)
		{
			Oled_ShowPic(0,8,32,32,(u8 *)pic19);//CO2图标
			Oled_ShowPic(0,48,32,32,(u8 *)pic20);//CO2超标图标

		}
		else
		{
			Oled_ShowPic(0,8,32,32,(u8 *)pic19);//CO2图标
			Oled_ShowPic(0,48,32,32,(u8 *)pic21);//CO2未超标图标

		}
		if(key==2)
		{
			OLED_Clear(0x00);//清屏	
			while(1)
			{
				Wifi_date();//机智云接收数据包
				key=key_scan();
				if(Fan)
				{
					//风扇转动
					Oled_ShowAll(4,36,"Fan ON ");//显示中英字符串
					Oled_ShowPic(0,48,32,32,(u8 *)fan1);//风扇开
					delay_ms(10);
					Oled_ShowPic(0,48,32,32,(u8 *)fan2);//风扇开
				}
			else
			{
				Oled_ShowPic(0,48,32,32,(u8 *)fan1);//LED补光关闭
				Oled_ShowAll(4,36,"Fan OFF");//显示中英字符串
			}
			if(key==1)
			{
				Fan_OFF;
			}
			if(key==2)
			{
				Hot_OFF;
				Fan_ON;
			}
			if(key == 3)
			{
				key=0;//清零，要不会直接跳回到上两个页面
				OLED_Clear(0x00);//清屏	
				break;
			}
			
			
			}				
		}
		if(key == 3)
		{
			//DHT11=0;
			OLED_Clear(0x00);//清屏
			break;
		}
	}

}
 
//阀值设置
void Set_Show(void)
{
	u8 rec0[20];
	u8 rec1[20];
	u8 rec2[20];
	u8 rec3[20];
	u8 rec4[20]; 
	static	u8 Temp=0;//放置温度
	static	u8 Hum=0;//放置湿度
	static	u8 Light=0;//放置光照强度
	static	u8 CO2=0;//放置二氧化碳浓度
	static	u8 Soil=0;//放置土壤湿度
	Act24_ContinueRead(&Temp,0,sizeof(Temp),6);//读取查重温度阈值
	Act24_ContinueRead(&Hum,2,sizeof(Hum),6);
	Act24_ContinueRead(&Light,4,sizeof(Light),6);
	Act24_ContinueRead(&CO2,6,sizeof(CO2),6);
	Act24_ContinueRead(&Soil,8,sizeof(Soil),6);
	OLED_Clear(0x00);//清屏
	u8 a=0;
	u8 key;
//	sprintf((char *)rec0,"%d℃",Temp);
//	sprintf((char *)rec1,"%dRH",Hum);	
//	sprintf((char *)rec4,"%dLX",Light);
//	sprintf((char *)rec3,"%dPPM",CO2);	
//	sprintf((char *)rec2,"%d",Soil);
//	Oled_ShowAll(0,32,"Temp:");//显示中英字符串
//	Oled_ShowAll(2,32,"Humi:");//显示中英字符串
//	Oled_ShowAll(4,32,"Soil:");//显示中英字符串
//	Oled_ShowAll(6,32,"CO2 :");//显示中英字符串
	while(1)
	{
		Wifi_date();//机智云接收数据包
		sprintf((char *)rec0,"%d℃",Temp);
		sprintf((char *)rec1,"%dRH",Hum);	
		sprintf((char *)rec3,"%dPPM",CO2);	
		sprintf((char *)rec2,"%d",Soil);
		Oled_ShowAll(0,32,"Temp:");//显示中英字符串
		Oled_ShowAll(2,32,"Humi:");//显示中英字符串
		Oled_ShowAll(4,32,"Soil:");//显示中英字符串
		Oled_ShowAll(6,32,"CO2 :");//显示中英字符串
		Oled_ShowAll(0,80,rec0);//显示中英字符串
		Oled_ShowAll(2,80,rec1);//显示中英字符串
		Oled_ShowAll(4,80,rec2);//显示中英字符串
		Oled_ShowAll(6,80,rec3);//显示中英字符串
	key =key_scan();
		if(key==1)
		{
			key=0;//清零
			if(a>0)
			{
				//清除上一个箭头记忆
				Oled_clear(a-2,16,16,16);
			}
				if(a>=8)
			{
				OLED_Clear(0x00);//清屏
				while(1)
				{
					Wifi_date();//机智云接收数据包
					key = key_scan();
					a=0;
					sprintf((char *)rec4,"%dLX",Light);
					Oled_ShowAll(a,16,"->");//显示中英字符串
					Oled_ShowAll(0,32,"Light:");//显示中英字符串
					Oled_ShowAll(0,88,rec4);//显示中英字符串
					if(key==1)
					{
						key=0;
						OLED_Clear(0x00);//清屏
//						Oled_ShowAll(0,32,"Temp:");//显示中英字符串
//						Oled_ShowAll(2,32,"Humi:");//显示中英字符串
//						Oled_ShowAll(4,32,"Soil:");//显示中英字符串
//						Oled_ShowAll(6,32,"CO2 :");//显示中英字符串
						break;
					}
					if(key ==2)
					{
						Light +=2;
					}
					if(key == 3)
					{
						Light -=2;
					}
					if(key ==4)
					{
						key=0;
						OLED_Clear(0x00);//清屏
						break;
					}
				Act24_AutoWrite(&Light,4,sizeof(Light),6);
					
				}
			}
			Oled_ShowAll(a,16,"->");//显示中英字符串
			a +=2;
		}
		
		//Temp 控制
		if(key == 2 && (a-2)==0)
		{
			
				Temp+=2;
//				Act24_AutoWrite(&Temp,1,1,6);

		}
		else if(key==3 && (a-2)==0)
		{
			 Temp-=2;
		}
	//Hum 控制
		if(key == 2 && (a-2)==2)
		{
			
				Hum+=2;
		}
		else if(key==3 && (a-2)==2)
		{
			 Hum-=2;
		}
		//Soil 控制
		if(key == 2 && (a-2)==4)
		{
			
				Soil+=2;
		}
		else if(key==3 && (a-2)==4)
		{
			 Soil-=2;
		}	
		//CO2 控制
		if(key == 2 && (a-2)==6)
		{
			
				CO2+=2;
		}
		else if(key==3 && (a-2)==6)
		{
			 CO2-=2;
		}	
		if(key ==4)
		{
			OLED_Clear(0x00);//清屏
			break;
		}
	Act24_AutoWrite(&Temp,0,sizeof(Temp),6);
	Act24_AutoWrite(&Hum,2,sizeof(Hum),6);
	Act24_AutoWrite(&CO2,6,sizeof(CO2),6);
	Act24_AutoWrite(&Soil,8,sizeof(Soil),6);
		
	}

}
//wifi控制页面
extern u8 flag_WIFI;
void Wifi_Show(void)
{
	u8 key;
	u16 num=0;
	static u8 dis=0;//wifi是否按下配网键
	OLED_Clear(0x00);//清屏
		while(1)
		{
//			Oled_ShowAll(4,0,"wait");//显示中英字符串
			if(flag_WIFI==1)
			{
				if(dis==1)
				{
					dis=0;
					OLED_Clear(0x00);//清屏
				}
				Oled_ShowPic(0,0,64,64,(u8 *)pic28);//wifi图片
				Oled_ShowAll(2,66,"WIFI");//显示中英字符串
				Oled_ShowAll(4,66,"ON ");//显示中英字符串
			}
			if(flag_WIFI==0)
			{
				if(dis==1)
				{
					dis=0;
					OLED_Clear(0x00);//清屏
				}
				Oled_ShowPic(0,0,64,64,(u8 *)pic29);//wifi图片
				Oled_ShowAll(2,66,"WIFI");//显示中英字符串
				Oled_ShowAll(4,66,"OFF");//显示中英字符串
			}
			key =key_scan();
			if(key == 1)//设置配网模式
		{
			dis=1;
			OLED_Clear(0x00);//清屏
			gizwitsSetMode(WIFI_AIRLINK_MODE);//手机广播配网
			Oled_ShowAll(0,48,"WAIT");//显示中英字符串
			Oled_ShowAll(4,0,"Wifi connecting");//显示中英字符串
			printf("WIFI_AIRLINK_MODE OK\r\n");
			while(!flag_WIFI)
			{
				delay_ms(1);
				num++;
				if(num>=50000)
				{
					break;
					
				}
				Wifi_date();//机智云接收数据包
			}
//			delay_ms(3000);
		}
				if(key == 2)//恢复出厂设置
		{
			gizwitsSetMode(WIFI_RESET_MODE);//恢复出厂设置
			printf("WIFI_RESET_MODE OK\r\n");
		}
		if(key==3)
		{
			
			OLED_Clear(0x00);//清屏
			break;
		}
		

//		KEY_Control_ML();
//	gizwitsHandle(&currentDataPoint);//上报函数
//	userHandle();	//数据发布
		Wifi_date();//机智云接收数据包
		
		
		}

	}
	

//选择界面
void Select_Show(void)
{
	u8 key,num=0;
	OLED_Clear(0x00);//清屏
		while(1)
		{
			
			Wifi_date();//机智云接收数据包
		if(num<7)
		{
			Admin_show();//各大功能页面
		}
		if(num>=7)
		{
			num=1;
		}
			key=key_scan();
			if(key==1)
			{
				num++;
				
			}
			if(key==3)
			{
				OLED_Clear(0x00);//清屏
				Smart_Greenhouse();//回到主页面
			}
		
			///空气温湿度单独页面
			if(num==1)
			{
				OLED_Clear(0x00);//清屏
				while(1)
				{
					Wifi_date();//机智云接收数据包
				Oled_ShowPic(0,32,64,64,(u8 *)pic4);//天气
					key=key_scan();
				if(key==1)
				{
					num++;
					break;
				}
				if(key==2)
				{
				 Weather_Show();//天气温湿度
				}
				if(key==3)
				{
					num=0;
					OLED_Clear(0x00);//清屏
					break;
				}
				}
			}
///土壤湿度单独页面
			if(num==2)
			{
				OLED_Clear(0x00);//清屏
				while(1)
				{
					Wifi_date();//机智云接收数据包
				Oled_ShowPic(0,32,64,64,(u8 *)pic10);//土壤湿度
					key=key_scan();
				if(key==1)
				{
					num++;
					break;
				}
				if(key==2)
				{
				 Soil_Show();//土壤湿度展示
				}
				if(key==3)
				{
					num=0;
					OLED_Clear(0x00);//清屏
					break;
				}
				}
			}
			///光照强度单独页面
			if(num==3)
			{
				OLED_Clear(0x00);//清屏
				while(1)
				{
					Wifi_date();//机智云接收数据包
				Oled_ShowPic(0,32,64,64,(u8 *)pic15);//光照强度
					key=key_scan();
				if(key==1)
				{
					num++;
					break;
				}
				if(key==2)
				{
				 Light_Show();//光照强度展示
				}
				if(key==3)
				{
					num=0;
					OLED_Clear(0x00);//清屏
					break;
				}
				}
			}
					///二氧化碳浓度单独页面
			if(num==4)
			{
				OLED_Clear(0x00);//清屏
				while(1)
				{
					Wifi_date();//机智云接收数据包
				Oled_ShowPic(0,32,64,64,(u8 *)pic18);//光照强度
					key=key_scan();
				if(key==1)
				{
					num++;
					break;
				}
				if(key==2)
				{
				 C02_Show();//光照强度展示
				}
				if(key==3)
				{
					num=0;
					OLED_Clear(0x00);//清屏
					break;
				}
				}
			}
					///阈值设置单独页面
			if(num==5)
			{
				OLED_Clear(0x00);//清屏
				while(1)
				{
					Wifi_date();//机智云接收数据包
				Oled_ShowPic(0,32,64,64,(u8 *)pic24);//设置图标
					key=key_scan();
				if(key==1)
				{
					num++;
					break;
				}
				if(key==2)
				{
				 Set_Show();//设置展示
				}
				if(key==3)
				{
					num=0;
					OLED_Clear(0x00);//清屏
					break;
				}
				}
			}
			//wifi单独页面
				if(num==6)
			{
				OLED_Clear(0x00);//清屏
				while(1)
				{
				Wifi_date();//机智云接收数据包
				Oled_ShowPic(0,32,64,64,(u8 *)pic28);//wifi
				key=key_scan();
				if(key==1)
				{
					num++;
					break;
				}
				if(key ==2)//进入窗帘页面
				{
					Wifi_Show();
				
				}
				if(key==3)
				{
					num=0;
					OLED_Clear(0x00);//清屏
					break;
				}
				}

			}

}

}


//展示温湿度、土壤湿度、二氧化碳浓度
void All_Show(void)
{
	OLED_Clear(0x00);//清屏
	light_flag=1;
	soil_flag=1;
	while(1)
	{
	
			CO2_Get();//二氧化碳浓度
			Dht11_GetValue();//温湿度
			Get_light_Value();//光照强度
			Get_soil_Value();//土壤湿度
		
			Voice_Loud();//报警模块
		if(key_scan()==3)
		{
			light_flag=0;
			soil_flag=0;
			Buz_OFF;
			OLED_Clear(0x00);//清屏
			Show_Greenhouse();//首页面展示
			break;
		}

	}

}


void Smart_Greenhouse(void)
{
	Show_Greenhouse();//首页面展示
	u8 key;
	while(1)
	{
		key =key_scan();
		Wifi_date();//机智云接收数据包
		if(key ==1)
		{
			All_Show();//所有数据展示
		
		}
		if(key==2)
		{
			Select_Show();
		}
	
	
	
	}


}
