#include <stdint.h>

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

void nRF24L01_DMAConfig(void);

