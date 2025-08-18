


#include "main.h"
#include "stm32f4xx_hal.h"
#include "can_bms.h"
#include "init.h"
#include "crc32.h"

//#include "cstring"

//extern const uint32_t CYCLE_TIME= 20;


extern "C" {
    void SystemClock_Config(void);
    void MX_GPIO_Init(void);
    void MX_I2S3_Init(void);
    void MX_SPI1_Init(void);
    void MX_CAN2_Init(void);
    void MX_TIM1_Init(void);
}

/* Private variables ---------------------------------------------------------*/



/* USER CODE BEGIN PV */
uint32_t crc32_array[TABLE_SIZE] = {0};

const uint8_t* p_dataRx;
uint32_t crc32_sum;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

void MX_USB_HOST_Process(void);

int val_1;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim -> Instance == TIM1){
		 //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

		trm_HVESSC1_PGN_6912.SetHS_HiUBusCnctCmd_Rx1(2);
		trm_HVESSC1_PGN_6912.SetHS_PwrDwnCmd_Rx1(3);
		trm_HVESSC1_PGN_6912.SetHS_HiUBusHiSideRestrCnctReq_Rx1(4);
		trm_HVESSC1_PGN_6912.SetHS_CellBalnCmd_Rx1(2);

		trm_HVESSC1_PGN_6912.fillTxData();				// data is calculated, variables are not changing
		p_dataRx = trm_HVESSC1_PGN_6912.getTxData();		// pointer to data of trm_HVESSC1_PGN_6912
		crc32_sum = crc32_calc(p_dataRx, crc32_array);		// crc32 calculation



		 trm_can2.trm_can_msg_j1939(&trm_HVESSC1_PGN_6912_SHM, CYCLE_TIME);		// message
		 trm_can2.trm_can_msg_j1939(&trm_HVESSC1_PGN_6912, CYCLE_TIME);			// shm




	}
}

/* USER CODE BEGIN PFP */
int main() {
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();

    MX_I2S3_Init();
    MX_SPI1_Init();
    MX_CAN2_Init();
     MX_TIM1_Init();


    __HAL_RCC_GPIOD_CLK_ENABLE();

    HAL_TIM_Base_Start_IT(&htim1);
    HAL_CAN_Start(&hcan2);

      crc32k9_init_table_ram(crc32_array, CRC32K9_POLYNOMIAL);

    while (1) {
      /*  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
        HAL_Delay(100);  // 500 ms
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
        HAL_Delay(100);  // 500 ms
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
        HAL_Delay(100);  // 500 ms
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
        HAL_Delay(100);  // 500 ms*/

    }
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


  /* USER CODE BEGIN SPI1_Init 2
val_1++;

		CAN_TxHeaderTypeDef TxHeader;
		        uint8_t TxData[8] = {0x01, 0x02, 0x03, 0x04, 0, 0, 0, 0};
		        uint32_t TxMailbox;

		        TxHeader.DLC = 4;
		        TxHeader.IDE = CAN_ID_STD;
		        TxHeader.StdId = 0x321;
		        TxHeader.RTR = CAN_RTR_DATA;

		        if (HAL_CAN_AddTxMessage(&hcan2, &TxHeader, TxData, &TxMailbox) != HAL_OK)
		        {
		            // Falls alle 3 Mailboxen voll sind oder Fehler
		        }
  /* USER CODE END SPI1_Init 2 */

/*void trm_can_msg(can_msg_j1939 &object, uint32_t cyclusTime);

void trm_can_msg(can_msg_j1939 &object,  uint32_t cyclusTime){

	static uint32_t trm_cnt;
	trm_cnt += CYCLE_TIME;

	if (trm_cnt == object.getTransmitRate())
	{
		if (HAL_CAN_AddTxMessage(&hcan2, object.getTxHeader(), object.getTxData(), object.getTxMailbox()) != HAL_OK)
			 {
					            // Falls alle 3 Mailboxen voll sind oder Fehler
			 }

		trm_cnt = 0;}

	}*/

/*
 * void trm_can_msg_j1939(HVESSC1_PGN_6912_Rx &object, uint32_t cyclusTime);

void trm_can_msg_j1939(HVESSC1_PGN_6912_Rx &object, uint32_t cyclusTime){

	static uint32_t trm_cnt;
	trm_cnt += CYCLE_TIME;

		if (trm_cnt == object.getTransmitRate())
		{
			object.fillTxData();
			if (HAL_CAN_AddTxMessage(&hcan2, object.getTxHeader(), object.getTxData(), object.getTxMailbox()) != HAL_OK)
				 {
						            // Falls alle 3 Mailboxen voll sind oder Fehler
				 }
			trm_cnt = 0;}

		}
 *
 * */










