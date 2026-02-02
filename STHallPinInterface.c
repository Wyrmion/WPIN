/**
 ****************************************************************************
 * @file     STHallPinInterface.c
 * @author   Wyrm
 * @brief    This file provides code for work interface piner class 
 * @version  V1.1.0
 * @date     06. Jan. 2025						
 *************************************************************************
 */

#include <stdint.h>
#include <stdlib.h>



#include "STHallPinInterface.h"
#include "PinInterfacePrivate.h"

#ifdef W_USE_RTOS
  #include "cmsis_os2.h"
#endif

#include "main.h"


/**
 * @addtogroup PinInterface 
 * @{
 */

#define ST_PIN_CAST(cthis) ((PIN_HandleTypeDef*)cthis)
/* Private macro -------------------------------------------------------------*/

#define CHECK_ST_PIN0     ~,~
#define CHECK_ST_PIN1     ~,~
#define CHECK_ST_PIN2     ~,~
#define CHECK_ST_PIN3     ~,~
#define CHECK_ST_PIN4     ~,~
#define CHECK_ST_PIN5     ~,~
#define CHECK_ST_PIN6     ~,~
#define CHECK_ST_PIN7     ~,~
#define CHECK_ST_PIN8     ~,~
#define CHECK_ST_PIN9     ~,~
#define CHECK_ST_PIN10    ~,~
#define CHECK_ST_PIN11    ~,~
#define CHECK_ST_PIN12    ~,~
#define CHECK_ST_PIN13    ~,~
#define CHECK_ST_PIN14    ~,~
#define CHECK_ST_PIN15    ~,~

#define CAT(a, b) CAT_IMPL(a, b)
#define CAT_IMPL(a, b) a ## b

enum {kCOUNTER_PIN_1_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_PIN_1_BASE - 1)

#define PIN_CASE_(num,counter) case (CAT(GPIO_PIN_,num)): {return COUNTER_REL_INC(counter);}
#define PIN_CASE(num) PIN_CASE_(num,__COUNTER__)

#define PIN_CASE_INDX_(num,indx,counter) case (CAT(GPIO_PIN_,num)): {indx = COUNTER_REL_INC(counter);break;}
#define PIN_CASE_INDX(num,indx) PIN_CASE_INDX_(num,indx,__COUNTER__)

#define IS_ST_PIN_DEFINED(num) CHECK((CAT(CHECK_,CAT(ST_PIN,num)), 0, 1))
#define CHECK_ST_PIN1 ~,~
#define CHECK(tup) CHECK_IMPL tup
#define CHECK_IMPL(a, b, c, ...) c

#define IIF(condition, true_value, false_value) CAT(IIF_,condition)(true_value, false_value)
#define IIF_0(true_value, false_value) false_value
#define IIF_1(true_value, false_value) true_value 

#define CASE_IF_ST_PIN(num,indx)  IIF(IS_ST_PIN_DEFINED(num), CASE_ST_PIN, CASE_NOT_ST_PIN)(num,indx)
// this will be used if ST_PIN##num is defined:
#define CASE_ST_PIN(num,indx)     PIN_CASE_INDX(num,indx)
// this will be used if ST_PIN##num is NOT defined:
#define CASE_NOT_ST_PIN(num,indx) //

#define PIN_IRQ_SWICH(mem,indx)\
  switch(mem){\
    CASE_IF_ST_PIN(0, indx)\
    CASE_IF_ST_PIN(1, indx)\
    CASE_IF_ST_PIN(2, indx)\
    CASE_IF_ST_PIN(3, indx)\
    CASE_IF_ST_PIN(4, indx)\
    CASE_IF_ST_PIN(5, indx)\
    CASE_IF_ST_PIN(6, indx)\
    CASE_IF_ST_PIN(7, indx)\
    CASE_IF_ST_PIN(8, indx)\
    CASE_IF_ST_PIN(9, indx)\
    CASE_IF_ST_PIN(10, indx)\
    CASE_IF_ST_PIN(11, indx)\
    CASE_IF_ST_PIN(12, indx)\
    CASE_IF_ST_PIN(13, indx)\
    CASE_IF_ST_PIN(14, indx)\
    CASE_IF_ST_PIN(15, indx)\
    default:  indx = -1;\
              break;\
  }\

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#ifndef USE_MACRO_SWITCH
static inline  int32_t _this_get_pin_indx(uint32_t pin);
#endif
/* Exported functions -------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
 * @brief Array of pointer to @ref sPinInterface_Handle_t linked to stm32 handle 
 *
 */
static PinInterface_t* hpinInter[kPinInter_number_of_elem] = {NULL};

enum {kCOUNTER_PIN_2_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_PIN_2_BASE - 1)

/**
 * @brief Pin Subscriber
 * 
 * @param cthis pointer to @ref PinInterface_t 
 * @return true   if subscribe successful
 * @return false  error
 */
bool PinInterface_SubscribeIrq(PinInterface_t* cthis)
{
  if(cthis == NULL)
    return false;
  #ifdef USE_MACRO_SWITCH
  __auto_type indx = -1;
  PIN_IRQ_SWICH(cthis->hwpin,indx);
  #else
  __auto_type indx = _this_get_pin_indx(cthis->hwpin);
  #endif

  if( (indx >= 0)&&
      (hpinInter[indx] == NULL))
    hpinInter[indx] = cthis; 
  else 
    return false;
  return true;
}

