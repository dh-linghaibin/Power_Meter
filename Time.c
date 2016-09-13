/*******************************************************************************
* Copyright 2016 HangZhou 杭州久天科技有限公司
* All right reserved
*
* 文件名称：time,c
*
* 文件标识：ds
* 摘    要：定时器，用于休眠
*
*
* 当前版本：v1.0
* 作    者：lhb Steven
* 完成日期：2016/3/18
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Time.h"

void TimerInit(void) {
    //CLK_PCKENR = 0x04;
    //TIM4_IER = 0x01;
    //TIM4_PSCR = 0x07;
    //TIM4_ARR = 0x7c; 
    //TIM4_CR1 = 0x01;
}

static u16 sec_flag = 0;

u16 TimerGetSec(void) {
    return sec_flag;
}

void TimerSetSec(u8 data) {
    sec_flag = data;
}

#pragma vector=0x1b
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
    static u16 count_time = 0;
    TIM4_SR1 = 0x00;
    
    if(count_time < 500) {
        count_time++;
    } else {
        count_time = 0;
        sec_flag++;
    }
    
    return;
}


