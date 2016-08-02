
#include "FreeRTOS.h"
#include "task.h"

#include "basic_io.h"

void vTaskFunction( void *pvParameters );
void vApplicationIdleHook(void);

unsigned long ulTaskNumber[configEXPECTED_NO_RUNNING_TASKS];

const char *pcTextForTask1 = "Task 1 is running\n";
const char *pcTextForTask2 = "Task 2 is running\n";

unsigned long ulIdleCycleCount = 0UL;

int main(void)
{
  xTaskCreate( vTaskFunction, "Task 1", 240, (void*)pcTextForTask1, 1, NULL );

  xTaskCreate( vTaskFunction, "Task 2", 240, (void*)pcTextForTask2, 2, NULL );

  vTaskStartScheduler();	
	
  for(;;);
}

void vTaskFunction(void *pvParameters)
{
  char *pcTaskName;
  portTickType xLastWakeTime;                                          // Declaration d'une variable portTickType qui recevra le dernier instant de reveil
	                                                                     // de la tache.
  pcTaskName = ( char * ) pvParameters;

  xLastWakeTime = xTaskGetTickCount();                                 // initialisation de la variable dernier instant de reveil avec xTaskGetTickCount()

  for(;;)	{
    vPrintString( pcTaskName );
		vPrintStringAndNumber(pcTaskName,ulIdleCycleCount);

    vTaskDelayUntil( &xLastWakeTime, ( 250 / portTICK_RATE_MS ) );     // Pour utiliser cette primitive, il faut d'abord l'autoriser dans le fichier FreeRTOSConfig.h
                                                                       // On recupere l'adresse de la variable instant de reveil
	}
}

void vApplicationIdleHook (void)
{
	ulIdleCycleCount++;
}

