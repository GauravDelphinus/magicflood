//
//  MFGameDialogController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 7/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MFIAPManager.h"

@protocol GameDialogOptionSelectedDelegate
-(void) gameDialogOptionSelected:(int)dialogType WithOption:(int) option;

#define GAME_DIALOG_POSITIVE_ACTION_1   1
#define GAME_DIALOG_POSITIVE_ACTION_2   2
#define GAME_DIALOG_POSITIVE_ACTION_3   3
#define GAME_DIALOG_POSITIVE_ACTION_4   4
#define GAME_DIALOG_POSITIVE_ACTION_5   5
#define GAME_DIALOG_NEGATIVE_ACTION_1   11
#define GAME_DIALOG_NEGATIVE_ACTION_2   12
#define GAME_DIALOG_NEGATIVE_ACTION_3   13
#define GAME_DIALOG_NEGATIVE_ACTION_4   14
#define GAME_DIALOG_NEGATIVE_ACTION_5   15
@end

@interface MFGameDialogController : UIViewController

@property int dialogType;
@property int data; // additional data used by a dialog, if required
@property id <GameDialogOptionSelectedDelegate> delegate; //dialog option selected delegate
@property MFIAPManager *mIAPManager;
@end

