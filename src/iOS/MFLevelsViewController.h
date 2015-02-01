//
//  MFLevelsViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 31/1/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MFLevelsViewController : UIViewController
{
    NSArray *mLevelButtons;
}
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton1;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton2;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton3;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton4;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton5;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton6;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton7;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton8;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton9;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton10;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton11;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton12;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton13;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton14;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton15;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton16;

@property NSUInteger pageIndex;
@property NSString *titleText;
@property NSUInteger numLevels;

-(void) initialize;
@end
