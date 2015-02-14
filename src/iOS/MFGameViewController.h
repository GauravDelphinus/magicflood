//
//  MFGameViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MFGameView.h"
#import <StoreKit/StoreKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import <iAd/iAd.h>
#import "MFGameDialogController.h"
#import "MFAddCoinsDialog.h"

@interface MFGameViewController : UIViewController <UIAlertViewDelegate, GameViewTapHandler, SKProductsRequestDelegate, ADBannerViewDelegate, GameDialogOptionSelectedDelegate>
{
   SystemSoundID mCurrentlyPlayingSound, mButtonClickSoundID, mGameSuccessSoundID, mGameFailedSoundID, mHurdleSmashedSoundID, mStarPlacedSoundID;
    NSURL *mCurrentlyPlayingSoundURL, *mButtonClickSoundURL, *mGameSuccessSoundURL, *mGameFailedSoundURL, *mHurdleSmashedSoundURL, *mStarPlacedSoundURL;
}

@property int gameLevel; //set by the calling MFViewController
@property BOOL mStarPlacementMode;
@property BOOL mHurdleSmasherMode;
@property NSArray *products;
@property BOOL mEnableSound;
@property (strong, nonatomic) IBOutlet ADBannerView *mAdBannerView;
@property BOOL mAdBannerVisible;
@property (strong, nonatomic) IBOutlet UIButton *mAddStarButton;
@property (strong, nonatomic) IBOutlet UIButton *mAddHurdleSmasherButton;
@property (strong, nonatomic) IBOutlet UIButton *mAddCoinsButton;
@property (strong, nonatomic) IBOutlet UIButton *mAddMovesButton;
@property (strong, nonatomic) IBOutlet UIButton *mRemoveAdsButton;
@property (strong, nonatomic) IBOutlet UIButton *mMenuButton;
@property (strong, nonatomic) IBOutlet UIButton *mRedButton;
@property (strong, nonatomic) IBOutlet UIButton *mGreenButton;
@property (strong, nonatomic) IBOutlet UIButton *mBlueButton;
@property (strong, nonatomic) IBOutlet UIButton *mYellowButton;
@property (strong, nonatomic) IBOutlet UIButton *mOrangeButton;
@property (strong, nonatomic) IBOutlet UIButton *mCyanButton;

-(int)GetColorCodeFromUIButton:(UIButton *)button;
-(void)startNewGame;
-(void)updateCoinsLabel:(int)numCoins;
-(NSString *)formatIAPPrice:(NSNumber *)price WithLocale:(NSLocale *)locale;
-(void)setupSound;
-(void)playSound:(SystemSoundID)soundID;
-(void) gameDialogOptionSelected:(int)dialogType WithOption:(int) option;
-(void)showDialog:(NSString *)storyBoardID withDialogType:(int)dialogType withData:(int)data;
-(void)showDialogOfType:(int)dialogType;

@property UIAlertView *failAlertView, *successAlertView, *exitAlertView, *addMovesAlertView, *addStarAlertView, *addHurdleSmasherAlertView, *addCoinsAlertView, *finishedAllLevelsView;

@property long gridHandle; //handle to the grid object in C++ code

#define DIALOG_TYPE_ADD_MOVES   1
#define DIALOG_TYPE_ADD_STAR    2
#define DIALOG_TYPE_ADD_HURDLE_SMASHER 3
#define DIALOG_TYPE_ADD_COINS   4
#define DIALOG_TYPE_REMOVE_ADS 5
#define DIALOG_TYPE_GAME_SUCCESS    6
#define DIALOG_TYPE_GAME_FAILED 7
#define DIALOG_TYPE_GAME_FINISHED   8
#define DIALOG_TYPE_GAME_MENU   9
#define DIALOG_TYPE_NOT_CONNECTED   10
#define DIALOG_TYPE_STAR_PLACEMENT_INFO 11
#define DIALOG_TYPE_STAR_PLACEMENT_TRY_AGAIN 12
#define DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO 13
#define DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_TRY_AGAIN 14
#define DIALOG_TYPE_IAP_PURCHASE_FAILED  15
#define DIALOG_TYPE_IAP_CONSUME_FAILED 16
#define DIALOG_TYPE_IAP_QUERY_FAILED 17
#define DIALOG_TYPE_INTRODUCE_STARS 18
#define DIALOG_TYPE_INTRODUCE_HURDLE_SMASHERS 19


@end