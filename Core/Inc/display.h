/*
 * display.h
 *
 *  Created on: Apr 1, 2026
 *      Author: Lucas
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdint.h>

//void display_init(void);
void display_scan(void);
void escreve_segmentos(uint8_t valor);
void desliga_displays(uint8_t d);

#endif /* INC_DISPLAY_H_ */
