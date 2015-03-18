//
//  MFIAPPurchaseFailedDialogViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 18/3/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFIAPPurchaseFailedDialogViewController.h"

@interface MFIAPPurchaseFailedDialogViewController ()
@property (strong, nonatomic) IBOutlet UILabel *mDescriptionLabel;

@end

@implementation MFIAPPurchaseFailedDialogViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    [self setupUI];
}

-(void)setupUI
{
    //set the description label
    if (self.data > 0)
    {
        NSError *error = (NSError *)self.data;
        NSString *errorCodeStr;
        switch (error.code)
        {
            case SKErrorClientInvalid:
                errorCodeStr = NSLocalizedString(@"iap_purchase_failed_error_SKErrorClientInvalid", @"");
                break;
            case SKErrorPaymentInvalid:
                errorCodeStr = NSLocalizedString(@"iap_purchase_failed_error_SKErrorPaymentInvalid", @"");
                break;
            case SKErrorPaymentNotAllowed:
                errorCodeStr = NSLocalizedString(@"iap_purchase_failed_error_SKErrorPaymentNotAllowed", @"");
                break;
            case SKErrorStoreProductNotAvailable:
                errorCodeStr = NSLocalizedString(@"iap_purchase_failed_error_SKErrorStoreProductNotAvailable", @"");
                break;
            case SKErrorUnknown:
            default:
                errorCodeStr = NSLocalizedString(@"iap_purchase_failed_error_SKErrorUnknown", @"");
                break;
        }
        
        NSString *title = [NSString stringWithFormat:NSLocalizedString(@"iap_purchase_failed_dialog_description_dynamic", @""), [errorCodeStr UTF8String],[error.localizedDescription UTF8String]];
        [self.mDescriptionLabel setText:title];
    }
    else
    {
        NSString *title = NSLocalizedString(@"iap_purchase_failed_dialog_description_static", @"");
        [self.mDescriptionLabel setText:title];
    }
}

@end
