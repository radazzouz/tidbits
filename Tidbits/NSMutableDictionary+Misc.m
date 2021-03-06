//
//  NSMutableDictionary+Misc.m
//  TBClientLib
//
//  Created by Ewan Mellor on 5/2/13.
//  Copyright (c) 2013 Tipbit, Inc. All rights reserved.
//

#import "NSMutableDictionary+Misc.h"

@implementation NSMutableDictionary (Misc)

-(void) addIfSet:(id)value forKey:(id<NSCopying>)key {
    if (value != nil)
        [self setObject:value forKey:key];
}

-(void) addIfSetIn:(NSDictionary*)source forKey:(id<NSCopying>)key {
    [self addIfSet:source[key] forKey:key];
}

-(void) addKeyIfSet:(id<NSCopying>)key value:(id)value {
    if (value != nil)
        [self setObject:value forKey:key];
}

-(void)mergeLeft:(NSDictionary *)dict {
    [dict enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
        self[key] = obj;
    }];
}


-(BOOL)removeEntriesPassingTest:(BOOL (^)(id, id, BOOL *))predicate {
    NSSet * to_remove = [self keysOfEntriesPassingTest:predicate];
    if (to_remove.count > 0) {
        [self removeObjectsForKeys:[to_remove allObjects]];
        return YES;
    }
    else {
        return NO;
    }
}


@end
