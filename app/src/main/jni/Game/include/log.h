//
// Created by bozie on 12.02.2016.
//

#ifndef TEST_LOG_H
#define TEST_LOG_H

#include <strings.h>
#include <android/log.h>

#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //TEST_LOG_H
