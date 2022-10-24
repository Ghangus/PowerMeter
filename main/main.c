#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "IWifi.h"
#include "IHTTP_Client.h"
#include "IUDP_Client.h"
#include "IGPIO.h"

void app_main(void)
{
	printf("Starting Wifi scan!!!!\n");
	IWifi_fast_scan();
	IGPIO_read();
	while(1)
	{
		sleep(3);
		//printf("Sending UDP packet!\n");
		//udp_client_task();
		//IHttp_get();
		//printf("Done!\n");
	}
}
