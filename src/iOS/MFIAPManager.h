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
-(void)onPurchaseFinished:(NSString *)pid WithStatus:(BOOL)status WithError:(NSError *)error;
-(void)onPurchaseRestored:(NSString *)pid WithStatus:(BOOL)status WithError:(NSError *)error;
@end

@protocol IAPQueryHandler
@required
-(void)onQueryFinished:(BOOL)status;
@end

@interface MFIAPManager : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver>
-(void)initialize;
-(void)startPurchase:(NSString *)pid;
-(SKProduct *)getProductFromPID:(NSString *)pid;
-(void)restorePurchases;
-(void)synchronize;

@property BOOL mIsSynchronized; //synchronized with server
@property NSArray *products;
@property id <IAPPurchaseHandler> mPurchaseDelegate;
@property id <IAPQueryHandler> mQueryDelegate;

@end

