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

#define radius 35.5  //��̥�뾶,��ȷ��

extern uint16_t Late2Frame;//�����֡������
extern uint16_t Usart2RecOrder;//����˳��


/*�������ݰ�struct*/
struct DataPack{
	_Bool isKick;			//�Ƿ�ʼ����
	_Bool kickTurn;			//�Ƿ��Լ��ĵ���غ�
	uint8_t gameState;		//��Ϸ״̬		
	uint16_t round;
	uint8_t self_x;
	uint16_t self_y;
	uint8_t enemy_x;
	uint16_t enemy_y;	
	uint8_t ball_x;
	uint16_t ball_y;
	uint16_t selfResStopTime;
	uint16_t enemyResStopTime;	//ʣ���ǿ��ֹͣ����
	uint8_t selfEvil;
	uint8_t enemyEvil;
	uint8_t selfScore;
	uint8_t enemyScore;		
	uint8_t fieldInfo[10];	//���������Ϣ
	
	
};
extern struct DataPack NewData;
extern struct DataPack OldData;

//void runA( float PWM, _Bool isForward, unsigned times );//����ת
//void runB( float PWM, _Bool isForward, unsigned times );//����ת
//���������ռ�ձ�ΪPWM,isForward��ʾǰ��or����,times��ʾ����(һ����ʱ20ms)

void L298N_Init();

void stop(unsigned delay_time);//ɲ��
void accelerate(float v_rate,unsigned delay_time);//ǰ�����ٶȱ��ʣ�0-1����ǰ��ʱ�䣩
void neutral(unsigned delay_time);//�յ�
void back(float v_rate,unsigned delay_time);//�������ٶȱ��ʣ�0-1����ǰ��ʱ�䣩
void turn(_Bool is_left, unsigned delay_time);//ת��

