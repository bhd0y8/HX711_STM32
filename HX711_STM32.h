/**
  ******************************************************************************
  * @file           : HX711_STM32.h
  * @brief          : STM32F103_LoadCell_&_HX711_Amplifier .
  ******************************************************************************
  ******************************************************************************
  */
	
	#ifndef HX711_STM32_H_
	#define HX711_STM32_H_
	
	#ifdef __cplusplus
	extern "C"{
	#endif
	
		/*Includes--------------------------------------------------------------------*/
	#include "stm32f1xx_hal.h"
	#include "gpio.h"
	
	/*********--------------------------------------------------------------------*/
	
	#define PD_SCK_SET_HIGH     HAL_GPIO_WritePin(_HX711_SCK_GPIO, _HX711_SCK_PIN, 1)
	#define PD_SCK_SET_LOW      HAL_GPIO_WritePin(_HX711_SCK_GPIO, _HX711_SCK_PIN, 0)
	#define DOUT_GET            HAL_GPIO_ReadPin(_HX711_DI_GPIO,  _HX711_DI_PIN)
	
	/*Private functions----------------------------------------------------------*/
	
	void 	        HX711_power_up(void);
	long long int   ReadHX(void);
	int32_t		HX711_valueAve(uint16_t sample);
	void 		Delay_us(uint32_t us);
	void            HX711_power_down(void);
	void            HX711_is_ready(void);
	void            HX711_set_gain(uint32_t gain);
	/*----------------------------------------------------------------------------*/
		
		
	#ifdef __cplusplus
}
#endif
	
	#endif
