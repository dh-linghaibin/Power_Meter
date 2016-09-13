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
* 完成日期：2016/9/8
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Ble.h"
#include "Delay.h"

/*串口数据*/
static com_data com_data_one;

#define BLE_EN PA_ODR_ODR1
/**********************************************函数定义***************************************************** 
* 函数名称: void BleInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/9/8
************************************************************************************************************/ 
void BleInit(void) { 
    PA_DDR_DDR2 = 1;
    PA_CR1_C12 = 1;
    PA_CR2_C22 = 1;
    
    PC_DDR_DDR5 = 1;
    PC_CR1_C15 = 1;
    PC_CR2_C25 = 1;
    
    BLE_EN = 1;
    
    CLK_PCKENR1_PCKEN15 = 1;//打开串口时钟
    
    USART1_CR1=0x00;
    USART1_CR2=0x00;
    USART1_CR3=0x00; 
    USART1_BRR2=0x02;//02 0a
    USART1_BRR1=0x68;//68 08
    USART1_CR2=0x2c;//允许接收，发送，开接收中断
}
/**********************************************函数定义***************************************************** 
* 函数名称: u8 ComGetFlag(void) 
* 输入参数: void 
* 返回参数: u8  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/22
************************************************************************************************************/ 
u8 ComGetFlag(void) { 
    return com_data_one.rs_ok;
}

/**********************************************函数定义***************************************************** 
* 函数名称: u8 ComGetDate(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: u8  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/22
************************************************************************************************************/ 
u8 ComGetDate(u8 cmd) { 
    return com_data_one.data[cmd];
}
/**********************************************函数定义***************************************************** 
* 函数名称: void ComSetFlag(u8 cmd) 
* 输入参数: u8 cmd 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/6/23
************************************************************************************************************/ 
void ComSetFlag(u8 cmd) { 
    com_data_one.rs_ok = 0x00;
}

/**********************************************函数定义***************************************************** 
* 函数名称: void ComSend(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/9/10
************************************************************************************************************/ 
void ComSend(u8 cmd, u8 data1, u8 data2, u8 data3,u8 data4) { 
    //while( (UART1_SR&(1<<6)) )/*等待发送完毕*/
    //while(!(com_data_one.s_data_count == 0));
    //USART1_SR &= ~BIT(6);  //清除送完成状态位
//    USART1_CR2 |= BIT(6);//开发送完成中
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

/**********************************************函数定义***************************************************** 
* 函数名称: __interrupt USARTx_IRQHandler(void) 
* 输入参数: void 
* 返回参数: __interrupt  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/9/8
************************************************************************************************************/ 
#pragma vector=29
__interrupt void USARTx_IRQHandler(void) {
    //USART1_SR &= ~(1<<6);    //清除送完成状态位
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
//        USART1_CR2 &= ~BIT(6);//开发送完成中?
//        USART1_CR2_TCIEN = 0;
//        USART1_CR2_TIEN = 0;
//    }
}

/**********************************************函数定义***************************************************** 
* 函数名称: __interrupt USARTx_IRQHandler(void) 
* 输入参数: void 
* 返回参数: __interrupt  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/9/8
************************************************************************************************************/ 
#pragma vector=30
__interrupt void USARRx_IRQHandler(void) {
    u8 data;
    data = USART1_DR;
    /*等待数据接受完成*/
    while((USART1_SR & 0x80) == 0x00);
    /*防止数据与头帧冲突*/
    if(com_data_one.rs_flag == 0x00) {
        if(data == com_head_frame) {
            com_data_one.rs_flag = 0x01;
        }    
    }
    /*开始结束数据*/
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

