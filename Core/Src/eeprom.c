/*
 * eeprom.c
 *
 *  Created on: Mar 24, 2026
 *      Author: Lucas
 */

#include "eeprom.h"
#include "main.h"
#include <string.h>

#define EEPROM_START_ADDR 0x0801F000
#define EEPROM_END_ADDR 0x0801FFFF

eeprom_data_t dados;

static eeprom_data_t eeprom_buffer = {
    0}; // Buffer para armazenar os dados da EEPROM
static uint8_t eeprom_pending =
    0; // Flag para indicar que uma leitura da EEPROM está pendente
static eeprom_data_t eeprom_last_saved = {
    0}; // Última vez que os dados foram salvos na EEPROM

// INICIA EEPROM VIRTUAL
void eeprom_init(void) {
  eeprom_last_saved = eeprom_read(); // Lê os dados da EEPROM ao iniciar
}

// LÊ DADOS DA EEPROM
eeprom_data_t eeprom_read(void) {
  uint32_t addr = EEPROM_START_ADDR;
  eeprom_data_t last = {0};

  while (addr < EEPROM_END_ADDR && *(uint32_t *)addr != 0xFFFFFFFF) {
    last = *(eeprom_data_t *)addr;
    addr += sizeof(eeprom_data_t);
  }
  return last;
}

// ESCREVE DADOS NA EEPROM
void eeprom_write(eeprom_data_t *data) {
  if (memcmp(data, &eeprom_last_saved, sizeof(eeprom_data_t)) == 0)
    return;

  eeprom_buffer = *data;
  eeprom_pending = 1;
}

bool eeprom_is_pending(void) { return eeprom_pending; }

void eeprom_process(void) {
  if (!eeprom_pending)

    return;

  eeprom_pending = 0;
  uint32_t addr = EEPROM_START_ADDR;

  while (*(uint32_t *)addr != 0xFFFFFFFF && addr < EEPROM_END_ADDR) {
    addr += 4;
  }

  HAL_FLASH_Unlock();
  if (addr >= EEPROM_END_ADDR) {
    FLASH_EraseInitTypeDef erase;
    uint32_t error;

    erase.TypeErase = FLASH_TYPEERASE_SECTORS;
    erase.Sector = FLASH_SECTOR_4;
    erase.NbSectors = 1;
    erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    HAL_FLASHEx_Erase(&erase, &error);
    addr = EEPROM_START_ADDR;
  }

  uint32_t *ptr = (uint32_t *)&eeprom_buffer;

  for (int i = 0; i < sizeof(eeprom_data_t) / 4; i++) {
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr + (i * 4), ptr[i]);
  }
  HAL_FLASH_Lock();
  eeprom_last_saved = eeprom_buffer;
}