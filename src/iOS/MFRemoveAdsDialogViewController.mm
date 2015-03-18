//
//  MFRemoveAdsDialogViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 15/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFRemoveAdsDialogViewController.h"
#import "MFIAPInterface.h"
#import "MFUIButton.h"
#import "MFUtils.h"

@interface MFRemoveAdsDialogViewController ()
@property (strong, nonatomic) IBOutlet UILabel *mRemoveAdsButtonLabel;
@property (strong, nonatomic) IBOutlet MFUIButton *mRemoveAdsButton;
@property (strong, nonatomic) IBOutlet MFUIButton *mRestorePurchaseButton;
@property (strong, nonatomic) IBOutlet UILabel *mNotConnectedLabel;
@property (strong, nonatomic) IBOutlet UILabel *mNotePermanentLabel;

@end

@implementation MFRemoveAdsDialogViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setupUI];
}

-(void)setupUI
{
    [self refreshUI];
    
    if ([SKPaymentQueue canMakePayments] && !self.mIAPManager.mIsSynchronized)
    {
        [self.mIAPManager synchronize];
        self.mIAPManager.mQueryDelegate = self;
    }
}

-(void)refreshUI
{
    if ([SKPaymentQueue canMakePayments] && self.mIAPManager.mIsSynchronized)
    {
        SKProduct *product = nil;
        int numProducts = (int)[self.mIAPManager.products count];
        for (int i = 0; i < numProducts; i++)
        {
            SKProduct *p = [self.mIAPManager.products objectAtIndex:i];
            if ([p.productIdentifier isEqualToString:@IAP_REMOVE_ADS])
            {
                product = p;
            }
        }
        
        NSString *priceStr = [MFUtils formatIAPPrice:product.price WithLocale:product.priceLocale];
        NSString *description = [NSString stringWithFormat:NSLocalizedString(@"remove_ads_description", @""), priceStr.UTF8String];
        [self.mRemoveAdsButtonLabel setText:description];
        
        self.mRemoveAdsButtonLabel.enabled = YES;
        self.mRemoveAdsButton.enabled = YES;
        self.mRestorePurchaseButton.enabled = YES;
        
        self.mNotConnectedLabel.hidden = YES;
        self.mNotePermanentLabel.hidden = NO;
    }
    else
    {
        [self.mRemoveAdsButtonLabel setText:@"----"];
        
        self.mRemoveAdsButton.enabled = NO;
        self.mRestorePurchaseButton.enabled = NO;
        
        self.mNotConnectedLabel.hidden = NO;
        self.mNotePermanentLabel.hidden = YES;
        
        self.mIAPManager.mQueryDelegate = self;
    }
}

/**
 This is called when a IAP query finished.  If successful,
 update the values of the IAP items and make the buttons
 enabled.
 **/
-(void)onQueryFinished:(BOOL)status
{
    [self refreshUI];
}

@end
