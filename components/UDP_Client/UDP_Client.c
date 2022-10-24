#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
//#include "addr_from_stdin.h"
#include "include/IUDP_Client.h"

#if defined(CONFIG_EXAMPLE_IPV4)
#define HOST_IP_ADDR CONFIG_EXAMPLE_IPV4_ADDR
#elif defined(CONFIG_EXAMPLE_IPV6)
#define HOST_IP_ADDR CONFIG_EXAMPLE_IPV6_ADDR
#else
#define HOST_IP_ADDR "192.168.50.12"
#endif

#define PORT 6666

static const char *TAG = "example";
static const char *payload = "Emelie är min hoe";


void udp_client_task()
{
    char rx_buffer[128];
    char host_ip[] = HOST_IP_ADDR;
    int addr_family = 0;
    int ip_protocol = 0;


	struct sockaddr_in dest_addr;
	dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(PORT);
	addr_family = AF_INET;
	ip_protocol = IPPROTO_IP;

	int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
	if (sock < 0) {
		ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
		return;
	}
	ESP_LOGI(TAG, "Socket created, sending to %s:%d", HOST_IP_ADDR, PORT);


	int err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
	if (err < 0) {
		ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
		return;
	}
	ESP_LOGI(TAG, "Message sent");

	struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
	socklen_t socklen = sizeof(source_addr);
	int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);

	// Error occurred during receiving
	if (len < 0) {
		ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
		return;
	}
	// Data received
	else {
		rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
		ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
		ESP_LOGI(TAG, "%s", rx_buffer);
		if (strncmp(rx_buffer, "OK: ", 4) == 0) {
			ESP_LOGI(TAG, "Received expected message, reconnecting");
			return;
		}
	}


	if (sock != -1) {
		ESP_LOGE(TAG, "Shutting down socket and restarting...");
		shutdown(sock, 0);
		close(sock);
	}

}


