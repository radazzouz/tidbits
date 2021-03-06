//
//  InlineTiming.m
//  Tidbits
//
//  Created by Ewan Mellor on 10/6/13.
//  Copyright (c) 2013 Tipbit, Inc. All rights reserved.
//

#import "LoggingMacros.h"

#import "InlineTiming.h"


#if INLINE_TIMING_ENABLED

#define ESCAPE @"\033["
#define FG_RED ESCAPE @"fg200,0,0;"
#define FG_ORANGE ESCAPE @"fg255,100,0;"
#define FG_OFF ESCAPE @"fg;"

static NSString* fg_red;
static NSString* fg_orange;
static NSString* fg_off;


@implementation InlineTiming


+(void)initialize {
    if (self != [InlineTiming class])
        return;
    char *xcode_colors = getenv("XcodeColors");
    bool enabled = xcode_colors && 0 == strcmp(xcode_colors, "YES");
    fg_red = enabled ? FG_RED : @"";
    fg_orange = enabled ? FG_ORANGE : @"";
    fg_off = enabled ? FG_OFF : @"";
}


-(id)init:(NSUInteger)line {
    self = [super init];
    if (self) {
        index = 0;
        [self mark:line];
    }
    return self;
}


-(void)mark:(NSUInteger)line {
    assert(index < INLINE_TIMING_MAX);
    times[index] = [NSDate timeIntervalSinceReferenceDate];
    lines[index] = line;
    index++;
}


-(void)endWithBudget:(NSTimeInterval)budget func:(const char*)func line:(NSUInteger)line {
    [self mark:line];
    [InlineTiming log:func line:line times:times lines:lines count:index budget:budget];
}


+(void)log:(const char*)func line:(NSUInteger)line times:(const NSTimeInterval[])times lines:(const NSUInteger[])lines count:(NSUInteger)count budget:(NSTimeInterval)budget {
    if (count <= 1)
        return;

    NSTimeInterval total_time = times[count - 1] - times[0];
    if (total_time < budget)
        return;

    bool all_orange = (budget > 0.0 && total_time > (10.0 * budget));
    NSString* all_orange_on = all_orange ? fg_orange : @"";
    NSString* all_orange_off = all_orange ? fg_off : @"";

    if (count == 2) {
        NSLog(@"%@Timing for %s:%lu: %lf%@", all_orange_on, func, (unsigned long)line, times[1] - times[0], all_orange_off);
        return;
    }

    NSTimeInterval deltas[INLINE_TIMING_MAX];
    NSTimeInterval max_delta = 0;
    NSUInteger max_line = 0;
    NSTimeInterval previous = times[0];
    for (NSUInteger i = 1; i < count; i++) {
        NSTimeInterval time = times[i];
        NSTimeInterval delta = time - previous;
        deltas[i] = delta;
        previous = time;
        if (delta > max_delta) {
            max_delta = delta;
            max_line = lines[i];
        }
    }

    NSMutableString* str = [NSMutableString string];
    for (NSUInteger i = 1; i < count; i++) {
        NSTimeInterval delta = deltas[i];
        bool is_max = max_delta - delta < 0.001;
        if (is_max)
            [str appendString:fg_red];
        [str appendFormat:@" %lf", delta];
        if (is_max)
            [str appendString:all_orange ? fg_orange : fg_off];
    }

    NSLog(@"%@Timings for %s:%lu:%@ = %lf; max of %lf(%0.2lf%%) at line %lu%@", all_orange_on, func, (unsigned long)line, str, total_time, max_delta, 100 * max_delta / total_time, (unsigned long)max_line, all_orange_off);
}

@end

#endif
