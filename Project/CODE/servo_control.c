/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.3.13
  * @brief   ������PID����
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "headfile.h"
/* Private Define ------------------------------------------------------------*/
int16 Last_error,integral,delta;  //ƫ��   �ϴ�ƫ��   ����   ΢��
int16 Now_duty;  //λ��ʽpid���
int16 angle;    //���ռ�ձ����
int16 position;
float T=0.000055;
float Kp =1 ;
float Ki = 0;
float Kd = 4;

float Kp_turn = 3;
float Ki_turn = 0;
float Kd_turn = 0;

extern double K_diff = 0;  //������ٱ�

/* Private Functions ---------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
//�����ʼ��
/**
  * @brief  �����ʼ������
  * @param  None
  * @retval None
  */
void servo_init(void)
{

	pwm_init(PWMB_CH1_P74,50,705);       //Ƶ��Ϊ50hz��ռ�ձ�Ϊ7%

  gpio_mode(P7_7,GPO_PP);	//�������ӿڳ�ʼ��
	Buzz=0;   //���ͣ���ֹ������һֱ��
//  pwm_duty(PWMB_CH1_P74,700);   //�������ʱ��while���ã���ֵʱռ�ձ�Ϊ7.5%������������100��  ��ֵ��Ϊ700.�޷�(620--->785).....
}
/**
  * @brief  ���ѭ��PID����
  * @param  None
  * @retval None
  */
void servo_pid_street(float left, float right)
{
  float error;
  error = left-right;
//  error = position;
//	if(position>40)
//	{
//		Kp =T*position*position+0.2;
//		Kp=Kp>0.8?0.8:Kp;
//	}
//	else
//	{
//		Kp=0.5;
//	}
	integral += error;
	delta = error - Last_error;
	Now_duty = Kp*error + Ki*integral +Kd*delta;
	Last_error = error;
	 
	angle = 705 + Now_duty;
	
	angle = (angle > angle_max) ? angle_max:angle;    //���ת���޷�
	angle = (angle < angle_min) ? angle_min:angle;
	pwm_duty(PWMB_CH1_P74, angle) ;
	
    //K_diff = ((15.5/39)*tan(0.18*Now_duty*DEC))+0.05;   //������ٱ�
		//K_diff = (15.5/39)*tan(0.18*Now_duty*DEC)-0.02;   //������ٱ�
}
//void Steering_Control_Out(int16 duty)
//{
//     duty = Steer_Duty_Midle + duty ;//�ڶ����ֵ�Ļ����Ͻ���ƫ��
//   if (duty >= Steer_Duty_Max) duty = Steer_Duty_Max;
//   else if(duty <= Steer_Duty_Min) duty = Steer_Duty_Min;
//     pwm_duty(Steer_Pin, duty);
//}
/**
  * @brief  ���ת��PID����
  * @param  None
  * @retval None
  */
void servo_pid_turn(float left, float right)
{
  float error;
  error = left-right;
	integral += error;
	delta = error - Last_error;
	Now_duty = Kp_turn*error + Ki_turn*integral +Kd_turn*delta;
	Last_error = error;
	 
	angle = 705 + Now_duty;
	
	angle = (angle > angle_max) ? angle_max:angle;    //���ת���޷�
	angle = (angle < angle_min) ? angle_min:angle;
	pwm_duty(PWMB_CH1_P74, angle) ;
	
    //K_diff = ((15.5/39)*tan(0.18*Now_duty*DEC))+0.05;   //������ٱ�
		//K_diff = (15.5/39)*tan(0.18*Now_duty*DEC)-0.02;   //������ٱ�
}
/**
  * @brief  ��������жϺ���
  * @param  None
  * @retval None
  */
void Servo_IT()
{
  if(Left_Xie_Adc>140&&Right_Xie_Adc>140)
  servo_pid_street(Left_Xie_Adc,Right_Xie_Adc);
  else if(Left_Xie_Adc<140&&Right_Xie_Adc<140&&Left_Xie_Adc>10&&Right_Xie_Adc>10)
  servo_pid_turn(Left_Xie_Adc,Right_Xie_Adc);
}

/**
  * @brief  ��Ȧ����
  * @param  None
  * @retval None
  */
void  Protect_Anticollision()
{
  if(Left_Xie_Adc<10&&Right_Xie_Adc<10)
  {
    while(1)
		{
        motor_speed(0.0);
		}
    }
}  
