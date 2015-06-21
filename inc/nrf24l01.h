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

/*********************
			nRF24L01 Define
			     **************************/
/* nRF24L01 Command define */
#define R_REG                0x00
#define W_REG                0x20
#define R_RX_PAYLOAD         0x61
#define W_TX_PAYLOAD         0xA0
#define FLUSH_TX             0xE1
#define FLUSH_RX             0xE0
#define REUSE_TX_PL          0xE3
#define R_RX_PL_WID          0x60
#define W_ACK_PAYLOAD        0xA8
#define W_TX_PAYLOAD_NOACK   0xB0
#define nRF24L01_NOP         0xFF

/* nRF24L01 Register address*/
#define CONFIG_REG_ADDR      0x00
#define EN_AA_REG_ADDR       0x01
#define EN_RX_REG_ADDR       0x02
#define SETUP_AW_REG_ADDR    0x03
#define SETUP_RETR_REG_ADDR  0x04
#define RF_CH_REG_ADDR       0x05
#define RF_SETUP_REG_ADDR    0x06
#define STATUS_REG_ADDR      0x07
#define OBSERVE_TX_REG_ADDR  0x08
#define RPD_REG_ADDR         0x09
#define RX_ADDR_P0_REG_ADDR  0x0A
#define RX_ADDR_P1_REG_ADDR  0x0B
#define RX_ADDR_P2_REG_ADDR  0x0C
#define RX_ADDR_P3_REG_ADDR  0x0D
#define RX_ADDR_P4_REG_ADDR  0x0E
#define RX_ADDR_P5_REG_ADDR  0x0F
#define TX_ADDR_REG_ADDR     0x10
#define RX_PW_P0_REG_ADDR    0x11
#define RX_PW_P1_REG_ADDR    0x12
#define RX_PW_P2_REG_ADDR    0x13
#define RX_PW_P3_REG_ADDR    0x14
#define RX_PW_P4_REG_ADDR    0x15
#define RX_PW_P5_REG_ADDR    0x16
#define FIFO_STATUS_REG_ADDR 0x17
#define DYNPD_REG_ADDR       0x1C
#define FEATURE_REG_ADDR     0x1D

/* nRF24L01 Register bits */
/* CONFIG 基本设置*/
#define MASK_RX_DR           0x40
#define MASK_TX_DS           0x20
#define MASK_MAX_RT          0x10
#define EN_CRC               0x08
#define CRCO                 0x04
#define PWR_UP               0x02
#define PRIM_RX              0x01

/* EN_AA 数据通道使能*/
#define ENAA_P5              0x20
#define ENAA_P4              0x10
#define ENAA_P3              0x08
#define ENAA_P2              0x04
#define ENAA_P1              0x02
#define ENAA_P0              0x01
#define ENAA_ALL             0x00

/* EN_RXADDR 地址使能*/
#define EN_RXADDR_P5         0x20
#define EN_RXADDR_P4         0x10
#define EN_RXADDR_P3         0x08
#define EN_RXADDR_P2         0x04
#define EN_RXADDR_P1         0x02
#define EN_RXADDR_P0         0x01
#define EN_RXADDR_ALL        0x00

/* SETUP_AW 地址宽度*/
#define AW_3Bytes            0x01
#define AW_4Bytes            0x02
#define AW_5Bytes            0x03

/* SETUP_RETR */
/* 自动重传延时 */
#define ARD_250us            0x00
#define ARD_500us            0x10
#define ARD_750us            0x20
#define ARD_1000us           0x30
#define ARD_1250us           0x40
#define ARD_1500us           0x50
#define ARD_1750us           0x60
#define ARD_2000us           0x70
#define ARD_2250us           0x80
#define ARD_2500us           0x90
#define ARD_2750us           0xA0
#define ARD_3000us           0xB0
#define ARD_3250us           0xC0
#define ARD_3500us           0xD0
#define ARD_3750us           0xE0
#define ARD_4000us           0xF0
/* 自动重传计数 */
#define ARC_DISABLE          0x00
#define ARC_1                0x01
#define ARC_2                0x02
#define ARC_3                0x03
#define ARC_4                0x04
#define ARC_5                0x05
#define ARC_6                0x06
#define ARC_7                0x07
#define ARC_8                0x08
#define ARC_9                0x09
#define ARC_10               0x0A
#define ARC_11               0x0B
#define ARC_12               0x0C
#define ARC_13               0x0D
#define ARC_14               0x0E
#define ARC_15               0x0F

/* RF_SETUP 射频设置*/
#define CONT_WAVE            0x80
#define RF_DR_LOW            0x40
#define PLL_LOCK             0x20
#define RF_DR_HIGH           0x10
#define RF_PWR_0             0x0C
#define RF_PWR_6             0x08
#define RF_PWR_12            0x04
#define RF_PWR_18            0x00

/* STATUS 状态设置 */
#define RX_P_MASK            0x0E

#define RX_DR                0x40
#define TX_DS                0x20
#define MAX_RT               0x10
#define RX_P_E               0x0E
#define RX_P_NO              0x0C
#define RX_P_5               0x0A
#define RX_P_4               0x08
#define RX_P_3               0x06
#define RX_P_2               0x04
#define RX_P_1               0x02
#define RX_P_0               0x00
#define TX_FULL              0x01



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

