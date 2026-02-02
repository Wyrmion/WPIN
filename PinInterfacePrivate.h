/**
  ******************************************************************************
  * @file     PinInterfacePrivate.h
  * @author   Wyrm
  * @brief    Header file for Pin Interface abstract class
  * @version  V1.0.0
  * @date     12 Nov. 2024
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PIN_INTERFACE_PRIVATE_H__
#define __PIN_INTERFACE_PRIVATE_H__


#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>



/**
 * @addtogroup Wyrm_Drivers Wyrm Drivers
 * @{
 */

/**
 * @defgroup PinInterfacePrivate Pin Interface private
 * @{
 */

/* Public macro -------------------------------------------------------------*/

/**
 * @brief Pin Interface class 
 * 
 */
struct PinInterface
{
  
  uint32_t   hwpin;         /*!< pin number class*/
  

  int32_t IRQn;             /*!< IRQ number for critical section*/
  bool    IRQnEnable;       /*!< IRQ enable flag (use for critical section)*/
  
  
  void*   sem;              /*!< pointer to rtos semaphore*/
  void*   ctx;              /*!< pointer to parent*/
  void(*ExtClb)(void*);    	/*!< pointer ext pin clb function*/
};

/* Public function prototypes -----------------------------------------------*/

/** @} */  /* Pin Interface group end */
/** @} */  /* Wyrm_Drivers group end*/


#ifdef __cplusplus
}
#endif

#endif

