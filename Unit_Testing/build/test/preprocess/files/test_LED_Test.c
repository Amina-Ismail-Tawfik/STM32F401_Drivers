#include "../STM32F401CC/include/HAL/LED_cfg.h"
#include "../STM32F401CC/include/HAL/LED.h"
#include "build/test/mocks/mock_GPIO.h"
#include "C:/Users/adel/.local/share/gem/ruby/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"










typedef enum{

    utest_OK,

    utest_NOK,

    utest_ParameterError,

    utest_ConfigurationError,

 utest_Clock_SourceError,

    utest_NULL_PointerError

}utest_ErrorStatus_t;





void setUp(void)

{



}



void tearDown(void)

{



}







void test_PARAM_LEDSetStatus_1(void)

{

    GPIO_setPinValue_CMockIgnoreAndReturn(34, 0);

    uint8_t result = LED_SetStatus(LED_ONE,1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((0)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT8);

}





void test_PARAM_LEDSetStatus_2(void)

{

    GPIO_setPinValue_CMockIgnoreAndReturn(42, 0);

    uint8_t result = LED_SetStatus(LED_ONE,3);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((2)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT8);

}
