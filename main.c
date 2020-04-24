#include "stm32f10x.h" 
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"


GPIO_InitTypeDef port;
SPI_InitTypeDef spi;
uint8_t data;
uint8_t sendData;
uint16_t counter;
uint16_t Data;

 
 
 
void initAll()
{
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	
 
    SPI_StructInit(&spi);
    spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi.SPI_Mode = SPI_Mode_Master;
    spi.SPI_DataSize = SPI_DataSize_8b;
    spi.SPI_CPOL = SPI_CPOL_Low;
    spi.SPI_CPHA = SPI_CPHA_2Edge;
    spi.SPI_NSS = SPI_NSS_Soft;
    spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    spi.SPI_FirstBit = SPI_FirstBit_MSB;
    spi.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &spi);
 
    GPIO_StructInit(&port);
    port.GPIO_Mode = GPIO_Mode_AF_PP;
    port.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    port.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &port);
 
    port.GPIO_Mode = GPIO_Mode_IPD;
    port.GPIO_Pin = GPIO_Pin_0;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &port);
/////////////////////////////////////////////////////qqqqqqq
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    SPI_StructInit(&spi);
    spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi.SPI_Mode = SPI_Mode_Slave;
    spi.SPI_DataSize = SPI_DataSize_8b;
    spi.SPI_CPOL = SPI_CPOL_Low;
    spi.SPI_CPHA = SPI_CPHA_2Edge;
    spi.SPI_NSS = SPI_NSS_Soft;
    spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    spi.SPI_FirstBit = SPI_FirstBit_MSB;
    spi.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &spi);
 
    GPIO_StructInit(&port);
    port.GPIO_Mode = GPIO_Mode_AF_PP;
    port.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    port.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &port);
		
		GPIO_StructInit(&port);
		port.GPIO_Mode = GPIO_Mode_AIN;
		port.GPIO_Pin = GPIO_Pin_12;
		port.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &port);
		
    GPIO_StructInit(&port); 
    port.GPIO_Mode = GPIO_Mode_Out_PP;
    port.GPIO_Pin = GPIO_Pin_13;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &port);
}
 
 
 
int main()
{
	   __enable_irq();	
    initAll();
    SPI_Cmd(SPI1, ENABLE);
	  char sendData = 'H';
    SPI_I2S_SendData(SPI1, (uint8_t) sendData);	
	  /////f 
    initAll();
	  SPI_Cmd(SPI1, ENABLE);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
    while(1)
		{
       data = SPI_I2S_ReceiveData(SPI1);
			 if (data == 'H')
			 {
				 GPIO_ResetBits(GPIOC, GPIO_Pin_13);
				 for(int i = 0; i < 160000; ++i){}
				 GPIO_SetBits(GPIOC, GPIO_Pin_13);
				 for(int i = 0; i < 160000; ++i){}
				 }
			 //for(int i = 0; i < 160000; --i){}
			 }
}
