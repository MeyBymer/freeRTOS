#include "FreeRTOS.h"
#include "task.h"

#include "basic_io.h"

#define mainDELAY_LOOP_COUNT		(0xfffff)                       // Macro pour les delais d'inactivité

void vTask1(void *pvParameters);                                // Prototype Tache une
void vTask2(void *pvParameters);                                // Prototype Tache deux

unsigned long ulTaskNumber[configEXPECTED_NO_RUNNING_TASKS];    // Tableau pour afficher les taches dans logique analyser

int main(void)
{
  xTaskCreate(vTask1, "Task 1", 200, NULL, 1, NULL);            // Creation de la tache une de taille 200 en mots, priorité 1 sans handle

  xTaskCreate(vTask2, "Task 2", 200, NULL, 1, NULL);            // Creation de la tache deux...

  vTaskStartScheduler();                                        // Creation de la tache idle pour l'ordonnancement

  for(;;);                                                      // Boucle infini
}

void vTask1(void *pvParameters)                                 // Implementation de la tache une
{
  const char *pcTaskName = "Task 1 is running\n";               // Declaration et initialisation de la variable pointe qui identifie la tache
  volatile unsigned long ul;                                    // Decl et init de la variable compteur

  for(;;) {
    vPrintString(pcTaskName);                                   // Code d'execution de la tache dans la boucle infinie

    for(ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) {              // Delai pour le blocage de la tache

    }
  }
}

void vTask2(void *pvParameters)
{
  const char *pcTaskName = "Task 2 is running\n";
  volatile unsigned long ul;

  for(;;) {
    vPrintString( pcTaskName );

    for(ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) {

      }
  }
}
