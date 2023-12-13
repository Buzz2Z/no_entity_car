#ifndef _MOTOR_H
#define _MOTOR_H

#define AIN_L P64
#define AIN_R P60
#define PWM_L PWMA_CH4P_P66
#define PWM_R PWMA_CH2P_P62

//������������
#define SPEEDL_PLUSE   CTIM0_P34
#define SPEEDR_PLUSE   CTIM3_P04
//���巽������
#define SPEEDL_DIR     P35
#define SPEEDR_DIR     P53


extern int16 Left_Encoder ;
extern int16 Right_Encoder ;
extern int16 Average_Encoder;  //���ұ�����ƽ��ֵ
extern int16 Sum_Encoder;      //�����������
extern int32 distance;         //�������ߵ�·��
extern Right_Duty;
extern Left_Duty;
extern float K_P ;
extern float K_I ;
extern float K_D ;

void motor_init(void);
void Get_Encoder(void);
void Moto_L(int16 moto1);
void Moto_R(int16 moto2);
void set_pwm(int16 moto1,int16 moto2);
void left_motor_pid(int16 goal);
void right_motor_pid(int16 goal);


#endif
