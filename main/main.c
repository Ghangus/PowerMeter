#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "IWifi.h"

void app_main(void)
{
	printf("Starting Wifi scan!!!!\n");
	IWifi_fast_scan();
	printf("Done!\n");

//    while (true) {
//        printf("Hello from app_main!\n");
//        sleep(1);
//    }
}
