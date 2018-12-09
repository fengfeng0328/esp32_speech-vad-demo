# esp32_baidu_tts
vad algorithm based on esp32 for mute detection

/* 基于ESP32平台的说话人识别静音检测VAD算法，已实现VAD检测与语音截取 */

Speaker recognition mute detection VAD algorithm based on ESP32 platform has realized VAD detection and voice interception


Hardware platform: Ai-Thinker ESP32-Aduio-Kit Audio Development Board

https://item.taobao.com/item.htm?spm=a1z10.5-c-s.w4002-16491566042.12.510625e7rCXkuY&id=578317054056


How to use Help:

1.To "make menuconfig" && "make -j2 flash monitor"

2.Speak to the microphone and realize voice interception


You can see the effect below

start vad detection

1 	1 	1 	1 	1 	1 	1 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	

To prepare the recording 20s

1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	0 	0 	0 	0 	0 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	1 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	

play recording

esp32_vad_task is over, thank you!


This vad algorithm can also properly adjust the sensitivity, good luck far away
