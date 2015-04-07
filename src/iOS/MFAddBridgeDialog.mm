//
//  MFAddBridgeDialog.m
//  Magic Flood
//
//  Created by Anukrity Jain on 5/4/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFAddBridgeDialog.h"
#import "MFGlobalInterface.h"

@interface MFAddBridgeDialog ()
@property (strong, nonatomic) IBOutlet UILabel *mAddBridge1Label;
@property (strong, nonatomic) IBOutlet UILabel *mAddBridge2Label;

@end

@implementation MFAddBridgeDialog

- (void)viewDidLoad {
    [super viewDidLoad];

    [self setupUI];
}

-(void) setupUI
{
    int addBridge1NumCoins = getNumCoinsForBridge(1);
    NSString *addBridge1ButtonLabel = [NSString stringWithFormat:NSLocalizedString(@"num_coins_label", @""), addBridge1NumCoins];
    [self.mAddBridge1Label setText:addBridge1ButtonLabel];
    
    int addBridge2NumCoins = getNumCoinsForBridge(2);
    NSString *addBridge2ButtonLabel = [NSString stringWithFormat:NSLocalizedString(@"num_coins_label", @""), addBridge2NumCoins];
    [self.mAddBridge2Label setText:addBridge2ButtonLabel];
}

@end
