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

-(int)GetColorCodeFromUIButton:(UIButton *)button;
-(void)startNewGame;
-(void)updateCoinsLabel:(int)numCoins;
-(NSString *)formatIAPPrice:(NSNumber *)price WithLocale:(NSLocale *)locale;
-(void)setupSound;
-(void)playSound:(SystemSoundID)soundID;
-(void) gameDialogOptionSelected:(int)dialogType WithOption:(int) option;

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
#define DIALOG_TYPE_PLAY_ON 9
#define DIALOG_TYPE_GAME_MENU   10

@end