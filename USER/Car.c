#include "Car.h"
#include "stm32f10x_gpio.h"
#include "sys.h"
#include "delay.h"
void L298N_Init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	//ʹ��PA��PD�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	//��ʼ��PB6(ENA),��Ϊ0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	//��ʼ��PB7(IN1),��Ϊ0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	//��ʼ��PB8(IN2),��Ϊ1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	//��ʼ��PB11(IN4),��Ϊ0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	//��ʼ��PA4(ENB),��Ϊ0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	//��ʼ��PB10(IN3),��Ϊ1
	
}//��ʼ����L298N���߼�����


void stop(unsigned delay_time){
	IN1=0;
	IN2=0;
	IN3=0;
	IN4=0;
	delay_ms(delay_time);
}

void accelerate(float v_rate,unsigned delay_time){
	int k=delay_time/10;
	int i=0;
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
	for(i=0;i<k;i++){
		ENA=1;
		ENB=1;
		delay_ms(10.0 * v_rate);
		ENA=0;
		ENB=0;
		delay_ms(10.0 * (1.0 - v_rate));
	}
}

void neutral(unsigned delay_time){
	ENA=0;
	ENB=0;
	delay_ms(delay_time);
}

void back(float v_rate,unsigned delay_time){
	int k=delay_time/10;
	int i=0;
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;
	for(i=0;i<k;i++){
		ENA=1;
		ENB=1;
		delay_ms(10.0 * v_rate);
		ENA=0;
		ENB=0;
		delay_ms(10.0 * (1.0 - v_rate));
	}
}

void turn(float left_rate, float right_rate, unsigned delay_time){
	int k=delay_time/10;
	int i=0;
	if(left_rate>0){
		IN1=0;
		IN2=1;
	}
	else{
		IN1=1;
		IN2=0;
	}
	if(right_rate>0){
		IN3=0;
		IN4=1;
	}
	else{
		IN3=1;
		IN4=0;
	}
	for(i=0;i<k;i++){
		ENA=1;
		delay_ms(10.0 * left_rate);
		ENB=1;
		delay_ms(10.0 * right_rate);
		ENA=0;
		delay_ms(10.0 * (1.0 - left_rate));
		ENB=0;
		delay_ms(10.0 * (1.0 - right_rate));
	}
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