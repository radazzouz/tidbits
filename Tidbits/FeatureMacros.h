//
//  FeatureMacros.h
//  Tidbits
//
//  Created by Ewan Mellor on 9/28/13.
//  Copyright (c) 2013 Tipbit, Inc. All rights reserved.
//

#ifndef Tidbits_FeatureMacros_h
#define Tidbits_FeatureMacros_h

#ifndef NSFoundationVersionNumber_iOS_7_1
#define NSFoundationVersionNumber_iOS_7_1 1047.25
#endif


#define IS_IPAD (UIDevice.currentDevice.userInterfaceIdiom == UIUserInterfaceIdiomPad)
#define IS_IPHONE5 ((UIScreen.mainScreen.bounds.size.height > 567) || (UIScreen.mainScreen.bounds.size.width > 567))
#define IS_IOS6 (floor(NSFoundationVersionNumber) <= NSFoundationVersionNumber_iOS_6_1)
#define IS_IOS7 (floor(NSFoundationVersionNumber) >= NSFoundationVersionNumber_iOS_6_1 && floor(NSFoundationVersionNumber) <= NSFoundationVersionNumber_iOS_7_1)
#define IS_IOS8 (floor(NSFoundationVersionNumber) >  NSFoundationVersionNumber_iOS_7_1)


#endif
