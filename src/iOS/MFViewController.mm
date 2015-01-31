//
//  MFViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import "MFViewController.h"
#import "MFGameViewController.h"
#import "MFIAPInterface.h"

@interface MFViewController ()
@property (strong, nonatomic) IBOutlet UIImageView *mLogoImageView;

@end

@implementation MFViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    [self initializeInAppPurchase];
    
    UIImage *logoImage = [UIImage imageNamed:@"iOS/iPhone/ic_logo_big"];
    [self.mLogoImageView initWithImage:logoImage];
}

-(void)initializeInAppPurchase
{
    addInAppProduct(IAP_REMOVE_ADS, "Remove Ads", "Remove Ads", "0", "0", false);
    addInAppProduct(IAP_COINS_FIRST, "Add 500 Coins", "Add 500 Coins", "0", "0",  false);
    addInAppProduct(IAP_COINS_SECOND, "Add 1000 Coins", "Add 1000 Coins", "0", "0",  false);
    addInAppProduct(IAP_COINS_THIRD, "Add 2500 Coins", "Add 2500 Coins", "0", "0",  false);
    addInAppProduct(IAP_COINS_FOURTH, "Add 5000 Coins", "Add 5000 Coins", "0", "0",  false);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/**
 Called when the view controller is about to load the MFGameViewController
 **/
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    UIButton *button = (UIButton *)sender;
    MFGameViewController *controller = (MFGameViewController *)segue.destinationViewController;
    
    //controller.gameLevel = button.tag;
    controller.gameLevel = 33;
}

@end
