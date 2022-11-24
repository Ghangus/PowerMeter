#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "ISleepManager.h"
#include "SleepManager.h"

const int wakeup_gpio_num = GPIO_INPUT_IO_0;
const int wakeup_level = 1;

void ISleepManager_Init()
{

}

void ISleepManager_Start()
{
    gpio_config_t config =
    {
            .pin_bit_mask = BIT64(wakeup_gpio_num),
            .mode = GPIO_MODE_INPUT
    };

    ESP_ERROR_CHECK(gpio_config(&config));
    gpio_wakeup_enable(wakeup_gpio_num,
            wakeup_level == 0 ? GPIO_INTR_LOW_LEVEL : GPIO_INTR_HIGH_LEVEL);
}

void ISleepManager_Sleep(void)
{
    esp_sleep_enable_timer_wakeup(2000000);
    esp_sleep_enable_gpio_wakeup();

    /* Wait until GPIO goes high */
    if (gpio_get_level(wakeup_gpio_num) == wakeup_level)
    {
    	printf("Waiting for GPIO%d to go high...\n", wakeup_gpio_num);
    	while (gpio_get_level(wakeup_gpio_num) == wakeup_level)
    	{
    		vTaskDelay(pdMS_TO_TICKS(10));
    	}
    }

    printf("Entering light sleep\n");
    /* To make sure the complete line is printed before entering sleep mode,
     * need to wait until UART TX FIFO is empty:
     */
    uart_wait_tx_idle_polling(CONFIG_ESP_CONSOLE_UART_NUM);

    /* Get timestamp before entering sleep */
    int64_t t_before_us = esp_timer_get_time();

    /* Enter sleep mode */
    esp_light_sleep_start();
    /* Execution continues here after wakeup */

    /* Get timestamp after waking up from sleep */
    int64_t t_after_us = esp_timer_get_time();

    /* Determine wake up reason */
    const char* wakeup_reason;
    switch (esp_sleep_get_wakeup_cause()) {
        case ESP_SLEEP_WAKEUP_TIMER:
            wakeup_reason = "timer";
            break;
        case ESP_SLEEP_WAKEUP_GPIO:
            wakeup_reason = "pin";
            break;
        default:
            wakeup_reason = "other";
            break;
    }

    printf("Returned from light sleep, reason: %s, t=%lld ms, slept for %lld ms\n",
            wakeup_reason, t_after_us / 1000, (t_after_us - t_before_us) / 1000);
}
