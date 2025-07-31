#define ADC1EN   (1U<<8)
#define GPIOAEN (1U<<0)
#include "stm32f4xx.h"
#include <stdint.h>
#define ADCCH1 (1U<<0)
#define ADC_SEQ_LEN_1 (0X00)
#define CR2_ADON (1U<<0)
#define CR2_SWSTART (1U<<30)
#define SR_EOC (1U<<1)
#include "ADC.h"

void pa1_adc_init(void){
	//enable clock access to adc pin port  gpioa
    RCC->AHB1ENR |=GPIOAEN;
	//st moder to pa1 to analog
    GPIOA->MODER |=(1U<<2);
    GPIOA->MODER |=(1U<<3);
	//configure the adc pin
    RCC->APB2ENR |= ADC1EN;
    //Configuring the adc parameters
    /*
     * conversion sequnence start/
     * conversion sequence length
     * enable adc module*/
    ADC1->SQR3=ADCCH1;
    ADC1->SQR1=ADC_SEQ_LEN_1;

    ADC1->CR2 |=CR2_ADON;


}

void start_conversion(void){
	//start the adc conversion
	ADC1->CR2|=CR2_SWSTART;//enables the swst(start conversions in the regular channnel)

}
uint32_t adc_read(void){
	//wait for conversion to be complete
	//read the converted result
while(!(ADC1->SR & SR_EOC)){}
return (ADC1->DR);
}
