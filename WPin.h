/**
  ******************************************************************************
  * @file     WPin.h
  * @author   Wyrm
  * @brief    Header file for fast pin set/reset
  * @version  V1.0.0
  * @date     20 Oct. 2024
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W_PIN_H__
#define __W_PIN_H__


#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "main.h"


/**
 * @addtogroup Wyrm_Drivers Wyrm Drivers
 * @{
 */

/**
 * @defgroup MyHalPin My HAL Pin control 
 * @{
  
 */
/* Public macro -------------------------------------------------------------*/
#define WPIN_SET(__PORT__,__PIN__)   __PORT__->BSRR = __PIN__                      /*!< Set pin via port struct*/
#define WPIN_RESET(__PORT__,__PIN__) __PORT__->BSRR = (uint32_t)__PIN__ << 16U     /*!< Reset pin via port struct*/

/**
 * @defgroup MY_HPIN_func My Hal pin set reset func/macro
 * @{
 */
#define WPIN_S_SET(WPin)      WPin.Port->BSRR = WPin.Pin                        /*!< Set pin via @ref MyHALPin_t struct*/
#define WPIN_S_RESET(WPin)    WPin.Port->BSRR = (uint32_t)WPin.Pin << 16U       /*!< Reset pin via @ref MyHALPin_t struct*/

#define WPIN_S_IS_SET(WPin)   ((WPin.Port->IDR & WPin.Pin) != (uint32_t)GPIO_PIN_RESET) /*!< Is @ref MyHALPin_t is set */
#define WPIN_S_IS_RESET(WPin) ((WPin.Port->IDR & WPin.Pin) == (uint32_t)GPIO_PIN_RESET)/*!< Is @ref MyHALPin_t is reset */

/* Public typedef -----------------------------------------------------------*/
/**
 * @brief Pin and Port united struct
 * 
 */
typedef struct
{
	GPIO_TypeDef* Port; 
	uint16_t Pin;       
}WPin_t;
/** @}*/

/* Public constants ---------------------------------------------------------*/
/* Public function prototypes -----------------------------------------------*/
/* Public variables ---------------------------------------------------------*/
/* Public function prototypes -----------------------------------------------*/


/** @}*/
/** @}*/

#ifdef __cplusplus
}
#endif

#endif

