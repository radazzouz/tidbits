//
//  NSUUID+Misc.m
//  Tidbits
//
//  Created by Ewan Mellor on 10/5/13.
//  Copyright (c) 2013 Tipbit, Inc. All rights reserved.
//

#import "NSData+Base64.h"

#import "NSUUID+Misc.h"


@implementation NSUUID (Misc)

-(NSString *)UUIDStringBase64url {
    unsigned char bytes[16];
    [self getUUIDBytes:bytes];
    NSData* data = [NSData dataWithBytesNoCopy:bytes length:16 freeWhenDone:NO];
    return [data base64urlEncodedString];
}

@end
