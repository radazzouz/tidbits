//
//  TBUserDefaults.h
//  Tidbits
//
//  Created by Ewan Mellor on 4/20/14.
//  Copyright (c) 2014 Tipbit, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 * TBUserDefaults is like NSUserDefaults except:
 * 1) the concept of per-user settings is built in;
 * 2) settings are separated by their desired protection level (in the sense of NSFileProtectionKey)
 *    and this class is able to handle the situation where the plist is inaccessible; and
 * 3) the API includes a default value to be returned if the setting is missing.
 *
 * NSUserDefaults is not used at all as part of the implementation.
 */
@interface TBUserDefaults : NSObject

/**
 * Equivalent to [TBUserDefaults userDefaultsForUser:user] where user is the last value that was set using [TBUserDefaults setUser].
 */
+(TBUserDefaults *)standardUserDefaults;

/**
 * @return A TBUserDefaults instance for use for settings that should be available when no-one is signed in.  Note that this is different
 * to [TBUserDefaults userDefaultsForUser:nil].
 */
+(TBUserDefaults *)userDefaultsForUnauthenticatedUser;

/**
 * @return A TBUserDefaults instance for the specified user.  If user is nil, you'll get an instance that returns the default for every
 * setting, and won't write anything.  To get a useful TBUserDefaults instance for when no-one is signed in, use
 * [TBUserDefaults userDefaultsForUnauthenticatedUser].
 */
+(TBUserDefaults *)userDefaultsForUser:(NSString *)user;

/**
 * @return The last value given to [NSUserDefaults setUser].
 * This includes reading it from [TBUserDefaults userDefaultsForUnauthenticatedUser] if necessary.  May be nil.
 */
+(NSString *)user;

+(NSString *)userType;

/**
 * Set the user that standardUserDefaults should use from now on.
 * This also saves the user in [TBUserDefaults userDefaultsForUnauthenticatedUser], with key = @"USER",
 * protection:NSFileProtectionNone so that it can be read the next time the app starts.
 *
 * @param user May be nil, for signing out.
 */
+(void)setUser:(NSString *)user;

+(void)setUserType:(NSString *)userType;

/**
 * Equivalent to [TBUserDefaults setUser:user]; [[TBUserDefaults userDefaultsForUnauthenticatedUser] synchronize].
 *
 * Note that this doesn't touch userType, so you can use it if you want to clear user but keep userType.
 */
+(void)setUserAndSynchronize:(NSString *)user;

/**
 * Equivalent to [TBUserDefaults setUser:user]; [TBUserDefaults setUserType:userType]; [[TBUserDefaults userDefaultsForUnauthenticatedUser] synchronize].
 */
+(void)setUserAndSynchronize:(NSString *)user type:(NSString *)type;

/**
 * @return YES if the given key has previously been registered through TBUserDefaultsRegisteredSettings.h.
 */
+(BOOL)isRegisteredSetting:(NSString*)key __attribute__((nonnull));

/**
 * @return An NSString array, yours to play with.  All the keys of all the registered settings.
 */
+(NSArray*)allRegisteredSettings;

/**
 * Write all changes to the plists for all instances immediately.
 */
+(BOOL)synchronizeAll;

/**
 * Write all changes to the plists immediately.
 */
-(BOOL)synchronize;

/**
 * Equivalent to [self objectForKey:key wasUnlocked:NULL].
 */
-(id)objectForKey:(NSString *)key __attribute__((nonnull));

/**
 * Look up a user default using the settings registered through TBUserDefaultsRegisteredSettings.h.
 */
-(id)objectForKey:(NSString *)key wasUnlocked:(BOOL *)wasUnlocked __attribute__((nonnull(1)));

/**
 * Set a user default using the settings registered through TBUserDefaultsRegisteredSettings.h.
 *
 * @param value May be nil, in which case this is equivalent to [self removeObjectForKey:key].
 * @return YES if this call was able to find the registered setting, read the old settings plist (i.e. the file was unlocked), and the write has been scheduled.
 */
-(BOOL)setObject:(id)value forKey:(NSString *)key __attribute__((nonnull(2)));

/**
 * Equivalent to setObject:forKey:, but parses the value from the given string, using the registered type
 * for that key (assuming NSString if this key is not registered).
 *
 * @param value May be nil or @"", in which case this is equivalent to [self removeObjectForKey:key].
 * If the registered type is BOOL, NSInteger, float, or double, may be anything that
 * NSString.{bool,integer,float,double}Value will handle.
 * If the registered type is NSNumber, may be anything that a lenient NSNumberFormatter will handle.
 * If the registered type is NSString, may be anything.
 * @return YES if this call was able to parse the given value, find the registered setting,
 * read the old settings plist (i.e. the file was unlocked), and the write has been scheduled.
 */
