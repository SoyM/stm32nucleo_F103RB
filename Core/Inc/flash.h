#ifndef _FLASH_H_
#define _FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

#define UPGRADE_ADDRESS ((uint32_t)0x0800F800)
#define ADDR_FLASH_PAGE_63 ((uint32_t)0x0800FC00)

enum
{
    FLASHIF_OK = 0,
    FLASHIF_ERASEKO,
    FLASHIF_WRITINGCTRL_ERROR,
    FLASHIF_WRITING_ERROR,
    FLASHIF_PROTECTION_ERRROR
};

typedef struct
{
	int16_t calibrationData[42];
} Flash;

extern Flash flash;
uint32_t FLASH_If_Erase(uint32_t start);
void FlashWriteDate(uint32_t address, int16_t *pData, uint16_t size);
void FlashReadDate(uint32_t address, int16_t *pData, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* _FLASH_H_ */
