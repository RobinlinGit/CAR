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


void L298N_Init(void);

//void runA( float PWM, _Bool isForward, unsigned times );//����ת
//void runB( float PWM, _Bool isForward, unsigned times );//����ת
//���������ռ�ձ�ΪPWM,isForward��ʾǰ��or����,times��ʾ����(һ����ʱ20ms)

void stop(unsigned delay_time);//ɲ��
void accelerate(float v_rate,unsigned delay_time);//ǰ�����ٶȱ��ʣ�0-1����ǰ��ʱ�䣩
void neutral(unsigned delay_time);//�յ�
void back(float v_rate,unsigned delay_time);//�������ٶȱ��ʣ�0-1����ǰ��ʱ�䣩
void turn(float left_rate, float right_rate, unsigned delay_time);//ת��

