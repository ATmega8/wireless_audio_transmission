#include "main.h"

void nRF24L01_InterfaceInit(void);

void nRF24L01_RxDMAInit(uint8_t* pdata, uint8_t len);
void nRF24L01_TxDMAInit(uint8_t* pdata, uint8_t len);

uint8_t nRF24L01_ReadRegister(uint8_t cmd, uint8_t* pdata, uint8_t len);
uint8_t nRF24L01_WriteRegister(uint8_t cmd, uint8_t* pdata, uint8_t len);

nRF24L01_StatusTypeDef nRF24L01_Test(void);

void nRF24L01_Delay(uint32_t timing);

void nRF24L01_InterfaceInit(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(NRF24L01_SPI_GPIO_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(NRF24L01_SPI_CLOCK, ENABLE);

	/*SPI DMA Clock Configure*/
	RCC_AHB1PeriphClockCmd(SPIx_DMA_STREAM_CLK, ENABLE);

    GPIO_PinAFConfig(NRF24L01_SPI_GPIO, NRF24L01_GPIO_AF_MOSI, NRF24L01_SPI_GPIO_AF);
    GPIO_PinAFConfig(NRF24L01_SPI_GPIO, NRF24L01_GPIO_AF_MISO, NRF24L01_SPI_GPIO_AF);
    GPIO_PinAFConfig(NRF24L01_SPI_GPIO, NRF24L01_GPIO_AF_SCK, NRF24L01_SPI_GPIO_AF);
    //GPIO_PinAFConfig(NRF24L01_SPI_GPIO, NRF24L01_GPIO_AF_CSN, NRF24L01_SPI_GPIO_AF);
 
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
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin =  NRF24L01_GPIO_CSN;
    GPIO_Init(NRF24L01_SPI_GPIO, &GPIO_InitStructure);
 
    /* NRF24L01  CE pin configuration */
    GPIO_InitStructure.GPIO_Pin =  NRF24L01_GPIO_CE;
    GPIO_Init(NRF24L01_SPI_GPIO, &GPIO_InitStructure);
 
    /* NRF24L01  IRQ pin configuration */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Pin =  NRF24L01_GPIO_IRQ;
    GPIO_Init(NRF24L01_SPI_GPIO, &GPIO_InitStructure);
    
   
    /* SPI configuration -------------------------------------------------------*/
    SPI_I2S_DeInit(NRF24L01_SPI);
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(NRF24L01_SPI, &SPI_InitStructure);
	SPI_Cmd(NRF24L01_SPI, ENABLE);

	/*GPIO Init Level*/
	GPIO_SetBits(NRF24L01_SPI_GPIO, NRF24L01_GPIO_CSN);
	GPIO_ResetBits(NRF24L01_SPI_GPIO, NRF24L01_GPIO_CE);
	//SPI_SSOutputCmd(NRF24L01_SPI, ENABLE);
}

void nRF24L01_TxDMAInit(uint8_t* pdata, uint8_t len)
{
	DMA_InitTypeDef DMA_InitStructure;

	/* Deinitialize DMA Streams */
	DMA_DeInit(SPIx_TX_DMA_STREAM);

	/* Configure DMA Initialization Structure */
	DMA_InitStructure.DMA_BufferSize = len;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI1->DR)) ;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	/* Configure TX DMA */
	DMA_InitStructure.DMA_Channel = SPIx_TX_DMA_CHANNEL ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
	DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)pdata;
	DMA_Init(SPIx_TX_DMA_STREAM, &DMA_InitStructure);

}

void nRF24L01_RxDMAInit(uint8_t* pdata, uint8_t len)
{
	DMA_InitTypeDef DMA_InitStructure;

	DMA_DeInit(SPIx_RX_DMA_STREAM);
  
	/* Configure DMA Initialization Structure */
	DMA_InitStructure.DMA_BufferSize = len;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI1->DR)) ;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	/* Configure RX DMA */
	DMA_InitStructure.DMA_Channel = SPIx_RX_DMA_CHANNEL ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
	DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)pdata; 
	DMA_Init(SPIx_RX_DMA_STREAM, &DMA_InitStructure);
}

