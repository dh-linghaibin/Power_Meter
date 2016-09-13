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
#include "Ads1220.h"
#include "Delay.h"

#define SPI_IN_DATA     PB_IDR_IDR2
#define SPI_DRDY        !(PB_IDR_IDR3)
#define SPI_CLK         PB_ODR_ODR5
#define SPI_OUT_DATA    PB_ODR_ODR1    
#define SPI_CS          PB_ODR_ODR4

#define OUTP 1      //��ʾGPIO�ӿڷ���Ϊ���  
#define INP 0       //��ʾGPIO�ӿڷ���Ϊ����  
/**********************************************��������***************************************************** 
* ��������: void void(Ads1220Init) 
* �������: Ads1220Init 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/31
************************************************************************************************************/ 
void Ads1220Init(void) { 
    PB_DDR_DDR1 = 1;
    PB_CR1_C11 = 1;
    PB_CR2_C21 = 1;
    
    PB_DDR_DDR2 = 0;
    PB_CR1_C12 = 0;
    PB_CR2_C22 = 0;
    
    PB_DDR_DDR3 = 0;
    PB_CR1_C13 = 0;
    PB_CR2_C23 = 0;
    
    PB_DDR_DDR4 = 1;
    PB_CR1_C14 = 1;
    PB_CR2_C24 = 1;
    
    PB_DDR_DDR5 = 1;
    PB_CR1_C15 = 1;
    PB_CR2_C25 = 1;
    
    ADS1220_Init();
}
/**********************************************��������***************************************************** 
* ��������: u8 Ads1220SpiSend(u8 dat) 
* �������: u8 dat 
* ���ز���: u8  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/8/31
************************************************************************************************************/ 
u8 Ads1220SpiSend(u8 dat) { 

    return 0x00;
}
/* 
���豸ʹ�� 
enable��Ϊ1ʱ��ʹ���ź���Ч��SS�͵�ƽ 
Ϊ0ʱ��ʹ���ź���Ч��SS�ߵ�ƽ 
*/  
void ss_enable(int enable)  
{  
    if (enable)  
        SPI_CS = 0;     //SS�͵�ƽ�����豸ʹ����Ч  
    else  
        SPI_CS = 1;     //SS�ߵ�ƽ�����豸ʹ����Ч  
}  
 /* SPI�ֽ�д */  
void spi_write_byte(unsigned char b)  
{  
    int i;  
    for (i=0; i < 8; i++) {//(i=7; i>=0; i--) {  
        SPI_CLK = 0; 
//        if(b&(1<<i) > 0) {
//            SPI_OUT_DATA = 1;
//        } else {
//            SPI_OUT_DATA = 0;
//        }
        if(b&0x80) {
            SPI_OUT_DATA=1;
        } else {   
            SPI_OUT_DATA=0; 
        }
        b<<= 1;
        //SPI_OUT_DATA = b&(1<<i);   //�Ӹ�λ7����λ0���д���д��  
        DelayUs(20);       //��ʱ  
        SPI_CLK = 1;    // CPHA=1����ʱ�ӵĵ�һ�������ز���  
        DelayUs(20);   
    }  
}  
/* SPI�ֽڶ� */  
unsigned char spi_read_byte()  
{  
    int i;  
    unsigned char r = 0;  
    for (i=0; i<8; i++) {  
        SPI_CLK = 0;  
        DelayUs(20);       //��ʱ  
        SPI_CLK = 1;    // CPHA=1����ʱ�ӵĵ�һ�������ز���  
        //r = (r <<1) | SPI_IN_DATA;   //�Ӹ�λ7����λ0���д��ж���
        r <<= 1;
        if(SPI_IN_DATA == 1) {
            r |=0x01;
        } else {
            r<<=1;
        }
        DelayUs(20);  
    }
    return r;
}  
/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : Sends a byte through the SPI interface and return the byte
*                  received from the SPI bus.
* Input          : byte : byte to send.
* Output         : None
* Return         : The value of the received byte.
*******************************************************************************/
u8 SPI_SendByte2(u8 byte)
{
    /* Loop while DR register in not emplty */
    //while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /* Send byte through the SPI1 peripheral */
    //SPI_I2S_SendData(SPI1, byte);
    if(byte == 0) {
    
    } else { 
        spi_write_byte(byte);
    }
    /* Wait to receive a byte */
    //while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /* Return the byte read from the SPI bus */
    return spi_read_byte();//SPI_I2S_ReceiveData(SPI1);
}
u8 SPI_SendByte(u8 dat)
{
    u8 i,temp;
    temp=0;
    SPI_CLK=0;
    DelayUs(10);;
    for(i=0;i<8;i++) {
        if(dat & 0x80) {
            SPI_OUT_DATA=1;
        }
        else {
            SPI_OUT_DATA=0;
        }
        DelayUs(15);
        dat<<=1;
        SPI_CLK=1;
        DelayUs(10);
        temp<<=1;
        if(SPI_IN_DATA) {
            temp++;
        }
        SPI_CLK=0;
        DelayUs(15);
    }
    return temp;
}

//-----------------------------------------------------------------//
//	��    �ܣ�ADS1220 д����
//	��ڲ���: /
//	���ڲ���: /
//	ȫ�ֱ���: /
//	��    ע: ��ADS1220�е�ַΪregaddr�ļĴ���д��һ���ֽ�databyte
//-----------------------------------------------------------------//

