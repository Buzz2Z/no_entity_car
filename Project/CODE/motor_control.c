/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.3.13
  * @brief    �������
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
 /* Includes ------------------------------------------------------------------*/
#include "headfile.h"

/* Private Define ------------------------------------------------------------*/
int16 Left_Encoder = 0;     //���������ֵ
int16 Right_Encoder = 0;    //�ұ�������ֵ
int16 Average_Encoder = 0;  //���ұ�����ƽ��ֵ
int16 Sum_Encoder = 0;      //�����������
int32 distance = 0;         //�������ߵ�·��

//int16 K_diff = 0 ;          //����ϵ��



float K_P_L = 3500;//800
float K_I_L = 20;//80
float K_D_L = 0;
float K_P_R = 3000;//800
float K_I_R = 20;//80
float K_D_R = 0;
int16 Right_Duty,Left_Duty;
float right_wheel_goal;
float left_wheel_goal;


#define WHEEL_R 32.5       //��λmm
#define WHEEL_POSITION 2*WHELL_R      //
#define ENCODER_POSITON 
#define ENCODER_SPEED

/* Private Functions ---------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/
/**
  * @brief  �����ٶ�pid
  * @param  goal
  * @retval None
  */
void left_motor_pid(float goal)
{
  static float error,last_error=0,last_last_error=0,Goal_speed,error_sum;
	Goal_speed = (float)(goal-K_diff);
  left_wheel_goal= Goal_speed;
  
//  if(Goal_speed<2*goal)
//    Goal_speed = Goal_speed;
//  else Goal_speed = 2*goal;  //���ֲ����޷�
  
	error = Goal_speed - 0.0017f*10*Left_Encoder;            //V = N/1024*��30/68*20.1/100*20*10�� = N*0.0017*10 m/s  30Ϊ���������֣�68Ϊ�������֣�20.1Ϊ�����ܳ�����������50ms
  error_sum += error;
  Left_Duty =(int)(K_P_L*error+K_I_L*error_sum+K_D_L*(error-2*last_error+last_last_error));
	
  last_error = error;
	last_last_error = last_error;
	
//	Left_Duty -=  position*0.1;
	Left_Duty = (Left_Duty>8000) ? 8000:Left_Duty;
	Left_Duty = (Left_Duty<0) ? 0:Left_Duty;
	
	
  Moto_L(Left_Duty);
	
}	
/**
  * @brief  �����ٶ�pid
  * @param  goal
  * @retval None
  */
void right_motor_pid(float goal)
{
  static float error,last_error=0,last_last_error=0,Goal_speed_R,error_sum;
	Goal_speed_R = (float)(goal+K_diff);
  right_wheel_goal = Goal_speed_R;
//  
//  if (Goal_speed_R<2*goal)
//    Goal_speed_R = Goal_speed_R;
//  else Goal_speed_R = 2*goal;
//  
	error = Goal_speed_R -0.0017f*10* Right_Encoder;
  error_sum += error;
	Right_Duty=(int)(K_P_R*error+K_I_R*error_sum+K_D_R*(error-2*last_error+last_last_error));
	
	
	
  last_error = error;
	last_last_error = last_error;
	
//	Right_Duty +=  position*0.1;
	
	Right_Duty = Right_Duty>8000 ? 8000:Right_Duty;
	Right_Duty = Right_Duty<0 ? 0:Right_Duty;
	
  Moto_R(Right_Duty);
	
}	

/**
  * @brief  ��������ʼ��
  * @param  None
  * @retval None
  */
void motor_init(void)
{
		pwm_init(PWM_R, 17000, 6000); //��ʼ��PWM1  ʹ��P60����  ��ʼ��Ƶ��Ϊ17Khz
		pwm_init(PWM_L, 17000, 6000); //��ʼ��PWM2  ʹ��P62����  ��ʼ��Ƶ��Ϊ17Khz
	
		gpio_mode(P6_4, GPO_PP);    //�������
		gpio_mode(P6_0, GPO_PP);    //

	//��������ʼ��
	 ctimer_count_init(SPEEDL_PLUSE);	//��ʼ����ʱ��0��Ϊ�ⲿ����
	 ctimer_count_init(SPEEDR_PLUSE);	//��ʼ����ʱ��3��Ϊ�ⲿ����
}


/**
  * @brief  ��ȡ��������ֵ����������ʼ��
  * @param  None
  * @retval None
  */
void Get_Encoder(void)
{
//��ȡ�ɼ����ı�����������
     Left_Encoder = ctimer_count_read(SPEEDL_PLUSE);
		 Right_Encoder = ctimer_count_read(SPEEDR_PLUSE);
	
//����������
    ctimer_count_clean(SPEEDL_PLUSE);
		ctimer_count_clean(SPEEDR_PLUSE);

//�ɼ�������Ϣ
    if(1 == SPEEDL_DIR)
      Left_Encoder =  Left_Encoder;
      else
      Left_Encoder = -Left_Encoder;
		if(1 == SPEEDR_DIR)
      Right_Encoder =-Right_Encoder;
    else
      Right_Encoder = Right_Encoder;
	
	 Average_Encoder = (Left_Encoder + Right_Encoder)*0.5;
   distance += (Average_Encoder * 0.07);  //ת��Ϊ����  distance=600<����>����1��
	
}
/**
  * @brief  ���ֿ���
  * @param  motor1ռ�ձ�
  * @retval None
  */
void Moto_L(int16 moto1)
{
	if(moto1!=0)
		{
    	if(moto1<0)				AIN_L=1;
			else 	          	AIN_L=0;
		}
		pwm_duty(PWM_L,myabs(moto1));
}
/**
  * @brief  ���ֿ���
  * @param  �������ռ�ձ�
  * @retval None
  */
void Moto_R(int16 moto2)
{
	if(moto2!=0)
		{
		  if(moto2<0)	 AIN_R=1;
			else         AIN_R=0;
		}
		pwm_duty(PWM_R,myabs(moto2));
		
}

void set_pwm(int16 moto1,int16 moto2)
{
  Moto_L(moto1);
	Moto_R(moto2);
}
