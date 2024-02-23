#ifdef TEST

#include "unity.h"

#include "mock_GPIO.h"
#include "LED.h"

#include "LED_cfg.h"

int8_t LED_THREE=3;
void setUp(void)
{   
    
}

void tearDown(void)
{

}


/*Test Case 1 for LED_SetStatus*/
void test_LEDSetStatus_1(void)
{
    GPIO_setPinValue_IgnoreAndReturn(0);
    uint8_t result = LED_SetStatus(LED_THREE,LED_STAT_ON);
    TEST_ASSERT_EQUAL_INT8(2,result);
}

/*Test Case 2 for LED_SetStatus*/
void test_LEDSetStatus_2(void)
{
    GPIO_setPinValue_IgnoreAndReturn(0);
    uint8_t result = LED_SetStatus(LED_ONE,LED_THREE);
    TEST_ASSERT_EQUAL_INT8(2,result);
}

#endif // TEST
