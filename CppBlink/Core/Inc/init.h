/*
 * init.h
 *
 *  Created on: Aug 5, 2025
 *      Author: malya
 */

#ifndef INC_INIT_H_
#define INC_INIT_H_


#ifdef __cplusplus
extern "C" {
#endif

void SystemClock_Config(void);
void MX_I2C1_Init(void);
void MX_I2S3_Init(void);
void MX_SPI1_Init(void);
void MX_CAN2_Init(void);
 void MX_TIM1_Init(void);

#ifdef __cplusplus
}
#endif




#endif /* INC_INIT_H_ */



extern CAN_HandleTypeDef hcan2;
extern TIM_HandleTypeDef htim1;

