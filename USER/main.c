#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "usart.h"
#include "Car.h"
//ALIENTEK Mini STM32�����巶������9
//���벶��ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

extern uint16_t Late2Frame;//�����֡������
extern uint16_t Usart2RecOrder;//����˳��
extern struct DataPack NewData;
extern struct DataPack OldData;

 int main(void)
<<<<<<< HEAD
{	//u32 i = 0;
=======
 {	//u32 i = 0;
extern u8  TIM2CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ
	 
>>>>>>> master
	delay_init();	    	 //��ʱ������ʼ��
	
	ENA = 0;
	ENB = 0;
	LED_Init();
	L298N_Init();
	while(1){
		accelerate(0.2,1000);
		stop(100);
		turn(1,300);
		stop(1000);
		back(0.2,1000);
		stop(100);
		turn(0,300);
		stop(1000);
	}
}
 











		/*for( i = 0; i <= 9; i++ )runForward(0.5);
		for( i = 0; i <= 9; i++ )runBack(0.5);
		for( i = 0; i <= 9; i++ ){
			runA(0.75,1,1);
			runB(0.25,1,1);
		}
		for( i = 0; i <= 9; i++ ){
			runA(0.75,0,1);
			runB(0.25,0,1);
		}
	}
}
	u32 temp=0; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	
	uart_init(9600);	 			//9600	 
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
 	TIM1_PWM_Init(899,0); 			//����Ƶ��PWMƵ��=72000/(899+1)=80Khz
 	TIM2_Cap_Init(0XFFFF,72-1);		//��1Mhz��Ƶ�ʼ��� 
   	while(1)
	{
 		delay_ms(10);
		TIM_SetCompare1(TIM1,TIM_GetCapture1(TIM1)+1);
		if(TIM_GetCapture1(TIM1)==300)TIM_SetCompare1(TIM1,0);		 
		if(TIM2CH1_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
		{
			temp=TIM2CH1_CAPTURE_STA&0X3F;
			temp*=65536;					//���ʱ���ܺ�
			temp+=TIM2CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
			printf("HIGH:%d us\r\n",temp);	//��ӡ�ܵĸߵ�ƽʱ��
 			TIM2CH1_CAPTURE_STA=0;			//������һ�β���
 		}
	}
}
*/