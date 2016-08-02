#include "FreeRTOS.h"
#include "task.h"

#include "basic_io.h"

#define mainDELAY_LOOP_COUNT		(0xfffff)                       // Macro pour les delais d'inactivité

/*

//void vTask1(void *pvParameters);                                // Prototype Tache une
//void vTask2(void *pvParameters);                                // Prototype Tache deux

 Modifiction du fichier, usage d'une fonction unique pour les deux taches 
   Création d'une tache vFonctionTask
	 Déclaration d'une const char * static pour recuperer l'identité de chaque tache
*/

void vFonctionTask (void *pvParameters);

static const char *pcTaskNom_1 = "La tache 1 s'execute ...\n";    // Declaration de variable statique pour identifier 
static const char *pcTaskNom_2 = "La tache 2 s'execute ...\n";    // et differencier les taches s'executant dans la fonction

unsigned long ulTaskNumber[configEXPECTED_NO_RUNNING_TASKS];    // Tableau pour afficher les taches dans logique analyser

int main(void)
{
  xTaskCreate(vFonctionTask, "Task 1", 200,
            	(void *) pcTaskNom_1, 1, NULL);                  // Creation de la tache une de taille 200 en mots, priorité 1 sans handle
  xTaskCreate(vFonctionTask, "Task 2", 200, 
	            (void *) pcTaskNom_2, 1, NULL);                  // Creation de la tache deux... avec utilisation du parametre pcTaskName recupéré

  vTaskStartScheduler();                                        // Creation de la tache idle pour l'ordonnancement

  for(;;);                                                      // Boucle infini
}

void vFonctionTask(void *pvParameters)                          // Implementation de la tache une
{
  char *pcTaskName;                                             // Declaration de la variable pointe qui identifie la tache
  volatile unsigned long ul;                                    // Decl et init de la variable compteur
  
	pcTaskName = (char *) pvParameters;                           // Initialisation de la variable d'identification en recuperant 
	                                                              // le parametre casté de (void *) en (char *)
	
  for(;;) {
    vPrintString(pcTaskName);                                   // Code d'execution de la tache dans la boucle infinie

    for(ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) {              // Delai pour le blocage de la tache

    }
  }
}

