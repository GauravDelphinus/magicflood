//
//  MFIAPManager.h
//  Magic Flood
//
//  Created by Anukrity Jain on 14/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>


@interface MFIAPManager : NSObject <SKProductsRequestDelegate>
-(void)initialize;

@property BOOL mIsSynchronized; //synchronized with server
@property NSArray *products;
@end
