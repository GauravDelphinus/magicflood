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

@end

@implementation MFViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    [self initializeInAppPurchase];
}

-(void)initializeInAppPurchase
{
    initializeInAppInterface();
    
    addInAppProduct(IAP_ALACARTE_1, "First A-la-carte Item", "My very first IAP", true);
    addInAppProduct(IAP_ALACARTE_2, "Second A-la-carte item", "My very second IAP", true);
    addInAppProduct(IAP_ALACARTE_3, "Third A-la-carte item", "My very third IAP", true);
    addInAppProduct(IAP_ALACARTE_4, "Fourth A-la-carte item", "My very fourth IAP", true);
    addInAppProduct(IAP_ALACARTE_5, "Fifth A-la-carte item", "My very fifth IAP", true);
    addInAppProduct(IAP_ALACARTE_6, "Sixth A-la-carte item", "My very sixth IAP", true);
    addInAppProduct(IAP_COMBO_1, "Combo: 5 Hurdles!", "My very seventh IAP", false);
    addInAppProduct(IAP_COMBO_2, "Combo: 10 Hurdles!", "My very eighth IAP", false);
    addInAppProduct(IAP_COMBO_3, "Combo: 25 Hurdles!", "My very ninth IAP", false);
    addInAppProduct(IAP_COMBO_4, "Combo: 50 Hurdles!", "My very tenth IAP", false);
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
    
    controller.gameLevel = button.tag;
}

@end
