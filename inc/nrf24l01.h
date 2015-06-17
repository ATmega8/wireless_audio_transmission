#include <stdint.h>

#define NRF24L01_SPI            SPI1

#define NRF24L01_SPI_CLOCK      RCC_APB2Periph_SPI1
#define NRF24L01_SPI_GPIO_CLOCK RCC_AHB1Periph_GPIOA

#define NRF24L01_SPI_GPIO       GPIOA
#define NRF24L01_SPI_GPIO_AF    GPIO_AF_SPI1

#define NRF24L01_GPIO_AF_MOSI   GPIO_PinSource7
#define NRF24L01_GPIO_AF_MISO   GPIO_PinSource6
#define NRF24L01_GPIO_AF_CSN    GPIO_PinSource4
#define NRF24L01_GPIO_AF_SCK    GPIO_PinSource5

#define NRF24L01_GPIO_MOSI      GPIO_Pin_7
#define NRF24L01_GPIO_MISO      GPIO_Pin_6
#define NRF24L01_GPIO_CSN       GPIO_Pin_4
#define NRF24L01_GPIO_SCK       GPIO_Pin_5
#define NRF24L01_GPIO_CE        GPIO_Pin_8
#define NRF24L01_GPIO_IRQ       GPIO_Pin_9

/***************
           DMA Define
		           ******************/

#define SPIx_DMA_STREAM_CLK RCC_AHB1Periph_DMA2

#define SPIx_TX_DMA_STREAM  DMA2_Stream3
#define SPIx_RX_DMA_STREAM  DMA2_Stream2

#define SPIx_TX_DMA_CHANNEL DMA_Channel_3
#define SPIx_RX_DMA_CHANNEL DMA_Channel_3

#define SPIx_RX_DMA_TCIF DMA_FLAG_TCIF2
#define SPIx_TX_DMA_TCIF DMA_FLAG_TCIF3

typedef enum
{
	NRF24L01_OK,
	NRF24L01_ERROR
} nRF24L01_StatusTypeDef;

typedef enum
{
	NRF24L01_Transmission,
	NRF24L01_Receive
} nRf24L01_ModeTypeDef;

nRF24L01_StatusTypeDef nRF24L01_Init(void);
nRF24L01_StatusTypeDef nRF24L01_DeInit(void);

nRF24L01_StatusTypeDef nRF24L01_SendData(void);
nRF24L01_StatusTypeDef nRF24L01_ReceiveData(void);

void nRF24L01_InterfaceInit(void);
nRF24L01_StatusTypeDef nRF24L01_Test(void);

void nRF24L01_DMAConfig(void);

