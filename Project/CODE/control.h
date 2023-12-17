 /**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.3.13
  * @brief   元素识别头文件
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
#ifndef _CONTROL_H
#define _CONTROL_H

extern float aim_speed;         //期望速度
extern float price_Velocite;    //两轮差速输出
extern float speed_output;      //反二次型速度输出
extern float my_gyro_z;
extern float Position_Get,Position_pre_Get;
extern float target_vel_z;  //目标角度
extern uint8 stop_flag;



void motor_speed(float speed);
void set_speed_target(float a,float b);
void DifferControl();
void DerectError_Get(void);
void Direction_out(void);

#endif