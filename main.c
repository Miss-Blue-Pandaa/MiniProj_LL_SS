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
float distance_cm(void);

static void Thread_Test (void *argument)
{
  (void)argument;

  // Initialisations propres à la tâche (si besoin) ici

  while (1)
  {
		osDelay(100);
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
	if (deg < 0) deg = 0;
  if (deg > 180) deg = 180;
	alpha = deg*20000.0/180;
	TIM13->CCR1 = alpha;			//DutyCyle PWM
}

float distance_cm(void)
{
	int duration = 0;
	int timeout = 0;
	//Envoi du signal, impulsion TRIG de 10 µs
	GPIOB->BSRR = (1 << 15); //TRIG High
	for (volatile int i = 0; i < 84; i++); //tempo
  GPIOB->BSRR = (1 << (14 + 16)); // TRIG Low
	// Attendre front montant ECHO
	timeout = 0;
	for (int t = 0; t < 30000; t++) {
		if ((GPIOB->IDR & (1 << 14))) break;
		if (t > 30000) return -1.0; //Timeout
	}
// Mesurer durée HIGH
	duration = 0;
	while ((GPIOB->IDR & (1 << 14))) {
			duration++;
			if (++timeout > 30000) return -1.0;
	}
	return (float)duration / 58.0;
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
	RCC->AHB1ENR|=(1<<1); //Activ GPIO B
	RCC->AHB1ENR|=(1<<5); //Activ GPIO F
	RCC->APB1ENR|=(1<<7); //Activ TIM13
	RCC->APB2ENR|=(1<<17); //Activ TIM10
	
	GPIOI->MODER|=(1<<4); //LED en output en PI2
	GPIOA->MODER |= (3<<8); //PA4 en mode analog (sortie PA4)
	GPIOB->MODER |= (0<<28); //PB14 ECHO input
	GPIOB->MODER |= (3<<30);	//PB15 TRIG ouput
	GPIOF->MODER |= (3<<20); //PF10 en mode analog potentiomètre
	GPIOF->MODER |= (2<<16); //PF8 en mode AF
	GPIOF->AFR[1] |= (9<<0); //PF8 en mode TIM13_CH1
	GPIOF->AFR[0] |= (3<<24); //PF6 en mode TIM10_CH1
//	DAC->CR |= (1<<0); //channel 1 en sortie
//	ADC3->SQR3 |= (8<<0); // Selection de la voie PF10
//	ADC3->CR2 |= (1<<0); // activation de l'ADC
	
	TIM13->CCMR1 |= (6<<4); //TIM13_CH1 en PWM mode 1
	TIM13->CCER |= (1<<0);	//connectr 0C1 
	TIM13->PSC = 83; 				//Prescaler
	TIM13->ARR = 19999;			//Periode PWM
	TIM13->CCR1 = 4000;			//DutyCyle PWM
	TIM13->CR1 |= (1<<0);		//Lancer le Timer

//	TIM10->CCMR1 |= (6<<4); //TIM10_CH1 en PWM mode 1
//	TIM10->CCER |= (1<<0);	//connectr 0C1 
//	TIM10->PSC = 83; 				//Prescaler
//	TIM10->ARR = 19999;			//Periode PWM
//	TIM10->CCR1 = 4000;			//DutyCyle PWM
//	TIM10->CR1 |= (1<<0);		//Lancer le Timer
//                           

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