void ADS1220WREG(unsigned char regaddr,unsigned char databyte)
{
    //ADS_CS_LOW();
    SPI_CS = 0;
	while(SPI_DRDY);//��ADS1220_DRDYΪ��ʱ����д�Ĵ���
	//��Ĵ���д�����ݵ�ַ
    SPI_SendByte(ADS1220_WREG_CMD | (regaddr & 0xF));
    //д�����ݵĸ���n-1
    SPI_SendByte(0);
    //��regaddr��ַָ��ļĴ���д������databyte
  	DelayUs(5);
    SPI_SendByte(databyte);
	SPI_CS = 1;
}

//-----------------------------------------------------------------//
//	��    �ܣ�ADS1220 ���Ĵ�������
//	��ڲ���: /
//	���ڲ���: /
//	ȫ�ֱ���: /
//	��    ע: ��ADS1220�е�ַΪregaddr�ļĴ�������һ���ֽ�databyte
//-----------------------------------------------------------------//

unsigned char ADS1220RREG(unsigned char regaddr)
{
    //��ADS1220�е�ַΪregaddr�ļĴ�������һ���ֽ�
    unsigned char r=0, len =0;
    SPI_CS = 0;
    //	DS_delay_us(10);
    while(SPI_DRDY);//��ADS1220_DRDYΪ��ʱ����д�Ĵ���
    //д���ַ

    SPI_SendByte(ADS1220_RREG_CMD | ((regaddr<<2|(len&0x0)) & 0xF));
    //д���ȡ���ݵĸ���n-1
    // SPI_SendByte(0);
    DelayUs(10);  //min=50*(1/fCLKIN)=50*(1/7.68MHZ)=6500ns;max=whatever
    //����regaddr��ַָ��ļĴ���������
    r=SPI_SendByte(0);
    SPI_CS = 1;

    return r;//��������
}

//-----------------------------------------------------------------//
//	��    �ܣ�ADS1220��ʼ���ӳ���
//	��ڲ���: /
//	���ڲ���: /
//	ȫ�ֱ���: /
//	��    ע: /
//-----------------------------------------------------------------//
void ADS1220_Init(void)
{ 

	unsigned char config[4];
	//config[0] = ADS1220_MUX_AIN0_AIN1 + ADS1220_GAIN_16 + ADS1220_USE_PGA;
	config[0] = ADS1220_MUX_AIN1_AIN0 + ADS1220_GAIN_128 + ADS1220_USE_PGA;
	config[1] = ADS1220_DATA_RATE_1000SPS + ADS1220_OP_MODE_NORMAL + ADS1220_CONVERSION_CONTINUOUS + ADS1220_TEMP_SENSOR_OFF + ADS1220_BURN_OUT_CURRENT_OFF;
	config[2] = ADS1220_FIR_50_60 + ADS1220_VREF_EXT_REF0_PINS + ADS1220_LOW_SIDE_POWER_OPEN + ADS1220_IDAC_CURRENT_500_UA;
	config[3] = ADS1220_IDAC1_AIN2 + ADS1220_IDAC2_AIN3 + ADS1220_DRDY_ON_DRDY_ONLY;
    
	SPI_CS = 0;
	DelayUs(1000);

	SPI_SendByte(ADS1220_RESET_CMD);
	DelayMs(10);
	while(SPI_DRDY);                                //��ADS1220_DRDYΪ��ʱ����д�Ĵ���
	SPI_SendByte(ADS1220_START_CMD);                 //ͬ������
	SPI_SendByte(ADS1220_START_CMD);               //ͬ������
	
	while(SPI_DRDY);
	SPI_SendByte(ADS1220_WREG_CMD | 3);//����д��4���Ĵ���
	SPI_SendByte(config[0]);
	SPI_SendByte(config[1]);//��λ��ǰ��ʹ���ڲ�У׼����ʹ�û���
	SPI_SendByte(config[2]);//�˿�����A2Ϊ����A3λ��
	SPI_SendByte(config[3]);                   //�Ŵ�������
	//SPI_SendByte(ADS1220_DRATE_2_5SPS);             //�ɼ��ٶ�����
	DelayUs(100);
    
	while(SPI_DRDY);                                //��ADS1220_DRDYΪ��ʱ����д�Ĵ���
//	SPI_SendByte(ADS1220_CMD_SELFCAL);              //ƫ�ƺ������Զ�У׼
    SPI_CS = 1;
	DelayMs(100);
	ADS1220RREG(0);
}


//-----------------------------------------------------------------//
//	��    �ܣ�
//	��ڲ���: /
//	���ڲ���: /
//	ȫ�ֱ���: /
//	��    ע:
//-----------------------------------------------------------------//
u8 xxx[10];
unsigned long ADS1220ReadData(void)  
{
    unsigned char i=0;
    unsigned long sum=0;
    unsigned long r=0;
    SPI_CS = 0;
    DelayUs(10); 
    
    SPI_SendByte(ADS1220_START_CMD);
    SPI_SendByte(ADS1220_START_CMD);
    SPI_SendByte(ADS1220_RDATA_CMD);
    
    while(SPI_DRDY);               //��ADS1220_DRDYΪ��ʱ����д�Ĵ��� 	
    DelayUs(1000);                  //min=50*(1/fCLKIN)=50*(1/7.68MHZ)=6500ns;max=whatever
    for(i=0;i<3;i++)
    {
        sum = sum << 8;
        r = SPI_SendByte(0);  
        xxx[i] = r;
        sum |= r;
        //DelayUs(1000);
    }
    //	SPI_SendByte(ADS1220_POWERDOWN_CMD);
    SPI_CS = 1;	
    //DelayMs(100);    
    return sum;
}


