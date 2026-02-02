/**
 ****************************************************************************
 * @file    STHallPinInterface.h
 * @author  Wyrm
 * @brief   This is a project-specific configuration file (should be skip-worktree in git). 
 *          Comment out the necessary lines to properly configure the project 
 * @version V1.0.2
 * @date    15. Feb. 2025							
 *************************************************************************
 */

#ifndef __W_PIN_H__
#define __W_PIN_H__ 

#include <stdlib.h>
#include "main.h"

#include "PinInterface.h"

/**
 * @addtogroup PinerInterface 
 * @{
 */

/**
 * @defgroup STHallPinInterface STHallPinInterface Config file 
 * @note
 * @{
 */
/* Private macro -------------------------------------------------------------*/
//#define ST_PIN0
//#define ST_PIN1
//#define ST_PIN2
//#define ST_PIN3
//#define ST_PIN4
//#define ST_PIN5
//#define ST_PIN6
//#define ST_PIN7
#define ST_PIN8
//#define ST_PIN9
//#define ST_PIN10
//#define ST_PIN11
//#define ST_PIN12
//#define ST_PIN13
//#define ST_PIN14

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions -------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
 * @brief   Used timer's enumerate in current code 
 * @details this enumeration is needed to determine the number of timers to be used
 */
typedef enum {
              #ifdef ST_PIN0
              kPinInter_pin0,
              #endif
              #ifdef ST_PIN1
              kPinInter_pin1,
              #endif

              #ifdef ST_PIN2
              kPinInter_pin2,
              #endif
              
              #ifdef ST_PIN3
              kPinInter_pin3,
              #endif

              #ifdef ST_PIN4
              kPinInter_pin4,
              #endif

              #ifdef ST_PIN5
              kPinInter_pin5,
              #endif

              #ifdef ST_PIN6
              kPinInter_pin6,
              #endif

              #ifdef ST_PIN7
              kPinInter_pin7,
              #endif

              #ifdef ST_PIN8
              kPinInter_pin8,
              #endif

              #ifdef ST_PIN9
              kPinInter_pin9,
              #endif

              #ifdef ST_PIN10
              kPinInter_pin10,
              #endif

              #ifdef ST_PIN11
              kPinInter_pin11,
              #endif

              #ifdef ST_PIN12
              kPinInter_pin12,
              #endif

              #ifdef ST_PIN13
              kPinInter_pin13,
              #endif

              #ifdef ST_PIN14
              kPinInter_pin14,
              #endif        
              #ifdef ST_PIN15
              kPinInter_pin15,
              #endif              
              kPinInter_number_of_elem  /*!< number of used timer's*/
}ePinHandle_t;

#endif
/* Public macro -------------------------------------------------------------*/
/** @}*/


/** @}*/
/** @}*/