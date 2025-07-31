#include "stm32f4xx.h"
#include<stdint.h>
#include<stdio.h>
#include "stm32f4xx.h"
#include "uart.h"
#include"ADC.h"


uint32_t sensor_value;
int main(void){


	UART2_RXTX_INIT();
    pa1_adc_init();
	start_conversion();
	while(1){
		 start_conversion();
		sensor_value=adc_read();
		printf("sensor value :%d \n \r ",(int)sensor_value);
	}


}




