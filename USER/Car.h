#include "stm32f10x_gpio.h"
#include "sys.h"
#include "delay.h"
/*
以下为控制l298N从而控制电机模块
左边电机连接A，右边接B，且电机白线正极红线负极才正转
*/

//几个L298N逻辑输入端口
#define ENA  PBout(6)
#define IN1  PBout(7)
#define IN2  PBout(8)
#define ENB  PAout(4)
#define IN3  PBout(10)
#define IN4  PBout(11)

#define radius 35.5  //轮胎半径,待确定

extern uint16_t Late2Frame;//最近两帧的数据
extern uint16_t Usart2RecOrder;//接受顺序


/*接收数据包struct*/
struct DataPack{
	_Bool isKick;			//是否开始点球
	_Bool kickTurn;			//是否自己的点球回合
	uint8_t gameState;		//游戏状态		
	uint16_t round;
	uint8_t self_x;
	uint16_t self_y;
	uint8_t enemy_x;
	uint16_t enemy_y;	
	uint8_t ball_x;
	uint16_t ball_y;
	uint16_t selfResStopTime;
	uint16_t enemyResStopTime;	//剩余可强制停止次数
	uint8_t selfEvil;
	uint8_t enemyEvil;
	uint8_t selfScore;
	uint8_t enemyScore;		
	uint8_t fieldInfo[10];	//场地相关信息
	
	
};
extern struct DataPack NewData;
extern struct DataPack OldData;

//void runA( float PWM, _Bool isForward, unsigned times );//匀速转
//void runB( float PWM, _Bool isForward, unsigned times );//匀速转
//驱动电机，占空比为PWM,isForward表示前进or倒退,times表示次数(一次延时20ms)

void L298N_Init();

void stop(unsigned delay_time);//刹车
void accelerate(float v_rate,unsigned delay_time);//前进（速度比率（0-1），前进时间）
void neutral(unsigned delay_time);//空档
void back(float v_rate,unsigned delay_time);//倒车（速度比率（0-1），前进时间）
void turn(_Bool is_left, unsigned delay_time);//转弯

