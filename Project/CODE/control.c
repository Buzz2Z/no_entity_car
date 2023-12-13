/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.3.27
  * @brief   ���ٴ���pid����
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
 /* Includes ------------------------------------------------------------------*/
#include "headfile.h"
/* Private Define ------------------------------------------------------------*/
float speed_output=0;
float Position_Get,Position_pre_Get;
uint8 COUNTS=0;     //���⻷������
float target_vel_z=0;  //Ŀ��Ƕ�
float target_vel_z_pre=0;
float my_gyro_z;
float ZX_kp=0.0;    //ת��PID���ڻ���
float ZX_ki=0.0;//float ZX_ki=0.0032;
float ZX_kd=0;
float Kp_angel_out;//float Kp_angel_out=90;
float Ki_angel_out=0;
float Kd_angel_out=10;       //�⻷pid
float price_Velocite=0;  //ת���������
uint8 stop_flag=0;
/* Private Functions ---------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  ������ٿ���
  * @param  float speed
  * @retval None
  */
void motor_speed(float speed)
{
//	left_motor_pid(speed+price_Velocite);
//  right_motor_pid(speed-price_Velocite);
  left_motor_pid(speed);
  right_motor_pid(speed);
}
/**
  * @brief  �ٶ��������������
  * @param  float a,b
  * @retval None
  */
void set_speed_target(float a,float b)
{
  Position_Get = Cha_BI_He(Left_Xie_Adc,Right_Xie_Adc);
  speed_output = -a*Position_Get*Position_Get + b;
  Kp_angel_out = 800*Position_Get*Position_Get + 130;//70,20
  K_diff =0.5*target_vel_z*0.2*(2*3.1415926/360);
  if(K_diff<=speed_output && K_diff>=(-speed_output))K_diff = K_diff;
  else K_diff=0;
  motor_speed(speed_output);
}
/**
  * @brief  None
  * @param  None
  * @retval None
  */
void DifferControl(){
//ת���⻷50ms,ת���ڻ�10ms
	//�����ڻ���ִ��һ���ڻ�
//  if(COUNTS==5){
//    COUNTS=0;
    DerectError_Get();
//  }
//  COUNTS++;
  my_gyro_z = imu660ra_gyro_transition(imu660ra_gyro_z);
  if(my_gyro_z<5 && my_gyro_z>(-5))
    my_gyro_z = 0;    //����������
  //target_vel_z=target_vel_z_pre+(target_vel_z-target_vel_z_pre)*COUNTS/5;
  //Direction_out();
}

void DerectError_Get(void)  //�⻷
{ 
    //target_vel_z=Kp_angel_out*Position_Get+Kd_angel_out*(Position_Get-Position_pre_Get);
    target_vel_z=Kp_angel_out*Position_Get+my_gyro_z;//������
   //target_vel_z=20; //������仰����ת��ֻ���ڻ����⻷���Ϊ0
     Position_pre_Get=Position_Get;
     target_vel_z_pre=target_vel_z;
}

/**
  * @brief  ���ٶ��ڻ�������
  * @param  None
  * @retval None
  */
void Direction_out(void)
{
  float error;
  static  float last_error;
  float price_Differention;
  float price_Intergration;
  float price_Proportion;
  static float Pre1_Error[4];
  float Direct_Parameter;
  static float sum;
	/*ֱ�߻��������ҡ�Ұڵ��ڻ�KP��KD*/
  error = target_vel_z-my_gyro_z;  
	//ת��PID����
  sum = error++;
  price_Proportion=ZX_kp * error;
  price_Intergration=ZX_ki * sum;
  price_Differention= ZX_kd* (error - last_error);
  
  Direct_Parameter =price_Proportion  + price_Differention + price_Intergration;
  
  last_error =  error; 
  Pre1_Error[3]=Pre1_Error[2];
  Pre1_Error[2]=Pre1_Error[1];
  Pre1_Error[1]=Pre1_Error[0];
  Pre1_Error[0]=Direct_Parameter;
  Direct_Parameter=Pre1_Error[0]*0.8+Pre1_Error[1]*0.1+Pre1_Error[2]*0.06+Pre1_Error[3]*0.04 ;
  price_Velocite= - Direct_Parameter;
	//ת������ٶ����Ʒ���
 if(price_Velocite>=1) price_Velocite=1;
  if(price_Velocite<=-1) price_Velocite=-1;
 
}