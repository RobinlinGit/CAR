#include "Car.h"
#include "stm32f10x_gpio.h"
#include "sys.h"
#include "delay.h"
extern uint16_t Usart2RecOrder;
extern uint16_t Late2Frame;

void Usart2_Init(){
	
  //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  
	
	Usart2RecOrder = 31;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_DeInit(USART2);
     //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART2_RX   PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
   //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART2
  
   //USART 初始化设置
   
	USART_InitStructure.USART_BaudRate = 115200;//;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
  
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
   
    USART_Cmd(USART2, ENABLE);                    //使能串口
}

void USART2_IRQHandler(){
	uint8_t temp;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){//接收中断{
		temp =USART_ReceiveData(USART2);//(USART1->DR); //读取接收到的数据
		Usart2RecOrder ++;
		Usart2RecOrder %= 32;		//确定得到的数据为第几个
		
		switch(Usart2RecOrder){
			case 0:{
				NewData.isKick = temp & 0x01;
				NewData.kickTurn = temp & (0x01<<1);
			}break;
			case 1:	NewData.gameState = (temp & 0xc0) >> 6;
				break;
			case 2: {
				uint16_t hiTurn =  Late2Frame & 0x3f ;
				uint16_t loTurn = temp;
				NewData.round =  (hiTurn<<6) & loTurn ;
			}	break;
			case 3:	
				NewData.self_x = temp;
				break;
			case 4:	
				break;
			case 5: 
				break;
			case 6:{
				NewData.self_y = Late2Frame;
				NewData.enemy_x = temp;
			}
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:{
				NewData.enemy_y = Late2Frame;
				NewData.ball_x = temp;
			}
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:{
				NewData.ball_y = Late2Frame;
			}
			case 13:
				break;
			case 14:
				NewData.selfResStopTime = Late2Frame;
				break;
			case 15:
				break;
			case 16:{
				NewData.enemyResStopTime = Late2Frame;
				NewData.selfEvil = temp;
			}
				break;
			case 17:
				NewData.enemyEvil = temp;
				break;
			case 18:
				NewData.selfScore = temp;
				break;
			case 19:
				NewData.enemyEvil = temp;
				break;
			
			case 20:NewData.fieldInfo[0] = temp;
				break;
			case 21:NewData.fieldInfo[1] = temp;
				break;
			case 22:NewData.fieldInfo[2] = temp;
				break;
			case 23:NewData.fieldInfo[3] = temp;
				break;
			case 24:NewData.fieldInfo[4] = temp;
				break;
			case 25:NewData.fieldInfo[5] = temp;
				break;
			case 26:NewData.fieldInfo[6] = temp;
				break;
			case 27:NewData.fieldInfo[7] = temp;
				break;
			case 28:NewData.fieldInfo[8] = temp;
				break;
			case 29:NewData.fieldInfo[9] = temp;
				break;
			
			case 30:
				break;
			case 31:
				break; //此处可能需要一些处理,等平台全部完成后再思考
			
		}
		Late2Frame = (Late2Frame<<8) | temp ;
		if( Late2Frame == 0x0D0A )
			Usart2RecOrder = 31;
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	} 
}


void L298N_Init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	//使能PA，PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	//初始化PB6(ENA),设为0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	//初始化PB7(IN1),设为0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	//初始化PB8(IN2),设为1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	//初始化PB11(IN4),设为0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	//初始化PA4(ENB),设为0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	//初始化PB10(IN3),设为1
	
}//初始化对L298N的逻辑输入


void stop(unsigned times){
	IN1=0;
	IN2=0;
}

void accelerate(){
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
	ENA=1;
	ENB=1;
}

void neutral(){
	ENA=0;
	ENB=0;
}

void back(){
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;
	ENA=1;
	ENB=1;
}

<<<<<<< HEAD
<<<<<<< HEAD
void turn(_Bool is_left, unsigned delay_time){
	if(is_left){
		IN3=0;
		IN4=1;
		ENA=0;
=======
=======
>>>>>>> parent of 8d82247... turn
void turn(_Bool isLeft){
	if(isLeft){
		IN1=1;
		IN2=0;
		IN3=0;
		IN4=1;
		ENA=1;
<<<<<<< HEAD
>>>>>>> parent of 8d82247... turn
=======
>>>>>>> parent of 8d82247... turn
		ENB=1;
	}
	else{
		IN1=0;
		IN2=1;
<<<<<<< HEAD
<<<<<<< HEAD
		ENA=1;
		ENB=0;
=======
=======
>>>>>>> parent of 8d82247... turn
		IN3=1;
		IN4=0;
		ENA=1;
		ENB=1;
<<<<<<< HEAD
>>>>>>> parent of 8d82247... turn
=======
>>>>>>> parent of 8d82247... turn
	}
	delay_ms(delay_time);
}
/*void runA( float PWM, _Bool isForward, unsigned times ){
	unsigned i = 0;
	if( PWM > 1 || PWM < 0 )return;
	ENA = 0;
	for( i = 0; i <= times-1; i++ ){
		IN1 = isForward;
		IN2 = ~IN1;
		ENA = 1;
		delay_ms((int)(PWM*100));
		ENA = 0;
		delay_ms((int)(PWM*100));
	}
}
void runB( float PWM, _Bool isForward, unsigned times ){
	unsigned i = 0;
	if( PWM > 1 || PWM < 0 )return;
	ENB = 0;
	for( i = 0; i <= times-1; i++ ){
		IN3 = isForward;
		IN4 = ~IN3;
		ENB = 1;
		delay_ms((int)(PWM*100));
		ENB = 0;
		delay_ms((int)(PWM*100));
	}
}*/