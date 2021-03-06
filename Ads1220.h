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
#ifndef __ADS1220_H
#define __ADS1220_H

#include "Type.h"

#define ADS1220_RESET_CMD          0x06
#define ADS1220_WREG_CMD           0x40
#define ADS1220_RREG_CMD           0x20
#define ADS1220_RDATA_CMD          0x10
#define ADS1220_START_CMD          0x08
#define ADS1220_POWERDOWN_CMD      0x02


#define ADS1220_WRITE_CMD(reg,len)     (ADS1220_WREG_CMD + (reg << 2) + (len-1))
#define ADS1220_READ_CMD(reg,len)      (ADS1220_RREG_CMD + (reg << 2) + (len-1))


#define ADS1220_CONFIG_0_REG      0
#define ADS1220_CONFIG_1_REG      1
#define ADS1220_CONFIG_2_REG      2
#define ADS1220_CONFIG_3_REG      3


// Configuration Register 0 Settings  00h
#define ADS1220_MUX_MASK          0xf0
#define ADS1220_MUX_SHIFT         4

#define ADS1220_MUX_AIN0_AIN1     (0x0 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN0_AIN2     (0x1 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN0_AIN3     (0x2 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN1_AIN2     (0x3 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN1_AIN3     (0x4 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN2_AIN3     (0x5 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN1_AIN0     (0x6 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN3_AIN2     (0x7 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN0_AVSS     (0x8 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN1_AVSS     (0x9 << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN2_AVSS     (0xa << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AIN3_AVSS     (0xb << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_REFP_REFN     (0xc << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_AVDD_AVSS     (0xd << ADS1220_MUX_SHIFT)
#define ADS1220_MUX_SHORTED       (0xe << ADS1220_MUX_SHIFT)


#define ADS1220_GAIN_MASK         0xe
#define ADS1220_GAIN_SHIFT        1

#define ADS1220_GAIN_1            (0x0 << ADS1220_GAIN_SHIFT)
#define ADS1220_GAIN_2            (0x1 << ADS1220_GAIN_SHIFT)
#define ADS1220_GAIN_4            (0x2 << ADS1220_GAIN_SHIFT)
#define ADS1220_GAIN_8            (0x3 << ADS1220_GAIN_SHIFT)
#define ADS1220_GAIN_16           (0x4 << ADS1220_GAIN_SHIFT)
#define ADS1220_GAIN_32           (0x5 << ADS1220_GAIN_SHIFT)
#define ADS1220_GAIN_64           (0x6 << ADS1220_GAIN_SHIFT)
#define ADS1220_GAIN_128          (0x7 << ADS1220_GAIN_SHIFT)

#define ADS1220_PGA_BYPASS        1
#define ADS1220_USE_PGA           0


// Configuration Register 1 Settings   01h

#define ADS1220_DATA_RATE_MASK    0xe0
#define ADS1220_DATA_RATE_SHIFT   5

#define ADS1220_DATA_RATE_20SPS   (0 << ADS1220_DATA_RATE_SHIFT)
#define ADS1220_DATA_RATE_45SPS   (1 << ADS1220_DATA_RATE_SHIFT)
#define ADS1220_DATA_RATE_90SPS   (2 << ADS1220_DATA_RATE_SHIFT)
#define ADS1220_DATA_RATE_175SPS  (3 << ADS1220_DATA_RATE_SHIFT)
#define ADS1220_DATA_RATE_330SPS  (4 << ADS1220_DATA_RATE_SHIFT)
#define ADS1220_DATA_RATE_600SPS  (5 << ADS1220_DATA_RATE_SHIFT)
#define ADS1220_DATA_RATE_1000SPS (6 << ADS1220_DATA_RATE_SHIFT)

#define ADS1220_OP_MODE_MASK      0x18
#define ADS1220_OP_MODE_SHIFT     3

#define ADS1220_OP_MODE_NORMAL    (0 << ADS1220_OP_MODE_SHIFT)
#define ADS1220_OP_MODE_DUTY      (1 << ADS1220_OP_MODE_SHIFT)
#define ADS1220_OP_MODE_TURBO     (2 << ADS1220_OP_MODE_SHIFT)

#define ADS1220_CONVERSION_MODE_MASK     0x4
#define ADS1220_CONVERSION_SINGLE_SHOT   0x0
#define ADS1220_CONVERSION_CONTINUOUS    0x4

#define ADS1220_TEMP_SENSOR_MASK         0x2
#define ADS1220_TEMP_SENSOR_ON           0x2
#define ADS1220_TEMP_SENSOR_OFF          0x0

#define ADS1220_BURN_OUT_MASK            0x1
#define ADS1220_BURN_OUT_CURRENT_ON      0x1
#define ADS1220_BURN_OUT_CURRENT_OFF     0x0

// Configuration Register 2 Settings   02h

#define ADS1220_VREF_MASK                0xc0
#define ADS1220_VREF_SHIFT               6

