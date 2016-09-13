/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：
*
* 文件标识：
* 摘    要：
*
*
* 当前版本：
* 作    者：lhb Steven
* 完成日期：2016/9/10
* 编译环境：D:\iar\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Battery.h"
#include "Delay.h"

#define BATTERY  PD_ODR_ODR0

/**********************************************函数定义***************************************************** 
* 函数名称: void BatteryInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/9/10
************************************************************************************************************/ 
void BatteryInit(void) { 
    PD_DDR_DDR0 = 1;
    PD_CR1_C10 = 1;
    PD_CR2_C20 = 1;
    
    PB_DDR_DDR0 = 0;
    PB_CR1_C10 = 0;
    PB_CR2_C20 = 0;
    
    BATTERY = 0;
}

/**********************************************函数定义***************************************************** 
* 函数名称: u16 BattertGetEle(void) 
* 输入参数: void 
* 返回参数: u16  
* 功    能: 获取电量 电量x100  
* 作    者: by lhb_steven
* 日    期: 2016/9/10
************************************************************************************************************/ 
u16 BattertGetEle(void) { 
    float volate = 0;
    u16 ele = 0;
    u16 ad_value;
    u8 ad_h = 0;
    u8 ad_l = 0;
	u8 i;
    u8 chx = 18;
    BATTERY = 1;
    //等待稳定
    DelayMs(5);
	ADC1_SQR4 = ADC1_SQR3 = ADC1_SQR2 = ADC1_SQR1 = 0;
    if (chx<=7)
    ADC1_SQR4 |= (1<<chx);
    else if (chx<=15)
    ADC1_SQR3 |= (1<<(chx-8));
    else if (chx<=23)
    ADC1_SQR2 |= (1<<(chx-16));
    ADC1_CR1 |= (1<<1);
    for (i=0  ; i<100; i++); //简单延时下
    while ((ADC1_SR & (1<<0))==0); //等待取样结束
    ADC1_SR &= (~(1<<0));          //马上清标志位
    ad_h = ADC1_DRH;
    ad_l = ADC1_DRL;
	ad_value = (ad_h<<8) + ad_l;
    volate = (15.95*ad_value)/0xffff*10;
    ele = (u16)volate*100;
    BATTERY = 0;
    return ele;
}





