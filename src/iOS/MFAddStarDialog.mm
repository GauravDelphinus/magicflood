//
//  MFAddStarDialog.m
//  Magic Flood
//
//  Created by Anukrity Jain on 5/4/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFAddStarDialog.h"
#import "MFGlobalInterface.h"

@interface MFAddStarDialog ()
@property (strong, nonatomic) IBOutlet UILabel *mAddStar1Label;
@property (strong, nonatomic) IBOutlet UILabel *mAddStar2Label;

@end

@implementation MFAddStarDialog

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setupUI];
}

-(void) setupUI
{
    int addStar1NumCoins = getNumCoinsForStar(1);
    NSString *addStar1ButtonLabel = [NSString stringWithFormat:NSLocalizedString(@"num_coins_label", @""), addStar1NumCoins];
    [self.mAddStar1Label setText:addStar1ButtonLabel];
    
    int addStar2NumCoins = getNumCoinsForStar(2);
    NSString *addStar2ButtonLabel = [NSString stringWithFormat:NSLocalizedString(@"num_coins_label", @""), addStar2NumCoins];
    [self.mAddStar2Label setText:addStar2ButtonLabel];
}

@end
