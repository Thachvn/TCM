//
//  Obj_Debug.h
//  TCApp
//
//  Created by Vu Ngoc Thach on 5/17/14.
//  Copyright (c) 2014 Vu Ngoc Thach. All rights reserved.
//

#ifndef TCApp_Obj_Debug_h
#define TCApp_Obj_Debug_h

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <cxxabi.h>
#include <exception>
#include "utils.h"

/**Log levels
 * There are 6 log levels/options.
 * You can combine them to print the concerned messages.
 */

#define ___NDEBUG
#ifdef ___NDEBUG
#define DEBUG_LOG_NONE          (0)     /*Remove all debug print*/
#define DEBUG_LOG_ERROR         (1)     /*Messages explaining the reason of critical errors*/
#define DEBUG_LOG_INFO          (2)     /*Messages explaining process info for end-user*/
#define DEBUG_LOG_WARNING       (4)     /*Messages explaining potential error*/
#define DEBUG_LOG_TRACE         (8)     /*Messages explaining function trace*/
#define DEBUG_LOG_DETAIL        (16)    /*Messages explaining detail information for debug*/
#define DEBUG_LOG_MAX           (255)   /*Print all messages - max value*/

#define UTIL_LOG_LEVEL          (DEBUG_LOG_MAX)

#if UTIL_LOG_LEVEL > 0
#define UTIL_PRINT_LOG(level, fmt, args...) do {                                 \
if(UTIL_LOG_LEVEL & (level)) {                                           \
    __debug_base__->debug_log(__FILE__, __LINE__, __FUNCTION__, fmt, ## args);      \
}                                                                               \
} while(0)
#else
#define UTIL_PRINT_LOG(level, fmt, args...) do {                                 \
} while(0)
#endif

#define UTIL_ENTRY() do { \
if (UTIL_LOG_LEVEL & DEBUG_LOG_TRACE) \
do {                   \
    int __debug_base_t___temporary_int; \
    __debug_base__ = new __debug_base_t__(abi::__cxa_demangle(typeid(this).name(), 0, 0, &__debug_base_t___temporary_int)); \
    __debug_base__->debug_log(__FILE__, __LINE__, __FUNCTION__, "Entry\n"); \
} while (0);                                 \
else \
do {                   \
    int __debug_base_t___temporary_int; \
    __debug_base__ = new __debug_base_t__(abi::__cxa_demangle(typeid(this).name(), 0, 0, &__debug_base_t___temporary_int)); \
} while (0);                                 \
} while (0)


#else
#define DEBUG_LOG_NONE          (0)     /*Remove all debug print*/
#define DEBUG_LOG_ERROR         (1)     /*Messages explaining the reason of critical errors*/
#define DEBUG_LOG_INFO          (2)     /*Messages explaining process info for end-user*/
#define DEBUG_LOG_WARNING       (4)     /*Messages explaining potential error*/
#define DEBUG_LOG_TRACE         (8)     /*Messages explaining function trace*/
#define DEBUG_LOG_DETAIL        (16)    /*Messages explaining detail information for debug*/
#define DEBUG_LOG_MAX           (255)   /*Print all messages - max value*/

#define UTIL_LOG_LEVEL          (DEBUG_LOG_MAX)

#if UTIL_LOG_LEVEL > 0
#define UTIL_PRINT_LOG(level, fmt, args...) do {                                 \
if(UTIL_LOG_LEVEL & (level)) {                                           \
    util_debug_log(__FILE__, __LINE__, __FUNCTION__, fmt, ## args);      \
}                                                                               \
} while(0)
#else
#define UTIL_PRINT_LOG(level, fmt, args...) do {                                 \
} while(0)
#endif

#define UTIL_ENTRY() do { \
if (UTIL_LOG_LEVEL & DEBUG_LOG_TRACE) \
do {                   \
    util_debug_log(__FILE__, __LINE__, __FUNCTION__, "Entry\n"); \
} while (0);                                 \
} while (0)

void util_debug_log(const char* file_name, unsigned int line, const char* func_name, const char* fmt, ...) {
	timespec tv;
	va_list args;
	char* allocatedBuffer;
    
	clock_gettime(CLOCK_MONOTONIC, &tv);
    
	va_start(args, fmt);
	int size = vasprintf(&allocatedBuffer, fmt, args);
	va_end(args);
    
	tv.tv_sec = tv.tv_sec % 1000000;
	tv.tv_nsec = (tv.tv_nsec/1000) % 1000000;
	printf( "[%6d.%06d](%s:%4d) %s() %s",
           tv.tv_sec, tv.tv_nsec, file_name, line, func_name, allocatedBuffer );
	free(allocatedBuffer);
}
#endif

