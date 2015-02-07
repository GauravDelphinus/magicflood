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

@interface MFGameViewController : UIViewController <UIAlertViewDelegate, GameViewTapHandler, SKProductsRequestDelegate, ADBannerViewDelegate>
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

@property UIAlertView *failAlertView, *successAlertView, *exitAlertView, *addMovesAlertView, *addStarAlertView, *addHurdleSmasherAlertView, *addCoinsAlertView, *finishedAllLevelsView;

@property long gridHandle; //handle to the grid object in C++ code
@end