uint8_t nRF24L01_ReadRegister(uint8_t cmd, uint8_t* pdata, uint8_t len)
{
	uint8_t i;
	uint8_t txbuf[34] = {0xFF};
	uint8_t rxbuf[34] = {0x00};

	txbuf[0] = cmd;

    SPI_I2S_DMACmd(NRF24L01_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
	SPI_I2S_DMACmd(NRF24L01_SPI, SPI_I2S_DMAReq_Rx, ENABLE);

	GPIO_ResetBits(NRF24L01_SPI_GPIO, NRF24L01_GPIO_CSN);
	nRF24L01_Delay(5);

	nRF24L01_TxDMAInit((uint8_t*)&txbuf, len+2);
	nRF24L01_RxDMAInit((uint8_t*)&rxbuf, len+2);

	DMA_Cmd(SPIx_TX_DMA_STREAM, ENABLE);
	DMA_Cmd(SPIx_RX_DMA_STREAM, ENABLE);

	while (DMA_GetFlagStatus(SPIx_TX_DMA_STREAM,SPIx_TX_DMA_TCIF)==RESET);
    while (DMA_GetFlagStatus(SPIx_RX_DMA_STREAM,SPIx_RX_DMA_TCIF)==RESET);
  
    /* Clear DMA Transfer Complete Flags */
    DMA_ClearFlag(SPIx_TX_DMA_STREAM,SPIx_TX_DMA_TCIF);
    DMA_ClearFlag(SPIx_RX_DMA_STREAM,SPIx_RX_DMA_TCIF);

	DMA_Cmd(SPIx_RX_DMA_STREAM, DISABLE);
	DMA_Cmd(SPIx_TX_DMA_STREAM, DISABLE);

    SPI_I2S_DMACmd(NRF24L01_SPI, SPI_I2S_DMAReq_Tx, DISABLE);
	SPI_I2S_DMACmd(NRF24L01_SPI, SPI_I2S_DMAReq_Rx, DISABLE);

	nRF24L01_Delay(5);
	GPIO_SetBits(NRF24L01_SPI_GPIO, NRF24L01_GPIO_CSN);

	for(i = 0; i < len; i++)
		*(pdata+i) = *(rxbuf+i+2);

	return *(rxbuf+1); 
}

uint8_t nRF24L01_WriteRegister(uint8_t cmd, uint8_t* pdata, uint8_t len)
{
	uint8_t i, status;
	uint8_t txbuf[33] = {0xFF};


	for(i = 0; i < len; i++)
		txbuf[i+1] = *(pdata+i);

	txbuf[0] = cmd;

    SPI_I2S_DMACmd(NRF24L01_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
	SPI_I2S_DMACmd(NRF24L01_SPI, SPI_I2S_DMAReq_Rx, ENABLE);

	GPIO_ResetBits(NRF24L01_SPI_GPIO, NRF24L01_GPIO_CSN);
	nRF24L01_Delay(5);


	nRF24L01_TxDMAInit((uint8_t*)&txbuf, len+1);
	nRF24L01_RxDMAInit(&status, 1);

	DMA_Cmd(SPIx_TX_DMA_STREAM, ENABLE);
	DMA_Cmd(SPIx_RX_DMA_STREAM, ENABLE);

	while (DMA_GetFlagStatus(SPIx_TX_DMA_STREAM,SPIx_TX_DMA_TCIF)==RESET);
    while (DMA_GetFlagStatus(SPIx_RX_DMA_STREAM,SPIx_RX_DMA_TCIF)==RESET);
  
    /* Clear DMA Transfer Complete Flags */
    DMA_ClearFlag(SPIx_TX_DMA_STREAM, SPIx_TX_DMA_TCIF);
    DMA_ClearFlag(SPIx_RX_DMA_STREAM, SPIx_RX_DMA_TCIF);

	DMA_Cmd(SPIx_RX_DMA_STREAM, DISABLE);
	DMA_Cmd(SPIx_TX_DMA_STREAM, DISABLE);

    SPI_I2S_DMACmd(NRF24L01_SPI, SPI_I2S_DMAReq_Tx, DISABLE);
	SPI_I2S_DMACmd(NRF24L01_SPI, SPI_I2S_DMAReq_Rx, DISABLE);

	nRF24L01_Delay(5);
	GPIO_SetBits(NRF24L01_SPI_GPIO, NRF24L01_GPIO_CSN);

	return status;
}

nRF24L01_StatusTypeDef nRF24L01_Test(void)
{
	uint8_t writeBuf[5] = {0x34, 0x34, 0x34, 0x34, 0x34};
	uint8_t readBuf[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t status, i;

	status = nRF24L01_WriteRegister(0x2A, (uint8_t*)&writeBuf, 5);
	status = nRF24L01_ReadRegister(0x0A, (uint8_t*)&readBuf, 5);

	for(i = 0; i < 5; i++)
	{
		if(readBuf[i+1] != writeBuf[i])
			return NRF24L01_ERROR;
	}

	return NRF24L01_OK;

}

void nRF24L01_Delay(uint32_t timing)
{
	while( timing -- );
}

