//
//  NSDictionary+Map.h
//  TBClientLib
//
//  Created by Ewan Mellor on 5/23/13.
//  Copyright (c) 2013 Tipbit, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDictionary (Map)

typedef id (^key_val_to_id_t)(id key, id val);

/*!
 * @abstract Create a new NSArray with the contents set to mapper(k, v) for each k,v pair in self.
 *
 * @discussion mapper may return nil, in which case no entry is added to the result
 * (i.e. the result will be shorter than self).
 */
-(NSArray*) map:(key_val_to_id_t)block;

@end