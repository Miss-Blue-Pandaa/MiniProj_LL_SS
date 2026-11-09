#include "stm32f7xx.h"                  // Device header
extern void configuration_overclock(void);
extern int Init_GUIThread (void);
extern void Init_Ethernet (void);

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS2                  // when RTE component CMSIS RTOS2 is used
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#endif

/*----------------------------------------------------------------------------
 *      Tâche de test (vide) : à compléter par les étudiants
 *---------------------------------------------------------------------------*/
osThreadId_t tid_Test;

void servo_set_angle (int deg);


static void Thread_Test (void *argument)
{
  (void)argument;

  // Initialisations propres à la tâche (si besoin) ici

  while (1)
  {
		for(int i=0;i<180;i++){
			servo_set_angle(i);
			osDelay(100);   // période de la boucle : 100 ms
		}

  }
}

static int Init_TestThread (void)
{
  tid_Test = osThreadNew(Thread_Test, NULL, NULL);
  if (tid_Test == NULL) {
    return -1;
  }
  return 0;
}

void servo_set_angle (int deg){
	float alpha;
	alpha = deg*20000/90.0;
	TIM10->CCR1 = alpha;			//DutyCyle PWM
}

int main(void)
{
  configuration_overclock(); //pour pouvoir utiliser l'écran LCD

	/**********************************
	Début Initialisation périphérique
	**********************************/
	
	RCC->APB1ENR |= (1<<29); //activation DAC
	RCC->APB2ENR |= (1<<10); //activation ADC3

	RCC->AHB1ENR|=(1<<8); //Activ GPIO I
	RCC->AHB1ENR|=(1<<0); //Activ GPIO A
	RCC->AHB1ENR|=(1<<5); //Activ GPIO F
	RCC->APB1ENR|=(1<<7); //Activ TIM13
	
	GPIOI->MODER|=(1<<4); //LED en output en PI2
	GPIOA->MODER |= (3<<8); //PA4 en mode analog (sortie PA4)
	GPIOF->MODER |= (3<<20); //PF10 en mode analog potentiomètre
	GPIOF->MODER |= (2<<16); //PF8 en mode AF
	GPIOF->AFR[1] |= (9<<0); //PF8 en mode TIM13_CH1
	
//	DAC->CR |= (1<<0); //channel 1 en sortie
//	ADC3->SQR3 |= (8<<0); // Selection de la voie PF10
//	ADC3->CR2 |= (1<<0); // activation de l'ADC
	
	TIM13->CCMR1 |= (6<<4); //TIM13_CH1 en PWM mode 1
	TIM13->CCER |= (1<<0);	//connectr 0C1 
	TIM13->PSC = 1; 				//Prescaler
	TIM13->ARR = 9999;			//Periode PWM
	TIM13->CCR1 = 4000;			//DutyCyle PWM
	TIM13->CR1 |= (1<<0);		//Lancer le Timer


                           

	/**********************************
	Fin Initialisation périphérique
	**********************************/

	/**********************************
	Utilisation RTOS (Keil RTX5)
	**********************************/
	#ifdef RTE_CMSIS_RTOS2
	  /* Initialize CMSIS-RTOS2 */
	  osKernelInitialize ();

	  /* Create thread functions that start executing */
		Init_Ethernet();
		Init_GUIThread();
		Init_TestThread();   // tâche de test (boucle avec osDelay)

	  /* Start thread execution */
	  osKernelStart();
	#endif

  /* Infinite loop  (ne s'exécute pas avec le RTOS!!!)*/
  while (1)
  {
  }
}

