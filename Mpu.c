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
#include "Mpu.h"
#include "Delay.h"

#define MPU_SCL         PC_ODR_ODR1
#define MPU_SDA         PC_ODR_ODR0
#define MPU_SDA_DR      PC_DDR_DDR0
#define MPU_SDA_IN      PC_IDR_IDR0

/**********************************************函数定义***************************************************** 
* 函数名称: void MpuInit(void) 
* 输入参数: void 
* 返回参数: void  
* 功    能:   
* 作    者: by lhb_steven
* 日    期: 2016/9/10
************************************************************************************************************/ 
void MpuInit(void) { 
    PC_DDR_DDR0 = 1;
    PC_CR1_C10 = 1;
    PC_CR2_C20 = 0;
    
    PC_DDR_DDR1 = 1;
    PC_CR1_C11 = 1;
    PC_CR2_C21 = 1;
    
    PC_DDR_DDR4 = 0;
    PC_CR1_C14 = 0;
    PC_CR2_C24 = 0;
    
    InitMPU6050();
}

//**************************************
//I2C起始信号
//**************************************
void I2C_Start(void)
{
	MPU_SCL = 1;//set SCL pin as output high
	MPU_SDA = 1;//set SDA pin as output high
    DelayUs(20);
	MPU_SDA = 0;//set SDA pin as output low
    DelayUs(20);
	MPU_SCL = 0;//set SDA pin as output low
}
//**************************************
//I2C接收应答信号
//**************************************
u8 I2C_RecvACK(void)
{
    u8 flag = 0;
    MPU_SCL = 1;//set SCL pin as output high 
    MPU_SDA_DR = 0; //set sda as input with pull up            
    DelayUs(20);            
    if(MPU_SDA_IN) {
        flag=1;
    } else {
        flag=0;
    }
    MPU_SCL = 0;;      //set SCL pin as output low             
    DelayUs(20);
    MPU_SDA_DR = 1;
    return flag;
}
//**************************************
//I2C发送应答信号
//入口参数:ack (0:ACK 1:NAK)
//**************************************
void I2C_SendACK(u8 ack)
{
    if (ack==1) {
        MPU_SDA = 1;//set SDA pin as output high
    } else {
        MPU_SDA = 0;//set SDA pin as output low
    }
    MPU_SCL = 1;//set SCL pin as output high
    DelayUs(20);//延时
    MPU_SCL = 0;  //set SCL pin as output low
    DelayUs(20);//延时
}

//**************************************
//向I2C总线发送一个字节数据
//**************************************
void I2C_SendByte(u8 dat)
{
    u8 i;
    for (i=0; i<8; i++)         //8位计数器
    {                  
        if (dat&0x80)
        {
            MPU_SDA = 1;//set SDA pin as output high
        }
        else
        {
            MPU_SDA = 0;//set SDA pin as output low
        }
        dat <<= 1;   //移出数据的最高位
        MPU_SCL = 1;//set SCL pin as output high
        DelayUs(20);
        MPU_SCL = 0;  //set SCL pin as output low
        DelayUs(20);
    }
    I2C_RecvACK();
}

//**************************************
//从I2C总线接收一个字节数据
//**************************************
u8 I2C_RecvByte(void) {
    u8 i;
    u8 dat = 0;
    MPU_SDA = 0;//set SDA pin as output high 
    //使能内部上拉,准备读取数据,
    MPU_SDA_DR = 0; //set sda as input with pull up
    for (i=0; i<8; i++) {//8位计数器
        dat <<= 1;
        MPU_SCL = 1;//set SCL pin as output high
        DelayUs(20);            //延时
        if(MPU_SDA_IN) {         
            dat|=0x01;
        } else {
            dat|=0;
        }
        MPU_SCL = 0;  //set SCL pin as output low
        DelayUs(20);           //延时
    }
    MPU_SDA_DR = 1;
    return dat;
}
//**************************************
//I2C停止运行
//
//**************************************
void I2C_Stop(void) {
    MPU_SDA = 0;//set SDA pin as output low
    MPU_SCL = 1;//set SCL pin as output high
    DelayUs(20);
    MPU_SCL = 0;//set SCL pin as output high
    DelayUs(20);
}

//**************************************
//向I2C设备写入一个字节数据
//**************************************
void Single_WriteI2C(u8 REG_Address,u8 REG_data)
{
    I2C_Start();                  //起始信号
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号
    I2C_SendByte(REG_Address);    //内部寄存器地址，
    I2C_SendByte(REG_data);       //内部寄存器数据，
    I2C_Stop();                   //发送停止信号
}
//**************************************
//从I2C设备读取一个字节数据
//**************************************
u8 Single_ReadI2C(u8 REG_Address)
{
	u8 REG_data;
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress);    //发送设备地址+写信号
	I2C_SendByte(REG_Address);     //发送存储单元地址，从0开始	
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress|0x01);  //发送设备地址+读信号
	REG_data=I2C_RecvByte();       //读出寄存器数据
	I2C_SendACK(1);                //接收应答信号
	I2C_Stop();                    //停止信号
	return REG_data;
}
/**
  * @brief  Mpu6050int program.
  * @param  None
  * @retval None
  */

void InitMPU6050(void)
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}
//**************************************
//合成数据
//**************************************
u16 GetData(u8 REG_Address)
{
	u8 H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return (H<<8)|L;   //合成数据
}
