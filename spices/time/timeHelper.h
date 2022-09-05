#ifndef ___TIMEHELPER_H___
#define ___TIMEHELPER_H___

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <glog/logging.h>
#include "systemHelper.h"

//使用select实现精确到1微秒(0.000001秒)的sleep
void sleep_us(unsigned int nusecs);

int sysNetTime( void );

#endif
