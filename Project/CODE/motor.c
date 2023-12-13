#include "headfile.h"
#include "motor.h"

int16 Left_Encoder = 0;     //���������ֵ
int16 Right_Encoder = 0;    //�ұ�������ֵ
int16 Average_Encoder = 0;  //���ұ�����ƽ��ֵ
int16 Sum_Encoder = 0;      //�����������
int32 distance = 0;         //�������ߵ�·��

int16 K_diff = 0 ;
//int16 Left_Encoder = 0;


float K_P = 70;
float K_I = 8;
float K_D = 0;

int16 Right_Duty,Left_Duty;

void left_motor_pid(int16 goal)
{
  static int16 error,last_error=0,last_last_error=0,Goal_speed;
	Goal_speed = (int16)((1-K_diff)*goal);
//	Goal_speed = goal;
	error = Goal_speed - Left_Encoder;
	Left_Duty+=K_P*(error-last_error)+K_I*error+K_D*(error-2*last_error+last_last_error);
	
  last_error = error;
	last_last_error = last_error;
	
//	Left_Duty -=  position*0.1;
	Left_Duty = Left_Duty>8000 ? 8000:Left_Duty;
	Left_Duty = Left_Duty<-3000? -3000:Left_Duty;
	
	
  Moto_L(Left_Duty);
	
}	

void right_motor_pid(int16 goal)
{
  static int16 error,last_error=0,last_last_error=0,Goal_speed;
	Goal_speed = (1+K_diff)*goal;
//	Goal_speed = goal;
	error = Goal_speed - Right_Encoder;
	Right_Duty+=K_P*(error-last_error)+K_I*error+K_D*(error-2*last_error+last_last_error);
	
	
  last_error = error;
	last_last_error = last_error;
	
//	Right_Duty +=  position*0.1;
	
	Right_Duty = Right_Duty>8000 ? 8000:Right_Duty;
	Right_Duty = Right_Duty<-3000 ? -3000:Right_Duty;
	
  Moto_R(Right_Duty);
	
}	


void motor_init(void)
{
		pwm_init(PWM_R, 10000, 0); //��ʼ��PWM1  ʹ��P60����  ��ʼ��Ƶ��Ϊ10Khz
		pwm_init(PWM_L, 10000, 0); //��ʼ��PWM2  ʹ��P62����  ��ʼ��Ƶ��Ϊ10Khz
	
		gpio_mode(P6_4, GPO_PP);
		gpio_mode(P6_0, GPO_PP);

	//��������ʼ��
	 ctimer_count_init(SPEEDL_PLUSE);	//��ʼ����ʱ��0��Ϊ�ⲿ����
	 ctimer_count_init(SPEEDR_PLUSE);	//��ʼ����ʱ��3��Ϊ�ⲿ����
}

//��ȡ��������ֵ
void Get_Encoder(void)
{
//��ȡ�ɼ����ı�����������
     Left_Encoder = ctimer_count_read(SPEEDL_PLUSE);
		 Right_Encoder = ctimer_count_read(SPEEDR_PLUSE);
	
//����������
    ctimer_count_clean(SPEEDL_PLUSE);
		ctimer_count_clean(SPEEDR_PLUSE);

//�ɼ�������Ϣ
    if(1 == SPEEDL_DIR)    Left_Encoder = Left_Encoder;
    else                   Left_Encoder = -Left_Encoder;
		if(1 == SPEEDR_DIR)    Right_Encoder =-Right_Encoder;
    else                   Right_Encoder = Right_Encoder;
	
	 Average_Encoder = (Left_Encoder + Right_Encoder)*0.5;
   distance += (Average_Encoder * 0.07);  //ת��Ϊ����  distance=600<����>����1��
	
}

void Moto_L(int16 moto1)
{
	if(moto1!=0)
		{
    	if(moto1<0)				AIN_L=1;
			else 	          	AIN_L=0;
		}
		pwm_duty(PWM_L,myabs(moto1));
}

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




