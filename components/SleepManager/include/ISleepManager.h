#ifndef ISLEEP_MANAGER_H_
#define ISLEEP_MANAGER_H_

#define GPIO_INPUT_IO_0     5
#define CONFIG_ESP_CONSOLE_UART_NUM 0

void ISleepManager_Init();
void ISleepManager_Start();

void ISleepManager_Sleep(void);

#endif /* ISLEEP_MANAGER_H_ */
