/*
 * ADC.h
 *
 *  Created on: Jul 31, 2025
 *      Author: desai
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_
#include<stdint.h>
uint32_t adc_read(void);
void start_conversion(void);
void pa1_adc_init(void);
#endif /* INC_ADC_H_ */
