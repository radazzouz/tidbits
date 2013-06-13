//
//  NSDictionary+Map.m
//  TBClientLib
//
//  Created by Ewan Mellor on 5/23/13.
//  Copyright (c) 2013 Tipbit, Inc. All rights reserved.
//

#import "NSDictionary+Map.h"

@implementation NSDictionary (Map)

-(NSArray*) map:(key_val_to_id_t)mapper {
    NSMutableArray *result = [NSMutableArray arrayWithCapacity:self.count];
    [self enumerateKeysAndObjectsUsingBlock:^(id key, id val, BOOL *stop) {
        id new_obj = mapper(key, val);
        if (new_obj != nil)
            [result addObject: new_obj];
    }];
    return result;
}

@end
