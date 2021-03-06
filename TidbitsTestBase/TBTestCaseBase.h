//
//  TBTestCaseBase.h
//  Tidbits
//
//  Created by Ewan Mellor on 10/9/13.
//  Copyright (c) 2013 Tipbit, Inc.
//

// XCTAssertEqualStrings is derived from STAssertEqualStrings in:
//
//  GTMSenTestCase.h
//
//  Copyright 2007-2008 Google Inc.
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

#import <XCTest/XCTest.h>

#import "TBTestHelpers.h"


// Set this to 0 to skip tests that require a network.
#define INCLUDE_NETWORKED_TESTS 1

#if INCLUDE_NETWORKED_TESTS
#define NETWORKED_TEST(__name) __name
#else
#define NETWORKED_TEST(__name) skip ## __name
#endif


// Generates a failure when string a1 is not equal to string a2. This call
// differs from STAssertEqualObjects in that strings that are different in
// composition (precomposed vs decomposed) will compare equal if their final
// representation is equal.
// ex O + umlaut decomposed is the same as O + umlaut composed.
//  Args:
//    a1: string 1
//    a2: string 2
//    description: A format string as in the printf() function. Can be nil or
//                 an empty string but must be present.
//    ...: A variable number of arguments to the format string. Can be absent.

#if __clang_major__ >= 6

#define XCTAssertEqualStrings(a1, a2, format...) \
    do { \
        @try { \
            id a1value = (a1); \
            id a2value = (a2); \
            if (a1value == a2value) continue; \
            if ([a1value isKindOfClass:[NSString class]] && \
                [a2value isKindOfClass:[NSString class]] && \
                [a1value compare:a2value options:(NSStringCompareOptions)0] == NSOrderedSame) continue; \
            _XCTRegisterFailure(self, _XCTFailureDescription(_XCTAssertion_EqualObjects, 0, @#a1, @#a2, a1value, a2value), format); \
        } \
        @catch (_XCTestCaseInterruptionException *interruption) { [interruption raise]; } \
        @catch (NSException *exception) { \
            _XCTRegisterFailure(self, _XCTFailureDescription(_XCTAssertion_EqualObjects, 1, @#a1, @#a2, [exception reason]), format); \
        } \
        @catch (...) { \
            _XCTRegisterFailure(self, _XCTFailureDescription(_XCTAssertion_EqualObjects, 2, @#a1, @#a2), format); \
        } \
    } while(0)

#define XCTAssertNotEqualStrings(a1, a2, format...) \
    do { \
    @try { \
        id a1value = (a1); \
        id a2value = (a2); \
        if (a1value == a2value) continue; \
        if ([a1value isKindOfClass:[NSString class]] && \
            [a2value isKindOfClass:[NSString class]] && \
            [a1value compare:a2value options:(NSStringCompareOptions)0] != NSOrderedSame) continue; \
        _XCTRegisterFailure(self, _XCTFailureDescription(_XCTAssertion_NotEqualObjects, 0, @#a1, @#a2, a1value, a2value), format); \
    } \
    @catch (_XCTestCaseInterruptionException *interruption) { [interruption raise]; } \
    @catch (NSException *exception) { \
        _XCTRegisterFailure(self, _XCTFailureDescription(_XCTAssertion_NotEqualObjects, 1, @#a1, @#a2, [exception reason]), format); \
    } \
    @catch (...) { \
        _XCTRegisterFailure(self, _XCTFailureDescription(_XCTAssertion_NotEqualObjects, 2, @#a1, @#a2), format); \
    } \
} while(0)


#else

#define XCTAssertEqualStrings(a1, a2, format...) \
    do { \
        @try { \
            id a1value = (a1); \
            id a2value = (a2); \
            if (a1value == a2value) continue; \
            if ([a1value isKindOfClass:[NSString class]] && \
                [a2value isKindOfClass:[NSString class]] && \
                [a1value compare:a2value options:(NSStringCompareOptions)0] == NSOrderedSame) continue; \
            _XCTRegisterFailure(_XCTFailureDescription(_XCTAssertion_EqualObjects, 0, @#a1, @#a2, a1value, a2value),format); \
        } \
        @catch (id exception) { \
            _XCTRegisterFailure(_XCTFailureDescription(_XCTAssertion_EqualObjects, 1, @#a1, @#a2, [exception reason]),format); \
        } \
    } while(0)

#define XCTAssertNotEqualStrings(a1, a2, format...) \
    do { \
        @try { \
        id a1value = (a1); \
        id a2value = (a2); \
        if (a1value == a2value) continue; \
        if ([a1value isKindOfClass:[NSString class]] && \
            [a2value isKindOfClass:[NSString class]] && \
            [a1value compare:a2value options:(NSStringCompareOptions)0] != NSOrderedSame) continue; \
        _XCTRegisterFailure(_XCTFailureDescription(_XCTAssertion_NotEqualObjects, 0, @#a1, @#a2, a1value, a2value),format); \
        } \
        @catch (id exception) { \
        _XCTRegisterFailure(_XCTFailureDescription(_XCTAssertion_NotEqualObjects, 1, @#a1, @#a2, [exception reason]),format); \
        } \
    } while(0)

#endif


/**
 * Redefine _XCTRegisterFailure so that we can log to Lumberjack.
 */
#undef _XCTRegisterFailure
#define _XCTRegisterFailure(test, condition, ...) \
({ \
    NSString * s = [NSString stringWithFormat:@"" __VA_ARGS__]; \
    NSLog(@"%@ %@ - %@", self, condition, s); \
    _XCTFailureHandler(test, YES, __FILE__, __LINE__, condition, @"" __VA_ARGS__); \
})


/**
 * Redefine DLog so that we include the test name as a prefix to each message.
 */
#undef DLog
#define DLog(__fmt, ...) LOG_C_MAYBE(LOG_ASYNC_DEBUG, LOG_LEVEL_DEBUG, LOG_FLAG_DEBUG, 0, _LoggingMacrosPrefix @"%@ " __fmt, self, ##__VA_ARGS__)


@interface TBTestCaseBase : XCTestCase


/**
 * Call [self loadJSONFromBundle:resourceName], assert that the result is an NSDictionary, and return it.
 */
-(NSDictionary*)loadJSONDictFromBundle:(NSString*)resourceName;


/**
 * Load <resourceName>.json from this class's bundle, and parse it as a JSON object.
 * Assert that the load and parse succeeded.
 */
-(id)loadJSONFromBundle:(NSString*)resourceName;


@end
