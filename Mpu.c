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
* ������ڣ�2016/9/10
* ���뻷����D:\iar\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "Mpu.h"
#include "Delay.h"

#define MPU_SCL         PC_ODR_ODR1
#define MPU_SDA         PC_ODR_ODR0
#define MPU_SDA_DR      PC_DDR_DDR0
#define MPU_SDA_IN      PC_IDR_IDR0

/**********************************************��������***************************************************** 
* ��������: void MpuInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/9/10
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
//I2C��ʼ�ź�
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
//I2C����Ӧ���ź�
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
//I2C����Ӧ���ź�
//��ڲ���:ack (0:ACK 1:NAK)
//**************************************
void I2C_SendACK(u8 ack)
{
    if (ack==1) {
        MPU_SDA = 1;//set SDA pin as output high
    } else {
        MPU_SDA = 0;//set SDA pin as output low
    }
    MPU_SCL = 1;//set SCL pin as output high
    DelayUs(20);//��ʱ
    MPU_SCL = 0;  //set SCL pin as output low
    DelayUs(20);//��ʱ
}

//**************************************
//��I2C���߷���һ���ֽ�����
//**************************************
void I2C_SendByte(u8 dat)
{
    u8 i;
    for (i=0; i<8; i++)         //8λ������
    {                  
        if (dat&0x80)
        {
            MPU_SDA = 1;//set SDA pin as output high
        }
        else
        {
            MPU_SDA = 0;//set SDA pin as output low
        }
        dat <<= 1;   //�Ƴ����ݵ����λ
        MPU_SCL = 1;//set SCL pin as output high
        DelayUs(20);
        MPU_SCL = 0;  //set SCL pin as output low
        DelayUs(20);
    }
    I2C_RecvACK();
}

//**************************************
//��I2C���߽���һ���ֽ�����
//**************************************
u8 I2C_RecvByte(void) {
    u8 i;
    u8 dat = 0;
    MPU_SDA = 0;//set SDA pin as output high 
    //ʹ���ڲ�����,׼����ȡ����,
    MPU_SDA_DR = 0; //set sda as input with pull up
    for (i=0; i<8; i++) {//8λ������
        dat <<= 1;
        MPU_SCL = 1;//set SCL pin as output high
        DelayUs(20);            //��ʱ
        if(MPU_SDA_IN) {         
            dat|=0x01;
        } else {
            dat|=0;
        }
        MPU_SCL = 0;  //set SCL pin as output low
        DelayUs(20);           //��ʱ
    }
    MPU_SDA_DR = 1;
    return dat;
}
//**************************************
//I2Cֹͣ����
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
//��I2C�豸д��һ���ֽ�����
//**************************************
void Single_WriteI2C(u8 REG_Address,u8 REG_data)
{
    I2C_Start();                  //��ʼ�ź�
    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    I2C_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
    I2C_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    I2C_Stop();                   //����ֹͣ�ź�
}
//**************************************
//��I2C�豸��ȡһ���ֽ�����
//**************************************
u8 Single_ReadI2C(u8 REG_Address)
{
	u8 REG_data;
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	I2C_SendByte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ	
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress|0x01);  //�����豸��ַ+���ź�
	REG_data=I2C_RecvByte();       //�����Ĵ�������
	I2C_SendACK(1);                //����Ӧ���ź�
	I2C_Stop();                    //ֹͣ�ź�
	return REG_data;
}
/**
  * @brief  Mpu6050int program.
  * @param  None
  * @retval None
  */

void InitMPU6050(void)
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//�������״̬
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}
//**************************************
//�ϳ�����
//**************************************
u16 GetData(u8 REG_Address)
{
	u8 H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return (H<<8)|L;   //�ϳ�����
}
