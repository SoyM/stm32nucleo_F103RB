/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "flash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
ProtoCmd_t curr_cmd;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId nonblockTaskHandle;
osMessageQId cmdQueueHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTaskNonblock(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of cmdQueue */
  osMessageQDef(cmdQueue, 4, ProtoCmd_t);
  cmdQueueHandle = osMessageCreate(osMessageQ(cmdQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of nonblockTask */
  osThreadDef(nonblockTask, StartTaskNonblock, osPriorityBelowNormal, 0, 128);
  nonblockTaskHandle = osThreadCreate(osThread(nonblockTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	
	
  for(;;)
  {
    if(cmdQueueHandle != 0)
    {
      if(xQueueReceive(cmdQueueHandle, (void *)&curr_cmd, ( TickType_t )500))
      {
				if(curr_cmd.data[0]== 0x81 
					|| curr_cmd.data[0]== 0x82 
					|| curr_cmd.data[0]== 0x83 
					|| curr_cmd.data[0]== 0x84
					|| curr_cmd.data[0]== 0xFF)
				{
					if(curr_cmd.data[2] == 0x00 && curr_cmd.data[3] == 0x23)
					{
						int16_t upgradeFlag;

						upgradeFlag = 0x0002;
						FlashWriteDate(UPGRADE_ADDRESS, &upgradeFlag, 1);
						__disable_irq();
						NVIC_SystemReset();					
					}
				}
         HAL_UART_Transmit_DMA(&huart2, (void *)curr_cmd.data, curr_cmd.len); 
      }
    }		
		

  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTaskNonblock */
/**
* @brief Function implementing the nonblockTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskNonblock */
void StartTaskNonblock(void const * argument)
{
  /* USER CODE BEGIN StartTaskNonblock */
	uint32_t sum_adc;
  /* Infinite loop */
  for(;;)
  {
    sum_adc = 0;
		for(uint8_t i=0; i<5; i++)
		{
			sum_adc = sum_adc + adc_value[i*2];
		}
		average_adc = sum_adc / 5;
		average_volt_a2 = average_adc * (3.363 / 4032);
		
		sum_adc = 0;
		for(uint8_t i=0; i<5; i++)
		{
			sum_adc = sum_adc + adc_value[i*2+1];
		}
		average_adc = sum_adc / 5;		
		average_volt_a3 = average_adc * (3.363 / 4032);
		
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    osDelay(500);
  }
  /* USER CODE END StartTaskNonblock */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
