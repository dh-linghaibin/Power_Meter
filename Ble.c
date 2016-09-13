/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�
*
* �ļ���ʶ��
* ժ    Ҫ��
*
*
* ��ǰ�汾��
* ��    �ߣ�lhb Steven
* ������ڣ�2016/9/8
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "Ble.h"
#include "Delay.h"

/*��������*/
static com_data com_data_one;

#define BLE_EN PA_ODR_ODR1
/**********************************************��������***************************************************** 
* ��������: void BleInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/9/8
************************************************************************************************************/ 
void BleInit(void) { 
    PA_DDR_DDR2 = 1;
    PA_CR1_C12 = 1;
    PA_CR2_C22 = 1;
    
    PC_DDR_DDR5 = 1;
    PC_CR1_C15 = 1;
    PC_CR2_C25 = 1;
    
    BLE_EN = 1;
    
    CLK_PCKENR1_PCKEN15 = 1;//�򿪴���ʱ��
    
    USART1_CR1=0x00;
    USART1_CR2=0x00;
    USART1_CR3=0x00; 
    USART1_BRR2=0x02;//02 0a
    USART1_BRR1=0x68;//68 08
    USART1_CR2=0x2c;//������գ����ͣ��������ж�
}
/**********************************************��������***************************************************** 
* ��������: u8 ComGetFlag(void) 
* �������: void 
* ���ز���: u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
u8 ComGetFlag(void) { 
    return com_data_one.rs_ok;
}

/**********************************************��������***************************************************** 
* ��������: u8 ComGetDate(u8 cmd) 
* �������: u8 cmd 
* ���ز���: u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/22
************************************************************************************************************/ 
u8 ComGetDate(u8 cmd) { 
    return com_data_one.data[cmd];
}
/**********************************************��������***************************************************** 
* ��������: void ComSetFlag(u8 cmd) 
* �������: u8 cmd 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/23
************************************************************************************************************/ 
void ComSetFlag(u8 cmd) { 
    com_data_one.rs_ok = 0x00;
}

/**********************************************��������***************************************************** 
* ��������: void ComSend(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/9/10
************************************************************************************************************/ 
void ComSend(u8 cmd, u8 data1, u8 data2, u8 data3,u8 data4) { 
    //while( (UART1_SR&(1<<6)) )/*�ȴ��������*/
    //while(!(com_data_one.s_data_count == 0));
    //USART1_SR &= ~BIT(6);  //��������״̬λ
//    USART1_CR2 |= BIT(6);//�����������
//    USART1_CR2_TCIEN = 1;
//    USART1_CR2_TIEN = 1;
    //com_data_one.s_data_count = 1;
    com_data_one.s_data[0] = 0x3a;
    com_data_one.s_data[1] = cmd;
    com_data_one.s_data[2] = data1;
    com_data_one.s_data[3] = data2;
    com_data_one.s_data[4] = data3;
    com_data_one.s_data[5] = data4;
    com_data_one.s_data[6] = (u8)(cmd+data1+data2+data3+data4);
    com_data_one.s_data[7] = 0x0a;
    //USART1_DR = com_data_one.s_data[0]; 
    //com_data_one.s_data_count++;
    for(u8 i = 0;i < 8;i++) {
        while((USART1_SR & 0x80) == 0x00);
        USART1_DR = com_data_one.s_data[i];
        DelayMs(1);
    }
}

/**********************************************��������***************************************************** 
* ��������: __interrupt USARTx_IRQHandler(void) 
* �������: void 
* ���ز���: __interrupt  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/9/8
************************************************************************************************************/ 
#pragma vector=29
__interrupt void USARTx_IRQHandler(void) {
    //USART1_SR &= ~(1<<6);    //��������״̬λ
//    USART1_CR2_TIEN = 0;
//    USART1_CR2_ILIEN = 0;
//    USART1_CR2_RIEN = 0;
//    USART1_DR = com_data_one.s_data[com_data_one.s_data_count];
//    if(com_data_one.s_data_count < 8) {
//        com_data_one.s_data_count++;
//        DelayMs(1);
//    } else {
//        com_data_one.s_data_count = 0;
//        
//        USART1_CR2 &= ~BIT(6);//�����������?
//        USART1_CR2_TCIEN = 0;
//        USART1_CR2_TIEN = 0;
//    }
}

/**********************************************��������***************************************************** 
* ��������: __interrupt USARTx_IRQHandler(void) 
* �������: void 
* ���ز���: __interrupt  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/9/8
************************************************************************************************************/ 
#pragma vector=30
__interrupt void USARRx_IRQHandler(void) {
    u8 data;
    data = USART1_DR;
    /*�ȴ����ݽ������*/
    while((USART1_SR & 0x80) == 0x00);
    /*��ֹ������ͷ֡��ͻ*/
    if(com_data_one.rs_flag == 0x00) {
        if(data == com_head_frame) {
            com_data_one.rs_flag = 0x01;
        }    
    }
    /*��ʼ��������*/
    if(com_data_one.rs_flag > 0x00) {
        com_data_one.data[com_data_one.rs_flag-1] = data;
        com_data_one.rs_flag++;
        if(com_data_one.rs_flag == com_size+1) {
            if(data == com_tail_frame) {
                com_data_one.rs_ok = 0x01;
                com_data_one.rs_flag = 0x00;
            } else {
                com_data_one.rs_flag = 0x00;
            }
        }
    }
    return;
}

