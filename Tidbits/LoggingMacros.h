//
//  LoggingMacros.h
//  TBClientLib
//
//  Created by Ewan Mellor on 5/10/13.
//  Copyright (c) 2013 Tipbit, Inc. All rights reserved.
//

#ifndef Tidbits_LoggingMacros_h
#define Tidbits_LoggingMacros_h

#include <Lumberjack/DDLog.h>

#import "NSThread+Misc.h"


//undefine the lumberjack defaults
#undef LOG_FLAG_ERROR
#undef LOG_FLAG_WARN
#undef LOG_FLAG_USER
#undef LOG_FLAG_INFO
#undef LOG_FLAG_DEBUG
#undef LOG_FLAG_VERBOSE

#undef LOG_LEVEL_ERROR
#undef LOG_LEVEL_WARN
#undef LOG_LEVEL_USER
#undef LOG_LEVEL_INFO
#undef LOG_LEVEL_DEBUG
#undef LOG_LEVEL_VERBOSE

#undef LOG_ERROR
#undef LOG_WARN
#undef LOG_USER
#undef LOG_INFO
#undef LOG_DEBUG
#undef LOG_VERBOSE

#undef DDLogError
#undef DDLogWarn
#undef DDLogUser
#undef DDLogInfo
#undef DDLogDebug
#undef DDLogVerbose

#undef DDLogCError
#undef DDLogCWarn
#undef DDLogCInfo
#undef DDLogCDebug
#undef DDLogCVerbose

// Now define everything how we want it

#define LOG_FLAG_FATAL   (1 << 0)  // 0...000001
#define LOG_FLAG_ERROR   (1 << 1)  // 0...000010
#define LOG_FLAG_WARN    (1 << 2)  // 0...000100
#define LOG_FLAG_USER    (1 << 3)  // 0...001000
#define LOG_FLAG_INFO    (1 << 4)  // 0...010000
#define LOG_FLAG_DEBUG   (1 << 5)  // 0...100000
#define LOG_FLAG_VERBOSE (1 << 6)  // 0..1000000

#define LOG_LEVEL_FATAL   (LOG_FLAG_FATAL)                       // 0...000001
#define LOG_LEVEL_ERROR   (LOG_FLAG_ERROR  | LOG_LEVEL_FATAL )   // 0...000011
#define LOG_LEVEL_WARN    (LOG_FLAG_WARN   | LOG_LEVEL_ERROR )   // 0...000111
#define LOG_LEVEL_USER    (LOG_FLAG_USER   | LOG_LEVEL_WARN  )   // 0...001111
#define LOG_LEVEL_INFO    (LOG_FLAG_INFO   | LOG_LEVEL_USER  )   // 0...011111
#define LOG_LEVEL_DEBUG   (LOG_FLAG_DEBUG  | LOG_LEVEL_INFO  )   // 0...111111
#define LOG_LEVEL_VERBOSE (LOG_FLAG_VERBOSE| LOG_LEVEL_DEBUG )   // 0..1111111

#endif

#define NSLogError(__fmt, ...) LOG_C_MAYBE(LOG_ASYNC_ERROR, LOG_LEVEL_ERROR, LOG_FLAG_ERROR, 0, __fmt, ##__VA_ARGS__)
#define NSLogWarn(__fmt, ...) LOG_C_MAYBE(LOG_ASYNC_WARN, LOG_LEVEL_WARN, LOG_FLAG_WARN, 0, __fmt, ##__VA_ARGS__)
#define NSLogInfo(__fmt, ...) LOG_C_MAYBE(LOG_ASYNC_INFO, LOG_LEVEL_INFO, LOG_FLAG_INFO, 0, __fmt, ##__VA_ARGS__)

//our logging already prints out the function and line.
//#define NSLogUser(MSG, ...) NSLog((@"[U] %s:%d "MSG), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
//#define NSLogUser(MSG, ...) NSLog((@"[U] "MSG), ##__VA_ARGS__)
#define NSLogUser(__fmt, ...) LOG_C_MAYBE(LOG_ASYNC_ERROR, LOG_LEVEL_USER, LOG_FLAG_USER, 0, __fmt, ##__VA_ARGS__)


#define NSLog(__fmt, ...) LOG_C_MAYBE(LOG_ASYNC_INFO,    LOG_LEVEL_INFO, LOG_FLAG_INFO,    0, __fmt, ##__VA_ARGS__)

#if DEBUG
#define DLog(__fmt, ...) LOG_C_MAYBE(LOG_ASYNC_VERBOSE, LOG_LEVEL_VERBOSE, LOG_FLAG_VERBOSE, 0, __fmt, ##__VA_ARGS__)
#else
#define DLog(...)
#endif

#define ELog(__err) {if (__err) NSLogError(@"%@", __err)}

#if DEBUG
#define CALLSTACK [NSThread callStackSymbols]
#define CALLEDBY [NSThread callingFunction]
#else
#define CALLSTACK @""
#define CALLEDBY @""
#endif
