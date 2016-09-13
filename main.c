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
* 完成日期：2016/8/31
* 编译环境：C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* 历史信息：
*******************************************************************************/
#include "Type.h"
#include "Sys.h"
#include "Eeprom.h"
#include "Ads1220.h"
#include "Ble.h"
#include "Awaken.h"
#include "Battery.h"
#include "Sleep.h"
#include "Time.h"
#include "Mpu.h"

long xx = 0;
extern u8 xxx[10];
/**********************************************函数定义***************************************************** 
* 函数名称: int void(main) 
* 输入参数: main 
* 返回参数: int  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/31
************************************************************************************************************/ 
int main( void ) {
    SysInit();
    EeepromInit();
    BleInit();
    Ads1220Init();
    MpuInit();
    AwakenInit();
    BatteryInit();//
    SleepInit();
    TimerInit();
    INTEN//开启中断
    while( 1 ) {
       static u16 time_count = 0;
       xx = ADS1220ReadData();
       if(AwaenRead() == 0) {
            time_count++;
       }
       if(time_count < 30) {
            time_count++;
       } else {
            time_count = 0;
            ComSend(0x01,xxx[0],xxx[1],xxx[2],xxx[3]);
       }
    }
}
