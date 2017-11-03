#include "Car.h"
#include "stm32f10x_gpio.h"
#include "sys.h"
#include "delay.h"
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

void runA( float PWM, _Bool isForward, unsigned times ){
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
}

void runForward(float PWM){
	runA(PWM,1,1);
	runB(PWM,1,1);
}

void runBack(float PWM){
	runA(PWM,0,1);
	runB(PWM,0,1);
}

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