-(BOOL)setObjectFromString:(NSString *)value forKey:(NSString *)key __attribute__((nonnull(2)));

/**
 * Remove a value for a user default using the settings registered through TBUserDefaultsRegisteredSettings.h.
 * @return YES if this call was able to find the registered setting, read the old settings plist (i.e. the file was unlocked), and the write has been scheduled.
 */
-(BOOL)removeObjectForKey:(NSString *)key __attribute__((nonnull));

/**
 * Equivalent to [self objectForKey:key protection:protection defaultValue:def wasUnlocked:NULL].
 */
-(id)objectForKey:(NSString *)key protection:(NSString *)protection defaultValue:(id)def __attribute__((nonnull(1,2)));

/**
 * @param wasUnlocked An out parameter.  Will be set to NO if this call was unable to open the settings plist
 * because the file is locked or no user is signed in, or YES otherwise.  May be NULL.
 */
-(id)objectForKey:(NSString *)key protection:(NSString *)protection defaultValue:(id)def wasUnlocked:(BOOL *)wasUnlocked __attribute__((nonnull(1,2)));

/**
 * @param value May be nil, in which case this is equivalent to [self removeObjectForKey:key].
 * @return YES if this call was able to read the old settings plist (i.e. the file was unlocked) and the write has been scheduled.
 */
-(BOOL)setObject:(id)value forKey:(NSString *)key protection:(NSString *)protection __attribute__((nonnull(2,3)));

/**
 * @return YES if this call was able to read the old settings plist (i.e. the file was unlocked) and the write has been scheduled.
 */
-(BOOL)removeObjectForKey:(NSString *)key protection:(NSString *)protection __attribute__((nonnull));


#pragma mark Type-safe getters / setters

#define TBUSERDEFAULTS_TYPED(__t, __f, __F)                                                                                    \
-(__t)__f ## ForKey:(NSString *)key __attribute__((nonnull));                                                                  \
-(__t)__f ## ForKey:(NSString *)key wasUnlocked:(BOOL *)wasUnlocked __attribute__((nonnull(1)));                               \
-(__t)__f ## ForKey:(NSString *)key protection:(NSString *)protection defaultValue:(__t)def __attribute__((nonnull(1,2)));     \
-(void)set ## __F:(__t)value forKey:(NSString *)key __attribute__((nonnull(2)));                                               \
-(BOOL)set ## __F:(__t)value forKey:(NSString *)key protection:(NSString *)protection __attribute__((nonnull(2,3)));

TBUSERDEFAULTS_TYPED(NSArray *, array, Array)
TBUSERDEFAULTS_TYPED(NSDictionary *, dictionary, Dictionary)
TBUSERDEFAULTS_TYPED(NSNumber *, number, Number)
TBUSERDEFAULTS_TYPED(NSString *, string, String)
TBUSERDEFAULTS_TYPED(NSInteger, integer, Integer)
TBUSERDEFAULTS_TYPED(float, float, Float)
TBUSERDEFAULTS_TYPED(double, double, Double)
TBUSERDEFAULTS_TYPED(BOOL, bool, Bool)

#undef TBUSERDEFAULTS_TYPED


/**
 * @return NSString -> (NSString -> id NSMutableDictionary).  The outer key is the key for the setting.  The inner dictionary contains the
 * the following: @"key": the key for the setting, @"protection": its protection level, @"defaultValue": its default value,
 * @"value": its current value, @"context": one of @"user", @"unauth", or @"none" depending on the value of self.user, @"error": an error message.
 * @"defaultValue" will be omitted if it set to nil or has never been registered.  @"error" will be omitted if no error is detected with this setting.
 * @"value" will be omitted if the setting is registered but currently has no value.
 */
-(NSMutableDictionary *)toJSON;

/**
 * @return NSString -> (NSString -> id NSMutableDictionary).  The outer key is the key for the registered setting.  The inner dictionary contains the
 * the following: @"key": the key for the registered setting, @"protection": its protection level, @"defaultValue": its default value.  @"defaultValue" will
 * be omitted if it set to nil.
 */
+(NSMutableDictionary *)registeredSettingsToJSON;


@end
