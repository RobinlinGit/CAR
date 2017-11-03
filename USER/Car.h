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

#define radius 35.5  //轮胎半径


void L298N_Init(void);

//void runA( float PWM, _Bool isForward, unsigned times );//匀速转
//void runB( float PWM, _Bool isForward, unsigned times );//匀速转
//驱动电机，占空比为PWM,isForward表示前进or倒退,times表示次数(一次延时20ms)

void stop(unsigned delay_time);//刹车
void accelerate(float v_rate,unsigned delay_time);//前进（速度比率（0-1），前进时间）
void neutral(unsigned delay_time);//空档
void back(float v_rate,unsigned delay_time);//倒车（速度比率（0-1），前进时间）
void turn(float left_rate, float right_rate, unsigned delay_time);//转弯

