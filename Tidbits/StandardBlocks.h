//
//  StandardBlocks.h
//  Tidbits
//
//  Created by Ewan Mellor on 6/13/13.
//  Copyright (c) 2013 Tipbit, Inc. All rights reserved.
//

#import <UIKit/UIApplication.h>

#ifndef Tidbits_StandardBlocks_h
#define Tidbits_StandardBlocks_h

typedef void (^IdBlock)(id obj);
typedef void (^NSArrayBlock)(NSArray* array);
typedef void (^NSArrayNSErrorBlock)(NSArray* array, NSError* error);
typedef void (^NSDataBlock)(NSData* data);
typedef void (^NSDataNSErrorBlock)(NSData* data, NSError* error);
typedef void (^NSDictionaryBlock)(NSDictionary* dict);
typedef void (^NSErrorBlock)(NSError* error);
typedef void (^NSMutableArrayBlock)(NSMutableArray* array);
typedef void (^NSStringBlock)(NSString* str);
typedef void (^NSStringNSArrayBlock)(NSString* str, NSArray* array);
typedef void (^NSStringNSErrorBlock)(NSString* str, NSError* error);
typedef void (^NSString2Block)(NSString* str1, NSString* str2);
typedef void (^NSUIntegerBlock)(NSUInteger i);
typedef void (^UIBackgroundFetchResultBlock)(UIBackgroundFetchResult result);
typedef void (^VoidBlock)(void);

typedef id (^id_to_id_t)(id obj);
typedef void (^id_to_id_async_t)(id obj, IdBlock onSuccess);
typedef bool (^predicate_t)(id obj);

#endif
