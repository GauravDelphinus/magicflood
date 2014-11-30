//
//  MFNativeLog.cpp
//  Magic Flood
//
//  Created by Anukrity Jain on 30/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#include <stdarg.h>
#include <stdio.h>
#ifdef __ANDROID
#include <android/log.h>
#endif
#include "MFNativeLog.h"

void logPrint(const char *tag, const char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsnprintf (buffer, 255, format, args);
    
    //do something with the error
        
    va_end (args);
    
#ifdef __ANDROID__
    __android_log_print(5, tag, "%s", buffer);
#else
    fprintf(stderr, "%s", buffer);
#endif
}