enum {kCOUNTER_PIN_3_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_PIN_3_BASE - 1)


/**
 * @brief Pin unsubscribe
 * 
 * @param cthis pointer to @ref PinInterface_t 
 * @return true   if unsubscribe successful
 * @return false  error
 */
bool PinInterface_UnsubscribeIrq(PinInterface_t* cthis)
{
  
  #ifdef USE_MACRO_SWITCH
  __auto_type indx = -1;
    PIN_IRQ_SWICH(cthis->hwpin,indx);
  #else
  __auto_type indx = _this_get_pin_indx(cthis->hwpin);
  #endif
  
  if(indx < 0)  
    return false;
            
  if( ( indx<0 )||
      (hpinInter[indx]!=cthis))
    return false;
   
  hpinInter[indx] = NULL;
  
  return true; 
}


enum {kCOUNTER_PIN_4_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_PIN_4_BASE - 1)

/**
 * @brief Stm32 EXTI callback in non-blocking mode 
 * 
 * @param hpin pointer to @ref PIN_HandleTypeDef
 */
void  HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  #ifdef USE_MACRO_SWITCH
  __auto_type indx = -1;
    PIN_IRQ_SWICH(GPIO_Pin,indx);
  #else
  __auto_type indx = _this_get_pin_indx(GPIO_Pin);
  #endif

  if(indx < 0)  
    return;
  
  

  if(hpinInter[indx]->ExtClb != NULL) 
    hpinInter[indx]->ExtClb(hpinInter[indx]->ctx);
  
  #ifdef W_USE_RTOS
  if(hpinInter[indx]->sem != NULL)
    osSemaphoreRelease(hpinInter[indx]->sem);
  #endif
}





/**
 * @brief Pin enter critical stm32 wrapper
 * 
 * @param cthis pointer to @ref PinInterface_t obj
 */
void PinInterface_CRITICAL_enter(PinInterface_t* cthis)
{
  if(cthis->IRQn == PIN_INTERFACE_NO_CRITICAL)
    return;

  if((cthis->IRQnEnable = NVIC_GetEnableIRQ(cthis->IRQn)) == true)
    NVIC_DisableIRQ(cthis->IRQn);
}

/**
 * @brief Pin exit critical stm32 wrapper
 * 
 * @param cthis pointer to @ref PinInterface_t obj
 */
void PinInterface_CRITICAL_exit(PinInterface_t* cthis)
{
  if(cthis->IRQn == PIN_INTERFACE_NO_CRITICAL)
    return; 

  if(cthis->IRQnEnable)
    NVIC_EnableIRQ(cthis->IRQn);
}

/**
 * @brief Disable Pin IRQ 
 * 
 * @param[in] cthis pointer to @ref PinInterface_t obj
 */
void PinInterface_IRQ_Disable(PinInterface_t* cthis)
{
  NVIC_DisableIRQ(cthis->IRQn);
}


/**
 * @brief Enable Pin IRQ 
 * 
 * @param[in] cthis pointer to @ref PinInterface_t obj
 */
void PinInterface_IRQ_Enable(PinInterface_t* cthis)
{
  NVIC_EnableIRQ(cthis->IRQn);
  NVIC_ClearPendingIRQ(cthis->IRQn);
}

enum {kCOUNTER_PIN_5_BASE = __COUNTER__};
#undef COUNTER_REL_INC
#define COUNTER_REL_INC(x) (x - kCOUNTER_PIN_5_BASE - 1)

#ifndef USE_MACRO_SWITCH
/**
 * @brief Get pin interface index
 * 
 * @param[in] pin number
 * @return int32_t -1 if index not found or >= 0  in found
 */
  static inline  int32_t _this_get_pin_indx(uint32_t pin)
  {
    switch(pin)
    {
      #ifdef ST_PIN0
        PIN_CASE(0);
      #endif
      #ifdef ST_PIN1
        PIN_CASE(1);
      #endif

      #ifdef ST_PIN2
        PIN_CASE(2);
      #endif

      #ifdef ST_PIN3
        PIN_CASE(3);
      #endif

      #ifdef ST_PIN4
        PIN_CASE(4);
      #endif
      #ifdef ST_PIN5
        PIN_CASE(5);
      #endif
      #ifdef ST_PIN6
        PIN_CASE(6);
      #endif
      #ifdef ST_PIN7
        PIN_CASE(7);    
      #endif
      #ifdef ST_PIN8
        PIN_CASE(8);
      #endif
      #ifdef ST_PIN9
        PIN_CASE(9);
      #endif
      #ifdef ST_PIN10
        PIN_CASE(10);
      #endif
      #ifdef ST_PIN11
        PIN_CASE(11);
      #endif
      #ifdef ST_PIN12
        PIN_CASE(12);
      #endif
      #ifdef ST_PIN13
        PIN_CASE(13);
      #endif
      #ifdef ST_PIN14
        PIN_CASE(14);
      #endif
      #ifdef ST_PIN15
        PIN_CASE(15);
      #endif
    }
    return -1;
  }
#endif

/** @} */ /*end of PinInterface group*/