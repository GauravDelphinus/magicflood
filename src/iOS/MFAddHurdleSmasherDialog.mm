//
//  MFAddHurdleSmasherDialogViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 5/4/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFAddHurdleSmasherDialog.h"
#import "MFGlobalInterface.h"

@interface MFAddHurdleSmasherDialog ()
@property (strong, nonatomic) IBOutlet UILabel *mAddHurdleSmasher1Label;
@property (strong, nonatomic) IBOutlet UILabel *mAddHurdleSmasher2Label;

@end

@implementation MFAddHurdleSmasherDialog

- (void)viewDidLoad {
    [super viewDidLoad];

    [self setupUI];
}

-(void) setupUI
{
    int addHurdleSmasher1NumCoins = getNumCoinsForHurdleSmasher(1);
    NSString *addHurdleSmasher1ButtonLabel = [NSString stringWithFormat:NSLocalizedString(@"num_coins_label", @""), addHurdleSmasher1NumCoins];
    [self.mAddHurdleSmasher1Label setText:addHurdleSmasher1ButtonLabel];
    
    int addHurdleSmasher2NumCoins = getNumCoinsForHurdleSmasher(2);
    NSString *addHurdleSmasher2ButtonLabel = [NSString stringWithFormat:NSLocalizedString(@"num_coins_label", @""), addHurdleSmasher2NumCoins];
    [self.mAddHurdleSmasher2Label setText:addHurdleSmasher2ButtonLabel];
}

@end
