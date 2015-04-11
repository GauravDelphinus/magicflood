//
//  MFLifelinePlacementInfoDialog.m
//  Magic Flood
//
//  Created by Anukrity Jain on 11/4/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFLifelinePlacementInfoDialog.h"

@interface MFLifelinePlacementInfoDialog ()

@end

@implementation MFLifelinePlacementInfoDialog

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setupUI];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)setupUI
{
    [self.mMessage setText:self.strData];
}

@end
