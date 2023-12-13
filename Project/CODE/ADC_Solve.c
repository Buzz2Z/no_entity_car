/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.3.18
  * @brief   adc�ɼ��˲�
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
 /* Includes ------------------------------------------------------------------*/
#include "headfile.h"
#define FILTER_N 5 //�˲�����
uint16 adc_date[4];
float Left_Adc=0,Right_Adc=0,Left_Xie_Adc=0,Right_Xie_Adc=0;
float  adc_max[4]={3800.0,3800.0,3800.0,3800.0};               //���ֵ
float  adc_min[4]={0.0,0.0,0.0,0.0};               //��Сֵ  (����һ����Ҫ)
float Cha,He;
float temp=0;
/* Functions -----------------------------------------------------------------*/
/**
  * @brief  adc��ʼ��
  * @param  None
  * @retval None
  */
void adc_Init_all(){
  adc_init(Left_ADC_Pin,ADC_SYSclk_DIV_2);             //ѡ��adc���ţ�����Ƶ�����Ƶ��
  adc_init(LeftXie_ADC_Pin,ADC_SYSclk_DIV_2); 
  adc_init(RightXie_ADC_Pin,ADC_SYSclk_DIV_2); 
  adc_init(Right_ADC_Pin,ADC_SYSclk_DIV_2); 
} 

/**
  * @brief  �Ե�в�ֵ����ð�����򻬶��˲�
  * @param  None
  * @retval None
  */
 void ADC_Date_Fitier()
{
   uint8 i;
  
  uint16 filter_buf_L[FILTER_N];  //����д������� 
  uint16 filter_buf_LC[FILTER_N]; //��б��д������� 
  uint16 filter_buf_R[FILTER_N];  //�Һ��д�������
  uint16 filter_buf_RC[FILTER_N];  //��б��д�������
  
 
//--------�����˲�--------------
	for(i = 0; i <FILTER_N; i++)//��ֵ 
  {
       filter_buf_L[i]  =   adc_mean_filter (Left_ADC_Pin,ADC_12BIT,5); //���
       filter_buf_LC[i] =   adc_mean_filter  (LeftXie_ADC_Pin,ADC_12BIT,5); //��б     
       filter_buf_RC[i] =  adc_mean_filter  (RightXie_ADC_Pin,ADC_12BIT,5);    //��б   
       filter_buf_R[i]  =  adc_mean_filter  (Right_ADC_Pin,ADC_12BIT,5);   //�Һ�  
   }
//--------ð������ȥ��ֵ��ƽ��---------
  adc_date[0]= Final_Average_Filter(filter_buf_L);//��      3800
  adc_date[1] =Final_Average_Filter(filter_buf_R);//��      3800
  adc_date[2] = Final_Average_Filter(filter_buf_LC);//��б  3800
  adc_date[3] = Final_Average_Filter(filter_buf_RC);//��б  3800

	normalize_date();//��һ������
	 
//  Left_Adc = adc_date[0];//��������ֵ
//  Right_Adc = adc_date[1];//�ҵ������ֵ 
//  Left_Xie_Adc = adc_date[2];//��б�������ֵ 
//  Right_Xie_Adc = adc_date[3];//��б�������ֵ


 

}
/**
  * @brief  �Ե�в�ֵȥ���ֵ��Сֵȡƽ��
  * @param  None
  * @retval None
  */
uint16 Final_Average_Filter(uint16 *Date)
{
  uint8 i;
  uint16 max,min;
  uint16 sum=0;
  
  max = Date[0];
  min = Date[0];
  
  for(i=0;i<5;i++)
  {
       if(max<Date[i]) max = Date[i];
       if(min>Date[i]) min = Date[i];
       sum += Date[i];
  }       
  sum = (sum-max-min)/(5-2);
  return sum;
}
/**
  * @brief  ��һ������,����ֵ�����0~1000
  * @param  None
  * @retval None
  */
void normalize_date()
{
  float temp_Date[4];
  uint16 i;
  for(i=0;i<4;i++)
  {
//    if(adc_date[i]<adc_min[i])
//    {
//      adc_min[i]=adc_date[i];
//    }
//   else if(adc_date[i]>adc_max[i])
//   {  
//   adc_max[i]=adc_date[i];
//   } 
     temp_Date[i] = (adc_date[i]-adc_min[i])/(adc_max[i]-adc_min[i])*500;
    if (temp_Date[i]<0)
    {
      temp_Date[i]=0.0;
    }
      else if(temp_Date[i]>500.0)
      {
      temp_Date[i]=500.0;
      }
      }
  Left_Adc = temp_Date[0];//��������ֵ
  Right_Adc = temp_Date[1];//�ҵ������ֵ 
  Left_Xie_Adc = temp_Date[2];//��б�������ֵ
  Right_Xie_Adc = temp_Date[3];//��б�������ֵ
}

///*****************��ȺͲ�***********************
//������ int16 Cha_BI_He_Cha(uint16 Date_1,uint16 Date_2,uint16 Date_3,uint16 Date_4,float a,float b,uint16 X)
//������  float Date_1--�����  float Date_2--�Һ��� 
//        float Date_3--��б���  float Date_4--��б��� 
//        float a--���м�Ȩϵ��  float b-- б��м�Ȩϵ��   int16 X--����λ��
//˵����  ��
//����ֵ��Resault
//���ڣ�2022-3-28
//����޸�ʱ�䣺2022-3-28
//���ߣ�       */
//int16 Cha_BI_He_Cha(uint16 Date_1,uint16 Date_2,uint16 Date_3,uint16 Date_4,float a,float b,uint16 X)
//{
//  int16 Resault;
//	int16 FengZ,FengM;
//  Cha_H =  (int16)((Date_1 - Date_2));   //���в�
//	Cha_X =  (int16)((Date_3 - Date_4));   //б��в�
//	
//  He =   Date_1 + Date_2;   //���к�
//	Sum = Date_1 + Date_2 + Date_3 + Date_4;  //���е��֮��
//	He_X = Date_3 + Date_4; //б��к�
//	
//  FengZ = a*Cha_H+b*Cha_X;  
//	FengM = a*He+b*myabs(Cha_X);
//	Resault = ((FengZ<<X)/(FengM+1)); //��ȺͲ�
//  return   Resault;
//}


//////////ȥ����ֵ��ƽ��
//int16 I_Median_Average_Filter(int16 *DATE)
//{
//    uint8 i;
//    int16 max,min;  //���弫ֵ�Լ���
//    int16 sum = 0;

//    max = DATE[0];
//    min = DATE[0];

//    for(i=0;i<sizeof(DATE);i++)
//    {
//        if(max<DATE[i]) max = DATE[i];
//        if(min>DATE[i]) min = DATE[i];
//        sum += DATE[i];
//    }

//    sum =(sum-max-min)/(sizeof(DATE)-2);    //>>3
//    return sum;
//}
/*****************��Ⱥ�***********************
������ float Cha_BI_He(float Date_1,float Date_2,int16 X)
������  float Date_1--��һ������  float Date_2--�ڶ�������  int16 X--����λ��
˵����  ��
����ֵ����
���ڣ�2022-3-19
����޸�ʱ�䣺2022-3-19
���ߣ�      */
float Cha_BI_He(float Date_1,float Date_2)
{
  float Resault;
  Cha =  (Date_1 - Date_2);   //��
  He =   Date_1 + Date_2;   //��
  //Resault = (Cha<<X/(He+1)) ; //��Ⱥ�
  Resault = Cha / (He+1);


  return   Resault;
}