#define ADS1220_VREF_INTERNAL            (0 << ADS1220_VREF_SHIFT)
#define ADS1220_VREF_EXT_REF0_PINS       (1 << ADS1220_VREF_SHIFT)
#define ADS1220_VREF_EXT_REF1_PINS       (2 << ADS1220_VREF_SHIFT)
#define ADS1220_VREF_AVDD                (3 << ADS1220_VREF_SHIFT)

#define ADS1220_FIR_FILTER_MASK          0x30
#define ADS1220_FIR_FILTER_SHIFT         4

#define ADS1220_FIR_NONE                 (0 << ADS1220_FIR_FILTER_SHIFT)
#define ADS1220_FIR_50_60                (1 << ADS1220_FIR_FILTER_SHIFT)
#define ADS1220_FIR_50                   (2 << ADS1220_FIR_FILTER_SHIFT)
#define ADS1220_FIR_60                   (3 << ADS1220_FIR_FILTER_SHIFT)

#define ADS1220_LOW_SIDE_POWER_MASK      0x04
#define ADS1220_LOW_SIDE_POWER_OPEN      0x00
#define ADS1220_LOW_SIDE_POWER_CLOSES    0x04

#define ADS1220_IDAC_CURRENT_MASK        0x07
#define ADS1220_IDAC_CURRENT_SHIFT       0

#define ADS1220_IDAC_CURRENT_OFF         (0 << ADS1220_IDAC_CURRENT_SHIFT)
#define ADS1220_IDAC_CURRENT_10_UA       (1 << ADS1220_IDAC_CURRENT_SHIFT)
#define ADS1220_IDAC_CURRENT_50_UA       (2 << ADS1220_IDAC_CURRENT_SHIFT)
#define ADS1220_IDAC_CURRENT_100_UA      (3 << ADS1220_IDAC_CURRENT_SHIFT)
#define ADS1220_IDAC_CURRENT_250_UA      (4 << ADS1220_IDAC_CURRENT_SHIFT)
#define ADS1220_IDAC_CURRENT_500_UA      (5 << ADS1220_IDAC_CURRENT_SHIFT)
#define ADS1220_IDAC_CURRENT_1000_UA     (6 << ADS1220_IDAC_CURRENT_SHIFT)
#define ADS1220_IDAC_CURRENT_1500_UA     (7 << ADS1220_IDAC_CURRENT_SHIFT)

// Configuration Register 3 Settings   03h

#define ADS1220_IDAC1_MUX_MASK           0xe0
#define ADS1220_IDAC1_MUX_SHIFT          5

#define ADS1220_IDAC1_DISABLED           (0 << ADS1220_IDAC1_MUX_SHIFT)
#define ADS1220_IDAC1_AIN0               (1 << ADS1220_IDAC1_MUX_SHIFT)
#define ADS1220_IDAC1_AIN1               (2 << ADS1220_IDAC1_MUX_SHIFT)
#define ADS1220_IDAC1_AIN2               (3 << ADS1220_IDAC1_MUX_SHIFT)
#define ADS1220_IDAC1_AIN3               (4 << ADS1220_IDAC1_MUX_SHIFT)
#define ADS1220_IDAC1_REFP0              (5 << ADS1220_IDAC1_MUX_SHIFT)
#define ADS1220_IDAC1_REFN0              (6 << ADS1220_IDAC1_MUX_SHIFT)

#define ADS1220_IDAC2_MUX_MASK           0x1c
#define ADS1220_IDAC2_MUX_SHIFT          2

#define ADS1220_IDAC2_DISABLED           (0 << ADS1220_IDAC2_MUX_SHIFT)
#define ADS1220_IDAC2_AIN0               (1 << ADS1220_IDAC2_MUX_SHIFT)
#define ADS1220_IDAC2_AIN1               (2 << ADS1220_IDAC2_MUX_SHIFT)
#define ADS1220_IDAC2_AIN2               (3 << ADS1220_IDAC2_MUX_SHIFT)
#define ADS1220_IDAC2_AIN3               (4 << ADS1220_IDAC2_MUX_SHIFT)
#define ADS1220_IDAC2_REFP0              (5 << ADS1220_IDAC2_MUX_SHIFT)
#define ADS1220_IDAC2_REFN0              (6 << ADS1220_IDAC2_MUX_SHIFT)

#define ADS1220_DOUT_DRDY_MASK           0x2
#define ADS1220_DRDY_ON_DOUT_DRDY        0x2
#define ADS1220_DRDY_ON_DRDY_ONLY        0x0

/**********************************************函数定义***************************************************** 
* 函数名称: void void(Ads1220Init) 
* 输入参数: Ads1220Init 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/8/31
************************************************************************************************************/ 
void Ads1220Init(void);
int ADS1220_Read_Data( void );
void ADS1220_Init(void);
unsigned long ADS1220ReadData(void);

#endif


