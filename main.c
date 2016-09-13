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
* ������ڣ�2016/8/31
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
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
/**********************************************��������***************************************************** 
* ��������: int void(main) 
* �������: main 
* ���ز���: int  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/31
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
    INTEN//�����ж�
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
