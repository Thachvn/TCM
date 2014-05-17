//
//  Basement.h
//  TCApp
//
//  Created by Vu Ngoc Thach on 5/17/14.
//  Copyright (c) 2014 Vu Ngoc Thach. All rights reserved.
//

#ifndef TCApp_Basement_h
#define TCApp_Basement_h

#include <iostream>
#include <time.h>
#include <sys/time.h>

#define ___NDEBUG
class __object_base__ {
#ifdef ___NDEBUG
protected:
	class __debug_base_t__ {
	protected:
		std::string module_name; /*Name of class play as module*/
	public:
		__debug_base_t__(const char* module) {
			this->module_name = std::string(module).substr(0,
                                                           std::string(module).length() - 1);
		}
		virtual ~__debug_base_t__() {
		}
		void debug_log(const char* file_name, unsigned int line,
                       const char* func_name, const char* fmt, ...) {
			timespec tv;
			va_list args;
			char* allocatedBuffer;
            
			clock_gettime(CLOCK_MONOTONIC, &tv);
            
			va_start(args, fmt);
			int size = vasprintf(&allocatedBuffer, fmt, args);
			va_end(args);
            
			tv.tv_sec = tv.tv_sec % 1000000;
			tv.tv_nsec = (tv.tv_nsec / 1000) % 1000000;
			printf("[%6d.%06d](%s:%4d) %s::%s() %s", tv.tv_sec, tv.tv_nsec,
                   file_name, line, this->module_name.c_str(), func_name,
                   allocatedBuffer);
			free(allocatedBuffer);
		}
	};
#else
protected:
	class __debug_base_t__ {
		std::string module_name;
	public:
		__debug_base_t__(const char* module) {
			this->module_name = "";
		}
		virtual ~__debug_base_t__() {
		}
		void debug_log(const char* file_name, unsigned int line, const char* func_name, const char* fmt, ...) {
		}
	};
#endif
public:
	__debug_base_t__ *__debug_base__;
};


#endif
