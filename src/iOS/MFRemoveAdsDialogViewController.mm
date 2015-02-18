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

@interface MFRemoveAdsDialogViewController ()
@property (strong, nonatomic) IBOutlet UILabel *mRemoveAdsButtonLabel;
@property (strong, nonatomic) IBOutlet MFUIButton *mRemoveAdsButton;
@property (strong, nonatomic) IBOutlet UILabel *mNotConnectedLabel;
@property (strong, nonatomic) IBOutlet UILabel *mNotePermanentLabel;

@end

@implementation MFRemoveAdsDialogViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    if ([SKPaymentQueue canMakePayments] && self.mIAPManager.mIsSynchronized)
    {
        SKProduct *product = nil;
        int numProducts = [self.mIAPManager.products count];
        for (int i = 0; i < numProducts; i++)
        {
            SKProduct *p = [self.mIAPManager.products objectAtIndex:i];
            if ([p.productIdentifier isEqualToString:@IAP_REMOVE_ADS])
            {
                product = p;
            }
        }
        
        [self.mRemoveAdsButtonLabel setText:[self formatIAPPrice:product.price WithLocale:product.priceLocale]];
        
        self.mRemoveAdsButtonLabel.enabled = YES;
        self.mRemoveAdsButton.enabled = YES;
        
        self.mNotConnectedLabel.hidden = YES;
        self.mNotePermanentLabel.hidden = NO;
    }
    else
    {
        [self.mRemoveAdsButtonLabel setText:@"??"];
     
        self.mRemoveAdsButton.enabled = NO;
        
        self.mNotConnectedLabel.hidden = NO;
        self.mNotePermanentLabel.hidden = YES;
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
