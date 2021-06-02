/**
  ******************************************************************************
  * @file           : HX711_STM32.c
  * @brief          : STM32F103_LoadCell_&_HX711_Amplifier .
  */
	
	/*Includes--------------------------------------------------------------------*/
	#include "HX711_STM32.h"
	#include "HX711_STM32_Config.h"

	#if (_HX711_USE_FREERTOS == 1)
	#include "cmsis_os.h"
	#define HX711_delay(x)    osDelay(x)
	#else
	#define HX711_delay(x)    HAL_Delay(x)
	#endif
	uint8_t GAIN=0;		                // amplification factor

	/*********--------------------------------------------------------------------*/


/*Private functions----------------------------------------------------------*/
	/**
	*@brief: *** Written according to the HX711_datasheet ***
	
					 Delay_us()        function is for making a delay with a microsecond accuracy.
						- Registers are used.
						- Timer 3
						- ///Testing/// : working test
						
					 ReadHX()					 function is for reading data(s).
					  - Data is read in two steps, 8-bit and 16-bit.
						
					 HX711_valueAve()  function is for averaging data that has been read.
					 
	
	*@retval: ret | ave / sample
	*/
	
//#############################################################################################
void Delay_us(uint32_t us){

	//////////////////////
	//////  Testing //////
	//////////////////////
//	clear();
//	print("Du");
	
	
	TIM3->CNT = 0;
while(	TIM3->CNT <us);

}

//#############################################################################################
void HX711_set_gain(uint32_t gain) {
	switch (gain) {
		case 128:		// ch A, gain_factor 128
			GAIN = 1;
			break;
		case 64:		// ch A, gain_factor 64
			GAIN = 3;
			break;
		case 32:		// ch B, gain_factor 32
			GAIN = 2;
			break;
	}

}
//#############################################################################################
void HX711_is_ready(void) {
	PD_SCK_SET_LOW;      //Power up_PD_SCK
	Delay_us(1);                                  
	while(DOUT_GET);  //DOUT
	Delay_us(1);
}
//#############################################################################################
long long int ReadHX(void){

		long long int ret = 0;
		int8_t myMSB = 0;
		int8_t myLSB = 0;
		int8_t myGB  = 0;
	
	
	for(int i=0; i < 8 ;i++){
		PD_SCK_SET_HIGH;
		Delay_us(1);
		PD_SCK_SET_LOW;
			
		myMSB <<=1;
			if(DOUT_GET)
				myMSB++;
				Delay_us(1);
		}
	
		
	for(int i=0; i < 16 ;i++){
		PD_SCK_SET_HIGH;
		Delay_us(1);
		PD_SCK_SET_LOW;
			
		myLSB <<=1;
			if(DOUT_GET)
				myLSB++;
				Delay_us(1);
		}
				PD_SCK_SET_HIGH; //Power down
		
ret += myMSB;
ret <<= 16;
ret += myLSB;
		
		for (int i = 0; i < GAIN; i++) {
		PD_SCK_SET_HIGH;
		Delay_us(1);
		PD_SCK_SET_LOW;
			
			myGB <<=1;
			if(DOUT_GET)
				myGB++;
				Delay_us(1);
		}
	ret <<= GAIN;
  ret += myGB;

		return ret;
	}
//#############################################################################################
	void HX711_power_down(void)
{
			PD_SCK_SET_LOW;
			PD_SCK_SET_HIGH;
	
	Delay_us(70);
}
//#############################################################################################
void HX711_power_up(void)
{
			PD_SCK_SET_LOW;
}
//#############################################################################################
int32_t HX711_valueAve(uint16_t sample)
{
  int64_t  ave = 0;
  for(uint16_t i=0 ; i<sample ; i++)
    ave += ReadHX();
  return (int32_t)(ave / sample);
}

	/*----------------------------------------------------------------------------*/
//#############################################################################################