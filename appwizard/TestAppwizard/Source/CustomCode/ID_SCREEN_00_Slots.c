/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2026  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File        : ID_SCREEN_00_Slots.c
Purpose     : AppWizard managed file, function content could be changed
---------------------------END-OF-HEADER------------------------------
*/

#include "Application.h"
#include "../Generated/Resource.h"
#include "../Generated/ID_SCREEN_00.h"

/*** Begin of user code area ***/
#include "stm32f7xx.h"                  // Device header

/*** End of user code area ***/

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       cbID_SCREEN_00
*/
void cbID_SCREEN_00(WM_MESSAGE * pMsg) {
  GUI_USE_PARA(pMsg);
}

/*********************************************************************
*
*       ID_SCREEN_00__ID_SWITCH_00__WM_NOTIFICATION_VALUE_CHANGED
*/
void ID_SCREEN_00__ID_SWITCH_00__WM_NOTIFICATION_VALUE_CHANGED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  int Val;
  Val = APPW_GetValue(ID_SCREEN_00, ID_SWITCH_00, NULL);
  //Val vaut 0 ou 1
  //code à exécuter à mettre ici
	if (Val == 0)	GPIOI->ODR &= ~(1<<2);
	else if (Val==1) GPIOI->ODR |= (1<<2);

}

/*********************************************************************
*
*       ID_SCREEN_00__ID_SLIDER_00__WM_NOTIFICATION_VALUE_CHANGED
*/
void ID_SCREEN_00__ID_SLIDER_00__WM_NOTIFICATION_VALUE_CHANGED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  int Val;
	float tension;
  Val = APPW_GetValue(ID_SCREEN_00, ID_SLIDER_00, NULL);
  //Val vaut une valeur entre 0 et 100
  //code à exécuter à mettre ici
	tension = Val*4095.0/100.0;
	DAC->DHR12R1 = tension;

}

/*********************************************************************
*
*       ID_SCREEN_00__ID_ROTARY_00__WM_NOTIFICATION_VALUE_CHANGED
*/
void ID_SCREEN_00__ID_ROTARY_00__WM_NOTIFICATION_VALUE_CHANGED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult) {
  int Val;
  Val = APPW_GetValue(ID_SCREEN_00, ID_ROTARY_00, NULL);
  //Val vaut une valeur entre -900 et 900
  //code à exécuter à mettre ici
}

/*************************** End of file ****************************/
