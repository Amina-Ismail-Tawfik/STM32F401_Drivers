#include "../STM32F401CC/include/HAL/LED_cfg.h"
#include "../STM32F401CC/include/HAL/LED.h"
#include "build/test/mocks/mock_GPIO.h"
#include "C:/Users/adel/.local/share/gem/ruby/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"










int8_t LED_THREE=3;

void setUp(void)

{



}



void tearDown(void)

{



}







void test_LEDSetStatus_1(void)

{

    GPIO_setPinValue_CMockIgnoreAndReturn(25, 0);

    uint8_t result = LED_SetStatus(LED_THREE,1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((2)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT8);

}





void test_LEDSetStatus_2(void)

{

    GPIO_setPinValue_CMockIgnoreAndReturn(33, 0);

    uint8_t result = LED_SetStatus(LED_ONE,LED_THREE);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT8 )((2)), (UNITY_INT)(UNITY_INT8 )((result)), (

   ((void *)0)

   ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT8);

}
