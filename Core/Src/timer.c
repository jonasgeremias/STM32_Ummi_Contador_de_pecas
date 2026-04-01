/*
 * timer.c
 *
 *  Created on: Apr 1, 2026
 *      Author: Lucas
 */

#include "timer.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

volatile uint16_t timer_3ms = 0;
volatile uint16_t timer_5ms = 0;
volatile uint16_t timer_10ms = 0;
volatile uint16_t timer_50ms = 0;
volatile uint16_t timer_100ms = 0;
volatile uint16_t timer_500ms = 0;
volatile uint16_t timer_1000ms = 0;
volatile uint8_t timer_flag_3ms = 0;
volatile uint8_t timer_flag_5ms = 0;
volatile uint8_t timer_flag_10ms = 0;
volatile uint8_t timer_flag_50ms = 0;
volatile uint8_t timer_flag_100ms = 0;
volatile uint8_t timer_flag_500ms = 0;
volatile uint8_t timer_flag_1000ms = 0;
volatile uint8_t timer_cnt_1000ms = 0;


static uint16_t correcao = 0;

void mainIsr(void) {

  // 1 ms - Timer base para serial
  //serialHandleTimeout1ms();

  // scan_display();

  if (++timer_3ms >= 3) {
    timer_3ms = 0;
    tmr_3ms();
  }

  if (++timer_5ms >= 5) {
    timer_5ms = 0;
    tmr_5ms();
  }

  if (++timer_10ms >= 10) {
    timer_10ms = 0;
    tmr_10ms();
  }

  if (++timer_50ms >= 50) {
    timer_50ms = 0;
    tmr_50ms();
  }
  if (++timer_100ms >= 100) {
    timer_100ms = 0;
    tmr_100ms();
  }

  if (++timer_500ms >= 500) {
    timer_500ms = 0;
    tmr_500ms();
  }

  if (++timer_1000ms >= 1000) {
    timer_1000ms = 0;
    tmr_1000ms();

    if (correcao >= 100) {
      correcao = 0;
      timer_cnt_1000ms--;
    }
  }
}

void tmr_3ms() {
  timer_flag_3ms = 1;
  display_scan();
  //debounce_btns();
  //debounce_entradas_digitais();
}
void tmr_5ms() { timer_flag_5ms = 1; }
void tmr_10ms() { timer_flag_10ms = 1; }
void tmr_50ms() {
//   timer_flag_50ms = 1;
//   if (btn_max_timeout > 0)
//     btn_max_timeout--;
//   if (btn_min_timeout > 0)
//     btn_min_timeout--;
}
void tmr_100ms() { timer_flag_100ms = 1; }
void tmr_500ms() { timer_flag_500ms = 1; }
void tmr_1000ms() { /*timer_flag_1000ms = 1;*/ timer_cnt_1000ms++; }

