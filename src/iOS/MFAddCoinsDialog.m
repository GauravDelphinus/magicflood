//
//  MFAddCoinsDialog.m
//  Magic Flood
//
//  Created by Anukrity Jain on 14/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFAddCoinsDialog.h"

@interface MFAddCoinsDialog ()
@property (strong, nonatomic) IBOutlet UILabel *mPrice500CoinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *mPrice1000CoinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *mPrice2500CoinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *mPrice5000CoinsLabel;

@end

@implementation MFAddCoinsDialog

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self.mPrice500CoinsLabel setText:self.mPrice500Coins];
    [self.mPrice1000CoinsLabel setText:self.mPrice1000Coins];
    [self.mPrice2500CoinsLabel setText:self.mPrice2500Coins];
    [self.mPrice5000CoinsLabel setText:self.mPrice5000Coins];
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
