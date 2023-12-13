/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.3.13
  * @brief   �������ͷ�ļ�
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
#ifndef _SERVO_CONTROL_H
#define _SERVO_CONTROL_H

#define angle_max  790
#define angle_min  610

#define PI 3.15159265   
#define DEC (PI/180)

sbit Buzz = P7^7;
sbit Hall = P1^0;

void servo_init(void);
void servo_pid_street();
void servo_pid_turn();
void Servo_IT();
void  Protect_Anticollision();

extern int16 angle;    //���ռ�ձ����
extern int16 Now_duty;
extern double K_diff ;  //������ٱ�



#endif