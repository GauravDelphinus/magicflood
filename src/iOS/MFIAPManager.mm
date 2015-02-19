//
//  MFIAPManager.m
//  Magic Flood
//
//  Created by Anukrity Jain on 14/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFIAPManager.h"
#import "MFIAPInterface.h"
#import "MFGameConstants.h"

@implementation MFIAPManager

-(void)initialize
{
    //register as observe for payment requests
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    
    //load the bundled product list
    NSString *id_iap_remove_ads = @IAP_REMOVE_ADS;
    NSString *id_iap_coins_first = @ IAP_COINS_FIRST;
    NSString *id_iap_coins_second = @ IAP_COINS_SECOND;
    NSString *id_iap_coins_third = @ IAP_COINS_THIRD;
    NSString *id_iap_coins_fourth = @ IAP_COINS_FOURTH;
    self.products = [NSArray arrayWithObjects: id_iap_remove_ads, id_iap_coins_first, id_iap_coins_second,
                     id_iap_coins_third, id_iap_coins_fourth, nil];
    
    //query items
    [self queryItems];
}

/**
 Query the iTunes Store for the list of products available
 for IAP in this app.
 **/
-(void)queryItems
{
    SKProductsRequest *productsRequest = [[SKProductsRequest alloc]
                                          initWithProductIdentifiers:[NSSet setWithArray:self.products]];
    productsRequest.delegate = self;
    [productsRequest start];
}

/**
 Called when a product request is processed. 
 SKProductsRequestDelegate protocol method
 **/
- (void)productsRequest:(SKProductsRequest *)request
     didReceiveResponse:(SKProductsResponse *)response
{
    BOOL allIsWell = YES;
    
    for (NSString *invalidIdentifier in response.invalidProductIdentifiers) {
        for (int i = 0; i < [self.products count]; i++)
        {
            if ([[self.products objectAtIndex:i] isEqualToString:invalidIdentifier])
            {
                //something's wrong
                allIsWell = NO;
                break;
            }
        }
        
        if (!allIsWell)
        {
            break;
        }
    }
    
    if (!allIsWell)
    {
        return;
    }

    self.products = nil;
    self.products = [response.products copy];

    self.mIsSynchronized = YES;
}

/**
 Call iTunes API to start a purchase workflow
 **/
-(void)startPurchase:(NSString *)pid
{
    SKProduct *product = [self getProductFromPID:pid];
    if (product != nil)
    {
        SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:product];
        payment.quantity = 1;
        [[SKPaymentQueue defaultQueue] addPayment:payment];
    }
}

/**
 Revert a product from a PID in the list of products.
 **/
-(SKProduct *)getProductFromPID:(NSString *)pid
{
    int numProducts = [self.products count];
    for (int i = 0; i < numProducts; i++)
    {
        SKProduct *product = [self.products objectAtIndex:i];
        if ([product.productIdentifier isEqualToString: pid])
        {
            return product;
        }
    }
    
    return nil;
}

/**
 Callback called by the IAP subsystem on a change in status
 of an ongoing transaction.
 **/
- (void)paymentQueue:(SKPaymentQueue *)queue
 updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions) {
        switch (transaction.transactionState) {
                // Call the appropriate custom method for the transaction state.
            case SKPaymentTransactionStatePurchasing:
                break;
            case SKPaymentTransactionStateDeferred:
                break;
            case SKPaymentTransactionStateFailed:
                [self.mPurchaseDelegate onPurchaseFinished:transaction.payment.productIdentifier WithStatus:NO];
                
                //finish the transaction
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                break;
            case SKPaymentTransactionStatePurchased:
                [self.mPurchaseDelegate onPurchaseFinished:transaction.payment.productIdentifier WithStatus:YES];
                
                //finish the transaction
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                [self.mPurchaseDelegate onPurchaseFinished:transaction.payment.productIdentifier WithStatus:YES];
                
                //finish the transaction
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                break;
            default:
                // For debugging
                break;
        }
    }
}

/**
 Restore any existing purchases on this user's Apple ID
 **/
-(void)restorePurchases
{
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

/**
 Callback when a restore purchase transaction changes status.
 **/
- (void) paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue
{
    for (SKPaymentTransaction *transaction in queue.transactions)
    {
        NSString *productID = transaction.payment.productIdentifier;
        if ([productID isEqualToString:@IAP_REMOVE_ADS])
        {
            switch (transaction.transactionState) {
                case SKPaymentTransactionStateFailed:
                    [self.mPurchaseDelegate onPurchaseRestored:transaction.payment.productIdentifier WithStatus:NO];
                    break;
                case SKPaymentTransactionStatePurchased:
                case SKPaymentTransactionStateRestored:
                    //finish the transaction
                    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                    
                    //remove ads has been restored.  Update the preference
                    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@PREFERENCE_ADS_REMOVED];
                    
                    [self.mPurchaseDelegate onPurchaseRestored:transaction.payment.productIdentifier WithStatus:YES];
                    break;
            }
        }
    }
}

@end
