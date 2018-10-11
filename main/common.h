//
// Created by fu on 3/7/18.
//

#ifndef VAD_DEMO_COMMON_H
#define VAD_DEMO_COMMON_H

#include <stdint.h>



// MULTI = 1 2 3 webrtc vad可以设置分别为以10ms 20ms 30ms作为包
#define MULTI 1

// VAD 模式 Aggressiveness mode (0, 1, 2, or 3). 数值越大，判断越是粗略，连着的静音或者响声增多
#define WEBRTC_VAD_MODE 3

// 有声音的音频段，xxx 毫秒后，认为该音频段结束，不能为0
#define FILE_CUT_SILENCE_AFTER_ACTIVE_MS 500

// 静音的音频段，切分xxx毫秒给之后有声音的音频段
#define FILE_CUT_SILENCE_BEFORE_ACTIVE_MS 300

// 最小的音频切分长度，即每个切分后音频文件不少于这个时长，最后一个除外
#define FILE_CUT_MIN_MS  (10 * 1000)

// 最大的音频切分长度，即每个切分后音频文件不多于这个时长
#define FILE_CUT_MAX_MS  (60 * 1000)

// 16000 采样率固定，更改采样频率需要手动更新FRAME_SIZE
#define SAMPLE_RATE 16000

// 用于 period_format.h
#define PERIODS_SIZE_INITIED 100

/* 采样一帧数据的大小(即在10ms(20ms,30ms)内的采样次数) 10ms-->160; 20ms-->320; 30ms-->480;
 * 16000HZ * 10ms/1000 = 160
 * 16000HZ * 20ms/1000 = 320
 * 16000HZ * 30ms/1000 = 480 */
#define FRAME_SIZE (160 * MULTI)

#define CAL_FRAME_BY_FRAME(frame) (MULTI * frame * 10)

#define CAL_FRAME_BY_TIME(time) (time / (MULTI * 10))

// VAD 检测总次数   	0.01s(0.02s,0.03s) * 2000
#define VAD_TIME_TOTAL 2000

// VAD 触发前缓存次数 	0.01s(0.02s,0.03s) * 100
#define START_CACHE_TIME 100

// VAD 触发检测次数  	0.01s(0.02s,0.03s) * 50
#define START_TIME 50

// VAD 结束检测次数 	0.01s(0.02s,0.03s) * 100
#define END_TIME 100

/*
uint64_t inline CAL_FRAME_BY_FRAME(int frame){
    return MULTI * frame * 10;
};

int inline CAL_FRAME_BY_TIME(uint64_t time){
    return time / (MULTI * 10);
};
*/
#endif //VAD_DEMO_COMMON_H
