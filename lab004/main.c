#include "FreeRTOS.h"
#include "task.h"

#include "basic_io.h"


/*
 #define mainDELAY_LOOP_COUNT		(0xfffff)                       // Macro pour les delais d'inactivit�

  Suppression de la busy loop et usage de l'api vTaskDelay((temps en ms) / portTICK_RATE_MS)
	
*/

void vFonctionTask (void *pvParameters);

static const char *pcTaskNom_1 = "La tache 1 s'execute ...\n";    // Declaration de variable statique pour identifier 
static const char *pcTaskNom_2 = "La tache 2 s'execute ...\n";    // et differencier les taches s'executant dans la fonction

unsigned long ulTaskNumber[configEXPECTED_NO_RUNNING_TASKS];    // Tableau pour afficher les taches dans logique analyser

int main(void)
{
  xTaskCreate(vFonctionTask, "Task 1", 200,
            	(void *) pcTaskNom_1, 1, NULL);                    // Creation de la tache une de taille 200 en mots, priorit� 1 sans handle
  xTaskCreate(vFonctionTask, "Task 2", 200, 
	            (void *) pcTaskNom_2, tskIDLE_PRIORITY+2, NULL);   // Creation de la tache deux... avec utilisation du parametre pcTaskName recup�r�
                                                                 // Modification de la priorit� avec tskIDLE_PRIORITY + 2, on remarque que la tache
	                                                               // deux est la seule � s'executer, �tant donn�e sa priorit� haute.
	
  vTaskStartScheduler();                                        // Creation de la tache idle pour l'ordonnancement

  for(;;);                                                      // Boucle infini
}

void vFonctionTask(void *pvParameters)                          // Implementation de la tache une
{
  char *pcTaskName;                                             // Declaration de la variable pointe qui identifie la tache
  volatile unsigned long ul;                                    // Decl et init de la variable compteur
  
	pcTaskName = (char *) pvParameters;                           // Initialisation de la variable d'identification en recuperant 
	                                                              // le parametre cast� de (void *) en (char *)
	
  for(;;) {
    vPrintString(pcTaskName);                                   // Code d'execution de la tache dans la boucle infinie

    vTaskDelay(250/portTICK_RATE_MS);                           // Usage du delai � la place de busy loop, on remarque notamment que 
		                                                            // vTaskDelay donne la main � la tache une de priorit� faible apr�s que 
		                                                            // la tache deux se soit execut�e; Ce que la busyloop ne faisait car elle 
		                                                            // maintenait la tache 1 en �tat bloqu�e
		
		//for(ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) {            //Delai pour le blocage de la tache
	  //}
  }
}

