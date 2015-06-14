#include "main.h"

void nRF24L01_InterfaceInit(void);
nRF24L01_StatusTypeDef nRF24L01_Test(void);

void nRF24L01_InterfaceInit(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(NRF24L01_SPI_GPIO_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(NRF24L01_SPI_CLOCK, ENABLE);

    GPIO_PinAFConfig(NRF24L01_SPI_GPIO, NRF24L01_GPIO_AF_MOSI, NRF24L01_SPI_GPIO_AF);
    GPIO_PinAFConfig(NRF24L01_SPI_GPIO, NRF24L01_GPIO_AF_MISO, NRF24L01_SPI_GPIO_AF);
    GPIO_PinAFConfig(NRF24L01_SPI_GPIO, NRF24L01_GPIO_AF_SCK, NRF24L01_SPI_GPIO_AF);
 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  
    /* NRF24L01 SCK pin configuration */
    GPIO_InitStructure.GPIO_Pin = NRF24L01_GPIO_SCK;
    GPIO_Init(NRF24L01_SPI_GPIO, &GPIO_InitStructure);
    
    /* NRF24L01  MOSI pin configuration */
    GPIO_InitStructure.GPIO_Pin =  NRF24L01_GPIO_MOSI;
    GPIO_Init(NRF24L01_SPI_GPIO, &GPIO_InitStructure);  
  
    /* NRF24L01  MISO pin configuration */
    GPIO_InitStructure.GPIO_Pin =  NRF24L01_GPIO_MISO;
    GPIO_Init(NRF24L01_SPI_GPIO, &GPIO_InitStructure);
 
    /* NRF24L01  CSN pin configuration */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin =  NRF24L01_GPIO_CSN;
    GPIO_Init(NRF24L01_SPI_GPIO, &GPIO_InitStructure);
 
    /* NRF24L01  CE pin configuration */
    GPIO_InitStructure.GPIO_Pin =  NRF24L01_GPIO_CE;
    GPIO_Init(NRF24L01_SPI_GPIO, &GPIO_InitStructure);
 
    /* NRF24L01  IRQ pin configuration */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Pin =  NRF24L01_GPIO_IRQ;
    GPIO_Init(NRF24L01_SPI_GPIO, &GPIO_InitStructure);
    
   
    /* SPI configuration -------------------------------------------------------*/
    SPI_I2S_DeInit(NRF24L01_SPI);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 15;
	SPI_Init(NRF24L01_SPI, &SPI_InitStructure);
}

