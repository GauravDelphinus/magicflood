//
//  MFAddCoinsDialog.m
//  Magic Flood
//
//  Created by Anukrity Jain on 14/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFAddCoinsDialog.h"
#import "MFUIButton.h"
#import "MFIAPInterface.h"
#import "MFUtils.h"

@interface MFAddCoinsDialog ()
@property (strong, nonatomic) IBOutlet UILabel *mDescriptionLabel;

@property (strong, nonatomic) IBOutlet UILabel *mPrice500CoinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *mPrice1000CoinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *mPrice2500CoinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *mPrice5000CoinsLabel;

@property (strong, nonatomic) IBOutlet MFUIButton *m500CoinsButton;
@property (strong, nonatomic) IBOutlet MFUIButton *m1000CoinsButton;
@property (strong, nonatomic) IBOutlet MFUIButton *m2500CoinsButton;
@property (strong, nonatomic) IBOutlet MFUIButton *m5000CoinsButton;

@property (strong, nonatomic) IBOutlet UILabel *mConnectionProblemLabel;
@property (strong, nonatomic) IBOutlet UILabel *mConsumableNoteLabel;

@end

@implementation MFAddCoinsDialog

- (void)viewDidLoad {
    [super viewDidLoad];

    [self setupUI];
}

-(void)setupUI
{
    //set the description label
    if (self.data > 0)
    {
        //there's a shortfall, so use the appropriate string
        NSString *title = [NSString stringWithFormat:NSLocalizedString(@"add_coins_dialog_description_dynamic", @""), self.data];
        [self.mDescriptionLabel setText:title];
    }
    else
    {
        NSString *title = NSLocalizedString(@"add_coins_dialog_description_static", @"");
        [self.mDescriptionLabel setText:title];
    }
    
    if ([SKPaymentQueue canMakePayments] && self.mIAPManager.mIsSynchronized)
    {
        SKProduct *product500Coins = nil, *product1000Coins = nil, *product2500Coins = nil, *product5000Coins = nil;
        int numProducts = (int)[self.mIAPManager.products count];
        for (int i = 0; i < numProducts; i++)
        {
            SKProduct *product = [self.mIAPManager.products objectAtIndex:i];
            if ([product.productIdentifier isEqualToString:@IAP_COINS_FIRST])
            {
                product500Coins = product;
            }
            else if ([product.productIdentifier isEqualToString:@IAP_COINS_SECOND])
            {
                product1000Coins = product;
            }
            else if ([product.productIdentifier isEqualToString:@IAP_COINS_THIRD])
            {
                product2500Coins = product;
            }
            else if ([product.productIdentifier isEqualToString:@IAP_COINS_FOURTH])
            {
                product5000Coins = product;
            }
        }
        
        [self.mPrice500CoinsLabel setText:[MFUtils formatIAPPrice:product500Coins.price WithLocale:product500Coins.priceLocale]];
        [self.mPrice1000CoinsLabel setText:[MFUtils formatIAPPrice:product1000Coins.price WithLocale:product1000Coins.priceLocale]];
        [self.mPrice2500CoinsLabel setText:[MFUtils formatIAPPrice:product2500Coins.price WithLocale:product2500Coins.priceLocale]];
        [self.mPrice5000CoinsLabel setText:[MFUtils formatIAPPrice:product5000Coins.price WithLocale:product5000Coins.priceLocale]];
        
        self.m5000CoinsButton.enabled = YES;
        self.m1000CoinsButton.enabled = YES;
        self.m2500CoinsButton.enabled = YES;
        self.m5000CoinsButton.enabled = YES;
        
        self.mConnectionProblemLabel.hidden = YES;
        self.mConsumableNoteLabel.hidden = NO;
    }
    else
    {
        [self.mPrice500CoinsLabel setText:@""];
        [self.mPrice1000CoinsLabel setText:@""];
        [self.mPrice2500CoinsLabel setText:@""];
        [self.mPrice5000CoinsLabel setText:@""];
        
        self.m5000CoinsButton.enabled = NO;
        self.m1000CoinsButton.enabled = NO;
        self.m2500CoinsButton.enabled = NO;
        self.m5000CoinsButton.enabled = NO;
        
        self.mConnectionProblemLabel.hidden = NO;
        self.mConsumableNoteLabel.hidden = YES;
    }
}

@end
