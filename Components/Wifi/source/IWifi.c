/*
 * IWifi.c
 *
 *  Created on: 7 Oct 2022
 *      Author: Ghangus
 */

/* INCLUDE FILES */
#include "Wifi.h"
#include "IWifi.h"

void IWifi_fast_scan(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    Wifi_fast_scan();
}

