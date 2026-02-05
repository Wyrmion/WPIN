/**
  ******************************************************************************
  * @file     PinInterface.h
  * @author   Wyrm
  * @brief    Header file for Pin Interface abstract class
  * @version  V1.0.0
  * @date     12 Nov. 2024
  ******************************************************************************
    @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  1) Register ctx and callback by:
  
  cthis->pininter.ctx  = cthis;
  cthis->pininter.ExtClb = _this_ext;

  2) Subscribe to irq
  
  if(!SubscribePin_Irq(&this->timerinter,this->reletim))
    while(1); //bug catch tag


  If need end use this timer call UnsubscribePin_Irq

  @endverbatim
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PIN_INTERFACE_H__
#define __PIN_INTERFACE_H__



#ifdef __cplusplus
extern "C"{
#endif

#include  <stdint.h>
#include  <stdbool.h>
#include  <stddef.h>
#include  <limits.h>

#include "wheap.h"
#include "main.h"

/**
 * @addtogroup Wyrm_Drivers Wyrm Drivers
 * @{
 */

/**
 * @defgroup PinInterface Pin Interface
 * @{
 */

/* Public macro -------------------------------------------------------------*/
#define PIN_INTERFACE_NO_CRITICAL INT32_MAX
/**
 * @brief Pin Interface class 
 * 
 */
typedef struct PinInterface PinInterface_t;  


/* Public typedef -----------------------------------------------------------*/
/* Public function prototypes -----------------------------------------------*/
/**
 * @defgroup Pin_public_func Pin public function
 * @{
 */

  /**
   * @defgroup Template_public_ctor_dtor Template constructor/destructor
   * @{
   */
  PinInterface_t*	  PinInterface_ctor(uint32_t hwpin,int32_t IRQn);
  void              PinInterface_dtor(PinInterface_t* cthis);
  
  /** @}*/ /*End of Template constructor/destructor group*/

/**
 * @defgroup  Pin_public_basic Pin basic public function
 * @{
 */
  bool PinInterface_SubscribeIrq(PinInterface_t* cthis);
  bool PinInterface_UnsubscribeIrq(PinInterface_t* cthis);

  void PinInterface_CRITICAL_enter(PinInterface_t* cthis);
  void PinInterface_CRITICAL_exit(PinInterface_t* cthis);

  void PinInterface_IRQ_Disable(PinInterface_t* cthis);
  void PinInterface_IRQ_Enable(PinInterface_t* cthis);
  
  bool PinInterface_SetCbExt(PinInterface_t* cthis,void* ctx,void(*ExtClb)(void*));
  #ifdef INC_FREERTOS_H
    bool PinInterface_SetSemaphore(PinInterface_t *cthis,void* ctx, void *semaphore);
  #endif
/** @} */ /*End of Pin basic public function group*/

/** @} */

/** @} */  /* Pin Interface group end */
/** @} */  /* Wyrm_Drivers group end*/


#ifdef __cplusplus
}
#endif

#endif

