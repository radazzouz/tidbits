//
//  GTMCodeCovereageTestsXC.m
//
//  Copyright 2013 Google Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not
//  use this file except in compliance with the License.  You may obtain a copy
//  of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
//  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
//  License for the specific language governing permissions and limitations under
//  the License.
//

// This code exists for doing code coverage with Xcode and iOS.
// Please read through https://code.google.com/p/coverstory/wiki/UsingCoverstory
// for details.

// This file should be conditionally compiled into your test bundle
// when you want to do code coverage and are using the XCTest framework.

#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>

#import "NSUserDefaults+Misc.h"

#import "GTMCodeCoverageApp.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
@interface GTMCodeCoverageTests : XCTestObserver
@end
#pragma clang diagnostic pop

@implementation GTMCodeCoverageTests

#if GTM_USING_XCTEST

- (void)stopObserving {
  [super stopObserving];

  if (!is_enabled())
    return;

  // Call gtm_gcov_flush in the application executable unit.
  // Silence the warning that comes because gtm_gcov_flush is linked into the main app, not the test lib.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wselector"
  id application = [UIApplication sharedApplication];
  if ([application respondsToSelector:@selector(gtm_gcov_flush)]) {
    [application performSelector:@selector(gtm_gcov_flush)];
  }
  else {
      // When testing a library under XCTest, [UIApplication sharedApplication] is nil, so we have to do the flush ourselves.
      extern void __gcov_flush(void);
      __gcov_flush();
  }
#pragma clang diagnostic pop

  // Reset defaults back to what they should be.
  NSUserDefaults *defaults = [NSUserDefaults tb_standardUserDefaults];
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
  [defaults removeObjectForKey:XCTestObserverClassKey];
#pragma clang diagnostic pop
}

+ (void)load {
  if (!is_enabled())
    return;

  // Verify that all of our assumptions in [GTMCodeCoverageApp load] still stand
  NSString *selfClass = NSStringFromClass(self);
  BOOL mustExit = NO;
  if (![selfClass isEqual:@"GTMCodeCoverageTests"]) {
    NSLog(@"Can't change GTMCodeCoverageTests name to %@ without updating GTMCoverageApp",
          selfClass);
    mustExit = YES;
  }
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated"
  if (![GTMXCTestObserverClassKey isEqual:XCTestObserverClassKey]) {
    NSLog(@"Apple has changed %@ to %@", GTMXCTestObserverClassKey, XCTestObserverClassKey);
    mustExit = YES;
  }
#pragma clang diagnostic pop
  if (!NSClassFromString(GTMXCTestLogClass)) {
    NSLog(@"Apple has gotten rid of the log class %@", GTMXCTestLogClass);
    mustExit = YES;
  }
  if (mustExit) {
    exit(1);
  }
}

static bool is_enabled() {
  char* val = getenv("GTM_CODE_COVERAGE_ENABLED");
  return val && val[0] == '1';
}

#endif

@end
