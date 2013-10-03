//
//  NSUserDefaults+PerUser.h
//  TBClientLib
//
//  Created by Nat Ballou on 9/26/13.
//  Copyright (c) 2013 Tipbit, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSUserDefaults (PerUser)

// Per user keys
-(NSString*)PUKey:(NSString*) key;
-(NSString*)PUKey:(NSString*) key user:(NSString*) TBUser;

// Per user Bool methods
-(BOOL)boolForPUKey:(NSString*)key;
-(BOOL)boolForPUKey:(NSString*)key defaultValue:(BOOL)defValue;
-(void)setBoolForPUKey:(BOOL)value forKey:(NSString*)key;

// Per user string methods
-(NSString*)stringForPUKey:(NSString*)key;
-(NSString*)stringForPUKey:(NSString*)key defaultValue:(NSString*)defValue;
-(void)setStringForPUKey:(NSString*)value forKey:(NSString*)key;

// Per user object methods
-(id)objectForPUKey:(NSString*)key;
-(void)setObjectForPUKey:(NSObject*)value forKey:(NSString*)key;
-(void)removeObjectForPUKey:(NSString*)key;

@end