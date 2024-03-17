#ifndef _MOTOR_H
#define _MOTOR_H

#include "encoder.h"
#include "headfile.h"

// 电机位置如图所示
//			 |
//	 1	 |   2
//----------------
//			 |
//	 3	 |   4

#define PWM_CH1_A PWM1_MODULE3_CHA_D0
#define PWM_CH1_B PWM1_MODULE3_CHB_D1

#define PWM_CH2_A PWM2_MODULE3_CHA_D2
#define PWM_CH2_B PWM2_MODULE3_CHB_D3

#define PWM_CH3_A PWM1_MODULE1_CHA_D14
#define PWM_CH3_B PWM1_MODULE1_CHB_D15

#define PWM_CH4_A PWM1_MODULE2_CHA_D16
#define PWM_CH4_B PWM1_MODULE2_CHB_D17


typedef struct Motor
{
	float Set_Speed;
	float Act_Speed;

}Motor_S;


extern Motor_S Motor_1;
extern Motor_S Motor_2;
extern Motor_S Motor_3;
extern Motor_S Motor_4;

void motor_pit_init();

void Motor_init();
void Motor_Pwm_cb();

void Motor1_Set_Pwm(int pwm);
void Motor2_Set_Pwm(int pwm);
void Motor3_Set_Pwm(int pwm);
void Motor4_Set_Pwm(int pwm);

#endif