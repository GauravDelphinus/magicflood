//
//  MFGameViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MFGameView.h"
#import <AudioToolbox/AudioToolbox.h>
#import <iAd/iAd.h>
#import "MFGameDialogController.h"
#import <MessageUI/MessageUI.h>

@interface MFGameViewController : UIViewController <UIAlertViewDelegate, GameViewTapHandler, ADBannerViewDelegate, GameDialogOptionSelectedDelegate,
                    IAPPurchaseHandler, MFMailComposeViewControllerDelegate>

@property int gameLevel; //set by the calling MFViewController

#define DIALOG_TYPE_ADD_MOVES   1
#define DIALOG_TYPE_ADD_STAR    2
#define DIALOG_TYPE_ADD_HURDLE_SMASHER 3
#define DIALOG_TYPE_ADD_BRIDGE  4
#define DIALOG_TYPE_ADD_COINS   5
#define DIALOG_TYPE_REMOVE_ADS 6
#define DIALOG_TYPE_GAME_SUCCESS    7
#define DIALOG_TYPE_GAME_FAILED 8
#define DIALOG_TYPE_GAME_FINISHED   9
#define DIALOG_TYPE_GAME_MENU   10
#define DIALOG_TYPE_STAR_PLACEMENT_INFO 11
#define DIALOG_TYPE_STAR_PLACEMENT_TRY_AGAIN 12
#define DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO 13
#define DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_TRY_AGAIN 14
#define DIALOG_TYPE_BRIDGE_PLACEMENT_INFO   15
#define DIALOG_TYPE_BRIDGE_PLACEMENT_TRY_AGAIN  16
#define DIALOG_TYPE_IAP_PURCHASE_FAILED  17

#define DIALOG_TYPE_IAP_RESTORE_FAILED 18
#define DIALOG_TYPE_INTRODUCE_STARS 19
#define DIALOG_TYPE_INTRODUCE_HURDLE_SMASHERS 20
#define DIALOG_TYPE_INTRODUCE_BRIDGES   21

#define DIALOG_TYPE_DO_YOU_LIKE_GAME    22
#define DIALOG_TYPE_RATE_GAME   23


@end