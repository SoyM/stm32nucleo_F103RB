#include "flash.h"


//Flash flash;

uint32_t FLASH_If_Erase(uint32_t start)
{
    uint32_t NbrOfPages = 0;
    uint32_t PageError = 0;
    FLASH_EraseInitTypeDef pEraseInit;
    HAL_StatusTypeDef status = HAL_OK;

    HAL_FLASH_Unlock();

    NbrOfPages = 1;

    pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    pEraseInit.PageAddress = start;
    pEraseInit.Banks = FLASH_BANK_1;
    pEraseInit.NbPages = NbrOfPages;
    status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);

    HAL_FLASH_Lock();

    if (status != HAL_OK)
    {
        return FLASHIF_ERASEKO;
    }

    return FLASHIF_OK;
}


void FlashWriteDate(uint32_t address, int16_t *pData, uint16_t size)
{
	uint16_t i;
	uint32_t pageError;
	FLASH_EraseInitTypeDef erase;

	erase.TypeErase = FLASH_TYPEERASE_PAGES;
	erase.NbPages = 1;
	erase.PageAddress = address;
	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&erase, &pageError);
	for (i = 0; i < size; i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address + (2 * i),
						  pData[i]);
	}
	HAL_FLASH_Lock();
}


void FlashReadDate(uint32_t address, int16_t *pData, uint16_t size)
{
	uint16_t i;

	for (i = 0; i < size; i++)
	{
		pData[i] = *(__IO uint16_t *)address;
		address += 2;
	}
}

