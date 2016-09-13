/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�time,c
*
* �ļ���ʶ��ds
* ժ    Ҫ����ʱ������������
*
*
* ��ǰ�汾��v1.0
* ��    �ߣ�lhb Steven
* ������ڣ�2016/3/18
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
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


