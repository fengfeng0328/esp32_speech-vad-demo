#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "driver/gpio.h"
#include "driver/i2s.h"
#include "../components/ac101_driver/AC101.h"
#include "../components/ac101_driver/recoder.h"
#include "../components/ac101_driver/uart.h"

#include "nvs_flash.h"
#include "sdkconfig.h"

#include "common_audio/vad/include/webrtc_vad.h"
#include "simple_vad.h"

#define CONFIG_AC101_I2S_DATA_IN_PIN 35

static void audio_recorder_AC101_init()
{
	AC101_init();

	i2s_config_t i2s_config = {
	        .mode = I2S_MODE_MASTER |I2S_MODE_RX | I2S_MODE_TX,
	        .sample_rate = 16000,
	        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
	        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,                           //1-channels
	        .communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
	        .dma_buf_count = 32,
	        .dma_buf_len = 32 *2,
	        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1                                //Interrupt level 1
	    };

	i2s_pin_config_t pin_config_rx = {
	        .bck_io_num = CONFIG_AC101_I2S_BCK_PIN,
	        .ws_io_num = CONFIG_AC101_I2S_LRCK_PIN,
	        .data_out_num = CONFIG_AC101_I2S_DATA_PIN,
	        .data_in_num = CONFIG_AC101_I2S_DATA_IN_PIN
	    };

	int reg_val = REG_READ(PIN_CTRL);
	REG_WRITE(PIN_CTRL, 0xFFFFFFF0);
	reg_val = REG_READ(PIN_CTRL);
	PIN_FUNC_SELECT(GPIO_PIN_REG_0, 1); //GPIO0 as CLK_OUT1

	/* 注册i2s设备驱动 */
	i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
	/* 设置i2s引脚 */
	i2s_set_pin(I2S_NUM_0, &pin_config_rx);
	/* 停止i2s设备 */
	i2s_stop(I2S_NUM_0);
}

//static void alexa__AC101_task(void *pvParameters)
//{
//	int recv_len=0;
//	int is_active;
//	int16_t data[FRAME_SIZE];	// FRAME_SIZE * 16bit/2
//
//	simple_vad *vad = simple_vad_create();	//simple_vad_free(vad);
//	if (vad == NULL) {
//		vTaskDelete(NULL);
//	}
//
//	i2s_start(I2S_NUM_0);
//	while(1)
//	{
//		recv_len=i2s_read_bytes(I2S_NUM_0,data,320,portMAX_DELAY);
//		is_active = process_vad(vad, data);
//		printf("%d \t",is_active);
//		i2s_write_bytes(I2S_NUM_0,data,recv_len,portMAX_DELAY);
//	}
//	i2s_stop(I2S_NUM_0);
//	simple_vad_free(vad);
//	vTaskDelete(NULL);
//}

/* 实际采集一定数据的时间(计算时间) < 说话人说话同等数据所花时间 */
static void esp32_vad_task(void *pvParameters)
{
	int recv_len = 0;
	int is_active = 0;
	int count = 0;
	int16_t data[FRAME_SIZE];		// FRAME_SIZE * 16bit/2
	int16_t data_del[FRAME_SIZE];

	simple_vad *vad = simple_vad_create();
	if (vad == NULL) {
		vTaskDelete(NULL);
	}
	QueueHandle_t data_que = NULL;
	data_que = xQueueCreate(VAD_TIME_TOTAL, sizeof(int16_t) * FRAME_SIZE);	// 625k内存

	i2s_start(I2S_NUM_0);
	printf("\nstart vad detection\n");
	while(1)
	{
		recv_len=i2s_read_bytes(I2S_NUM_0,data,sizeof(int16_t) * FRAME_SIZE,portMAX_DELAY);
		xQueueSend(data_que, data, portMAX_DELAY);
		if (uxQueueMessagesWaiting(data_que) == START_CACHE_TIME + 1)	// must +1
		{
			xQueueReceive(data_que,data_del,portMAX_DELAY);
		}
		is_active = process_vad(vad, data);
		printf("%d \t",is_active);
		if (is_active == 1) {
			count++;
			if (count == START_TIME) {		// 1s
				count = 0;
				goto status_1;
			}
		} else {
			count = 0;
		}
		i2s_write_bytes(I2S_NUM_0,data,recv_len,portMAX_DELAY);
	}
status_1:
	printf("\nTo prepare the recording %ds\n", (int)(VAD_TIME_TOTAL * 0.01));
	for (int i = 0; i < VAD_TIME_TOTAL-START_CACHE_TIME; i++)	// 0.01s * 2000 = 20s
	{
		recv_len=i2s_read_bytes(I2S_NUM_0,data,sizeof(int16_t) * FRAME_SIZE,portMAX_DELAY);
		xQueueSend(data_que, data, portMAX_DELAY);
		is_active = process_vad(vad, data);
		printf("%d \t", is_active);
		if (is_active == 0) {
			count++;
			if (count == END_TIME) {
				count = 0;
				goto status_2;
			}
		} else {
			count = 0;
		}
		i2s_write_bytes(I2S_NUM_0, data, recv_len, portMAX_DELAY);
	}
status_2:
	printf("\nplay recording\n");
	while(1)
	{
		if (uxQueueMessagesWaiting(data_que) == 0)
			break;
		else
		{
			xQueueReceive(data_que, data, portMAX_DELAY);
			i2s_write_bytes(I2S_NUM_0, data, recv_len, portMAX_DELAY);//recv_len=320
		}
	}
	printf("esp32_vad_task is over, thank you!\n");
	i2s_stop(I2S_NUM_0);
	vQueueDelete(data_que);
	simple_vad_free(vad);
	vTaskDelete(NULL);
}

void app_main() {
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES
			|| ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	audio_recorder_AC101_init();
//	xTaskCreatePinnedToCore(&alexa__AC101_task, "alexa__AC101_task", 8096, NULL,
//			2, NULL, 1);
	xTaskCreatePinnedToCore(&esp32_vad_task, "esp32_vad_task", 40000, NULL,
			2, NULL, 1);
}

