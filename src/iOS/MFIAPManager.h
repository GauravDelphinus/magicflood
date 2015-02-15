//
//  MFIAPManager.h
//  Magic Flood
//
//  Created by Anukrity Jain on 14/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@protocol IAPPurchaseHandler
@required
-(void)onPurchaseFinished:(NSString *)pid WithStatus:(BOOL)status;
@end

@interface MFIAPManager : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>
-(void)initialize;
-(void)startPurchase:(NSString *)pid;
-(SKProduct *)getProductFromPID:(NSString *)pid;
-(void)restorePurchases;

@property BOOL mIsSynchronized; //synchronized with server
@property NSArray *products;
@property id <IAPPurchaseHandler> mPurchaseDelegate;

@end

