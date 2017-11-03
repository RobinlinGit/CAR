#include "stm32f10x_gpio.h"
#include "sys.h"
#include "delay.h"
/*
����Ϊ����l298N�Ӷ����Ƶ��ģ��
��ߵ������A���ұ߽�B���ҵ�������������߸�������ת
*/

//����L298N�߼�����˿�
#define ENA  PBout(6)
#define IN1  PBout(7)
#define IN2  PBout(8)
#define ENB  PAout(4)
#define IN3  PBout(10)
#define IN4  PBout(11)

#define radius 35.5  //��̥�뾶


void L298N_Init();

//void runA( float PWM, _Bool isForward, unsigned times );//����ת
//void runB( float PWM, _Bool isForward, unsigned times );//����ת
//���������ռ�ձ�ΪPWM,isForward��ʾǰ��or����,times��ʾ����(һ����ʱ20ms)

void stop(unsigned times);//ɲ��
void accelerate();//���ǰת
void neutral();//�յ�
void back();//����
void turn(_Bool isLeft);//ת��

