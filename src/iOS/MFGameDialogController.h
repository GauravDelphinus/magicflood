//
//  MFGameDialogController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 7/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MFGameDialogController : UIViewController
@property (strong, nonatomic) IBOutlet UILabel *mTitleLabel;
@property (strong, nonatomic) IBOutlet UILabel *mDescriptionLabel;
@property (strong, nonatomic) IBOutlet UIButton *mPositiveAction1Button;
@property (strong, nonatomic) IBOutlet UIButton *mNegativeAction1Button;

@property int dialogType;
@property id delegate; //dialog option selected delegate
@end

@protocol GameDialogOptionSelectedDelegate
-(void) gameDialogOptionSelected:(int)dialogType WithOption:(int) option;

#define GAME_DIALOG_POSITIVE_ACTION_1   1
#define GAME_DIALOG_POSITIVE_ACTION_2   2
#define GAME_DIALOG_POSITIVE_ACTION_3   3
#define GAME_DIALOG_POSITIVE_ACTION_4   4
#define GAME_DIALOG_POSITIVE_ACTION_5   5
#define GAME_DIALOG_NEGATIVE_ACTION_1   11
#define GAME_DIALOG_NEGATIVE_ACTION_2   12
@end