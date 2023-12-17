/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020, ��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file        main
 * @company     �ɶ���ɿƼ����޹�˾
 * @author      ��ɿƼ�(QQ790875685)
 * @version     �鿴doc��version�ļ� �汾˵��
 * @Software    MDK FOR C251 V5.60
 * @Target core STC32G12K128
 * @Taobao      https://seekfree.taobao.com/
 * @date        2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"
// ����ϵͳƵ��
//#define PWM_1 PWMA_CH1P_P20;
//#define PWM_2 PWMA_CH2P_P22;
//#define PLUSE_LEFT CTIM0_P34
//#define PLUSE_RIGHT CTIM3_P04
//#define DIR_LEFT P35
//#define DIR_RIGHT P53
//#define DIR_1 P62
//#define DIR_2 P66
//#define PWM_1 PWMA_CH3P_P64
//#define PWM_2 PWMA_CH1P_P60

//int16 encoder_left = 0;
//int16 encoder_right = 0;
uint16 right_adc_1 = 0, adc_2 = 0, adc_3 = 0, adc_4 = 0;
uint16 count = 0;
float pos;
float temp_test;

void main()
{
    board_init();   // ��ʼ���Ĵ�������ɾ���˾���롣

    // �˴���д�û�����(���磺�����ʼ�������)
    //lcd_init();
    motor_init();
    imu660ra_init();
    //servo_init();
    //adc_init(Right_ADC_Pin, ADC_SYSclk_DIV_2);
    adc_Init_all();
    //pit_timer_ms(TIM_1, 1);   // ��ʱ��4  50ms�ж�
    bluetooth_ch9141_init();

    // ctimer_count_init(SPEEDL_PLUSE);
    // ctimer_count_init(PLUSE_RIGHT);

    // gpio_mode(P6_4,GPO_PP);
    // gpio_mode(P6_0,GPO_PP);
    // pwm_init(PWMA_CH3P_P64, 17000, 0);
    // pwm_init(PWMA_CH1P_P60, 17000, 0);
    //  pwm_init(PWMA_CH4P_P66, 10000, 0);

    //  gpio_mode(P6_4,GPO_PP);
    //  gpio_pull_set(P6_4,PULLUP);

    EnableGlobalIRQ();   // �������ж�
    while (1)
    {
        // encoder_left = ctimer_count_read(PLUSE_LEFT);
        // if (DIR_LEFT == 0) encoder_left = -encoder_left;
        // else  encoder_left = encoder_left;
        // ctimer_count_clean(PLUSE_LEFT);
        // right_adc_1 = adc_once(Left_ADC_Pin, ADC_12BIT);
        // adc_2 = adc_once(LeftXie_ADC_Pin, ADC_12BIT);
        // adc_3 = adc_once(RightXie_ADC_Pin, ADC_12BIT);
        // adc_4 = adc_once(Right_ADC_Pin, ADC_12BIT);
        // encoder_right = ctimer_count_read(PLUSE_RIGHT);
        // if (DIR_RIGHT == 0) encoder_right = -encoder_right;
        // else  encoder_right = encoder_right;
        // ctimer_count_clean(PLUSE_RIGHT);

        // Moto_L(1000);
        // Moto_R(1000);
        // DIR_1  = 0;
        // pwm_duty(PWMA_CH3P_P64,1000);
        // DIR_2 = 0;
        // pwm_duty(PWMA_CH1P_P60,5000);
        // delay_ms(2000);

        // DIR_1  = 1;
        // pwm_duty(PWMA_CH3P_P64,5000);
        // DIR_2 = 1;
        // pwm_duty(PWMA_CH1P_P60,5000);
        // delay_ms(2000);
        // Get_Encoder();
        // Moto_L(1000);
        // left_motor_pid(1);
        ///uart_putstr(UART_1,"123");
        //uart_putchar(UART_1,123);
        //ADC_Date_Fitier();
        //right_adc = adc_mean_filter  (Right_ADC_Pin,ADC_12BIT,5);
        //ADC_Date_Fitier();

        //imu660ra_get_gyro();

        // temp_test = 1800/3800.0*500;
        // printf("g:%f,%f,%f,%f,%f,%f,%f,%f,%f\r\n",Left_Encoder*0.0017f*10,Right_Encoder*0.0017f*10,Left_Xie_Adc,Right_Xie_Adc,Left_Adc,Right_Adc,100.0,right_wheel_goal,left_wheel_goal);
        //printf("g: %d,%d,%d,%d,%d\r\n",Left_Encoder,right_adc_1,adc_2,adc_3,adc_4);
        //printf("%f\r\n",Left_Encoder);
        // lcd_showstr(0,0,"lyx");
        // lcd_showuint16(0,1,count++);
        //lcd_showfloat(0,2,1234.56,4,1);
        //    lcd_showuint8(0,2,right_adc_1);
        // lcd_showint16(0,2,Left_Encoder);
        // lcd_showint16(0,3,Right_Encoder);

        // lcd_showint16(0,4,imu660ra_gyro_x);
        // lcd_showint16(0,5,imu660ra_gyro_y);
        // lcd_showint16(0,6,imu660ra_gyro_z);

        //    lcd_showint16(0,4,Left_Adc);
        //    lcd_showint16(0,5,Right_Adc);
        //    lcd_showint16(0,6,Left_Xie_Adc);
        //    lcd_showint16(0,7,Right_Xie_Adc);
        //lcd_showint16(0,5,a);
        //lcd_showfloat(0,5,error_sum,50,50);
        //delay_ms(50);
        //pwm_init(PWM_1,17000,0);

        //pwm_duty(PWMA_CH4P_P66,10000);
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}
