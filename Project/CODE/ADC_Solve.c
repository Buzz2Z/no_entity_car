/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.3.18
  * @brief   ADC采集滤波
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "headfile.h"
#define FILTER_N 5 // 滤波次数
uint16 adc_date[4];
float Left_Adc = 0, Right_Adc = 0, Left_Xie_Adc = 0, Right_Xie_Adc = 0;
float adc_max[4] = {3800.0, 3800.0, 3800.0, 3800.0};  // 最大值
float adc_min[4] = {0.0, 0.0, 0.0, 0.0};              // 最小值  (给定一个需要)
float Cha, He;
float temp = 0;

/* Functions -----------------------------------------------------------------*/

/**
  * @brief  ADC初始化
  * @param  None
  * @retval None
  */
void adc_Init_all() {
  adc_init(Left_ADC_Pin, ADC_SYSclk_DIV_2);        // 选择ADC引脚，二分频，最高频率
  adc_init(LeftXie_ADC_Pin, ADC_SYSclk_DIV_2);
  adc_init(RightXie_ADC_Pin, ADC_SYSclk_DIV_2);
  adc_init(Right_ADC_Pin, ADC_SYSclk_DIV_2);
} 

/**
  * @brief  对电感采值进行冒泡排序滑动滤波
  * @param  None
  * @retval None
  */
void ADC_Date_Fitier() {
  uint8 i;

  uint16 filter_buf_L[FILTER_N];   // 左横电感储存数组 
  uint16 filter_buf_LC[FILTER_N];  // 左斜电感储存数组 
  uint16 filter_buf_R[FILTER_N];   // 右横电感储存数组
  uint16 filter_buf_RC[FILTER_N];  // 右斜电感储存数组

  // 滑动滤波
  for(i = 0; i < FILTER_N; i++) {
    filter_buf_L[i]  = adc_mean_filter(Left_ADC_Pin, ADC_12BIT, 5);     // 左横
    filter_buf_LC[i] = adc_mean_filter(LeftXie_ADC_Pin, ADC_12BIT, 5);   // 左斜     
    filter_buf_RC[i] = adc_mean_filter(RightXie_ADC_Pin, ADC_12BIT, 5);  // 右斜   
    filter_buf_R[i]  = adc_mean_filter(Right_ADC_Pin, ADC_12BIT, 5);     // 右横  
  }

  // 冒泡排序去极值求平均
  adc_date[0] = Final_Average_Filter(filter_buf_L);    // 左      3800
  adc_date[1] = Final_Average_Filter(filter_buf_R);    // 右      3800
  adc_date[2] = Final_Average_Filter(filter_buf_LC);   // 左斜  3800
  adc_date[3] = Final_Average_Filter(filter_buf_RC);   // 右斜  3800

  normalize_date();  // 归一化处理
}

/**
  * @brief  对电感采值去最大值最小值取平均
  * @param  None
  * @retval None
  */
uint16 Final_Average_Filter(uint16 *Date) {
  uint8 i;
  uint16 max, min;
  uint16 sum = 0;

  max = Date[0];
  min = Date[0];

  for(i = 0; i < 5; i++) {
    if(max < Date[i]) max = Date[i];
    if(min > Date[i]) min = Date[i];
    sum += Date[i];
  }       
  sum = (sum - max - min) / (5 - 2);
  return sum;
}

/**
  * @brief  归一化处理, 结算值结果在0~1000
  * @param  None
  * @retval None
  */
void normalize_date() {
  float temp_Date[4];
  uint16 i;
  for(i = 0; i < 4; i++) {
    temp_Date[i] = (adc_date[i] - adc_min[i]) / (adc_max[i] - adc_min[i]) * 500;
    if (temp_Date[i] < 0) {
      temp_Date[i] = 0.0;
    } else if(temp_Date[i] > 500.0) {
      temp_Date[i] = 500.0;
    }
  }
  Left_Adc = temp_Date[0];    // 左电感最终值
  Right_Adc = temp_Date[1];   // 右电感最终值 
  Left_Xie_Adc = temp_Date[2]; // 左斜电感最终值 
  Right_Xie_Adc = temp_Date[3]; // 右斜电感最终值
}

/**
  * @brief  差比和差
  * @param  Date_1: 左横电感
  *         Date_2: 右横电感
  *         Date_3: 左斜电感
  *         Date_4: 右斜电感
  *         a: 横电感加权系数
  *         b: 斜电感加权系数
  *         X: 左移位数
  * @retval Resault
  */
// int16 Cha_BI_He_Cha(uint16 Date_1, uint16 Date_2, uint16 Date_3, uint16 Date_4, float a, float b, uint16 X) {
//   int16 Resault;
//   int16 FengZ, FengM;
//   Cha_H =  (int16)((Date_1 - Date_2));   // 横电感差
//   Cha_X =  (int16)((Date_3 - Date_4));   // 斜电感差
  
//   He = Date_1 + Date_2;   // 横电感和
//   Sum = Date_1 + Date_2 + Date_3 + Date_4;  // 所有电感之和
//   He_X = Date_3 + Date_4; // 斜电感和
  
//   FengZ = a * Cha_H + b * Cha_X;  
//   FengM = a * He + b * myabs(Cha_X);
//   Resault = ((FengZ << X) / (FengM + 1)); // 差比和差
//   return Resault;
// }

/**
  * @brief  差比和
  * @param  Date_1: 第一个数据
  *         Date_2: 第二个数据
  * @retval Resault
  */
float Cha_BI_He(float Date_1, float Date_2) {
  float Resault;
  Cha =  (Date_1 - Date_2);   // 差
  He = Date_1 + Date_2;   // 和
  Resault = Cha / (He + 1);
  return Resault;
}
