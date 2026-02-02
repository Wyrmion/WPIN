/**
 ****************************************************************************
 * @file     PinInterface.C
 * @author   Wyrm
 * @brief    This file provides code for work with PinInterface abstract class
 * @version  V1.0.0
 * @date     30. July 2025
 *************************************************************************
 */
 
#include "PinInterface.h"
#include "PinInterfacePrivate.h"
#include <stdlib.h>
#include <string.h>


//#include <string.h>
//#include <math.h>


/**
 * @addtogroup PinInterface
 * @{
 */
/* Private macro -------------------------------------------------------------*/ 
  /** @defgroup PinInterface_Private_macro PinInterface Private macro
   * @{
   */
  /** @}*/ /* End of PinInterface macro group*/
/* Private typedef -----------------------------------------------------------*/


/* Private constants ---------------------------------------------------------*/



/** @defgroup PinInterface_Private_Functions PinInterface Private Functions
  * @{
  */
  /** @}*/
/* Exported functions -------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 

/**
 * @brief Pin interface constructor 
 * 
 * @param hwtim  pointer to hw class
 * @param IRQn   irq number for critical section. Use TIMER_INTERFACE_NO_CRITICAL if you don't need enter critical section
 * @return PinInterface_t* allocated memory
 */
PinInterface_t*	  PinInterface_ctor(uint32_t hwpin,int32_t IRQn)
{
  
  PinInterface_t* cthis;
  
  if((cthis = heap_malloc_cast(PinInterface_t)) == NULL)
    return NULL;
  
  memset(cthis,0,sizeof(*cthis));

  cthis->hwpin  = hwpin;
  cthis->IRQn = IRQn;
  
  return cthis;
}

/**
 * @brief Pin interface destructor 
 * 
 * @param cthis pointer to this @rer PinInterface_t obj
 */
void PinInterface_dtor(PinInterface_t* cthis)
{
  heap_free(cthis);
}

/**
 * @brief Set callback for tim ellapsed
 * 
 * @param[in] cthis  pointer to @ref PinInterface_t obj
 * @param[in] ctx pointer to ctx
 * @param[in] TOutClb pointer to tim callback function
 * @return true  is setup succesful
 * @return false 
 */
bool PinInterface_SetCbExt(PinInterface_t* cthis,void* ctx,void(*ExtClb)(void*))
{
  if((cthis == NULL)||(ExtClb == NULL))
    return false;
  
  cthis->ctx = ctx;
  cthis->ExtClb = ExtClb;
  return true;
}

/**
* @brief Set callback for tim ellapsed
 * 
 * @param[in] cthis  pointer to @ref PinInterface_t obj
 * @param[in] ctx   pointer to ctx
 * @param[in] semaphore pointer to tim callback function
 * @return true is setup succesful
 * @return false 
 */
bool PinInterface_SetSemaphore(PinInterface_t *cthis,void* ctx, void *semaphore)
{
  if((cthis == NULL)||(semaphore == NULL))
    return false;

  cthis->ctx = ctx;
  cthis->sem = semaphore;    
  return true;
}



  

/** @}*/ /*End of PinInterface group*/