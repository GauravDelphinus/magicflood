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

@interface MFAddCoinsDialog ()
@property (strong, nonatomic) IBOutlet UILabel *mPrice500CoinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *mPrice1000CoinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *mPrice2500CoinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *mPrice5000CoinsLabel;
@property (strong, nonatomic) IBOutlet MFUIButton *m500CoinsButton;

@property (strong, nonatomic) IBOutlet MFUIButton *m1000CoinsButton;
@property (strong, nonatomic) IBOutlet MFUIButton *m2500CoinsButton;
@property (strong, nonatomic) IBOutlet MFUIButton *m5000CoinsButton;
@property (strong, nonatomic) IBOutlet UILabel *mConnectionProblemLabel;

@end

@implementation MFAddCoinsDialog

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    if ([SKPaymentQueue canMakePayments] && self.mIAPManager.mIsSynchronized)
    {
        SKProduct *product500Coins = nil, *product1000Coins = nil, *product2500Coins = nil, *product5000Coins = nil;
        int numProducts = [self.mIAPManager.products count];
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
        
        [self.mPrice500CoinsLabel setText:[self formatIAPPrice:product500Coins.price WithLocale:product500Coins.priceLocale]];
        [self.mPrice1000CoinsLabel setText:[self formatIAPPrice:product1000Coins.price WithLocale:product1000Coins.priceLocale]];
        [self.mPrice2500CoinsLabel setText:[self formatIAPPrice:product2500Coins.price WithLocale:product2500Coins.priceLocale]];
        [self.mPrice5000CoinsLabel setText:[self formatIAPPrice:product5000Coins.price WithLocale:product5000Coins.priceLocale]];
        
        self.m5000CoinsButton.enabled = YES;
        self.m1000CoinsButton.enabled = YES;
        self.m2500CoinsButton.enabled = YES;
        self.m5000CoinsButton.enabled = YES;
        
        self.mConnectionProblemLabel.hidden = YES;
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
    }
}

-(NSString *)formatIAPPrice:(NSNumber *)price WithLocale:(NSLocale *)locale
{
    NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
    [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
    [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [numberFormatter setLocale:locale];
    NSString *formattedPrice = [numberFormatter stringFromNumber:price];
    
    return formattedPrice;
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
