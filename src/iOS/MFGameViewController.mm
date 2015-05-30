//
//  MFGameViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//


#import "MFGameViewController.h"
#import "MFGlobalInterface.h"
#import "MFIAPInterface.h"
#import "MFGameView.h"
#import "MFGridInterface.h"
#import "MFGameConstants.h"
 #import <StoreKit/StoreKit.h>
#import <StoreKit/SKPaymentQueue.h>
#import "MFGameDialogController.h"
#import "MFIAPInterface.h"
#import "MFUtils.h"

#define STAR_ANIMATION_INTERVAL 0.05 //seconds
#define STAR_ANIMATION_DURATION 10 //steps
#define STAR_BLINK_INTERVAL 1.0 //seconds
#define STAR_ANIMATION_INITIAL_SIZE -20

@interface MFGameViewController ()
{
    SystemSoundID mCurrentlyPlayingSound, mButtonClickSoundID, mGameSuccessSoundID, mGameFailedSoundID, mHurdleSmashedSoundID, mBridgePlacedSoundID, mStarPlacedSoundID;
    NSURL *mCurrentlyPlayingSoundURL, *mButtonClickSoundURL, *mGameSuccessSoundURL, *mGameFailedSoundURL, *mHurdleSmashedSoundURL, *mBridgePlacedSoundURL, *mStarPlacedSoundURL;
}
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
@property (strong, nonatomic) IBOutlet UIButton *mSoundButton;
@property (strong, nonatomic) IBOutlet UILabel *mLevelsLabel;
@property (strong, nonatomic) IBOutlet UILabel *coinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *movesLable; //UILabel that displays the Moves header
@property (strong, nonatomic) IBOutlet UIButton *mAddBridgeButton;
@property (strong, nonatomic) IBOutlet NSLayoutConstraint *mAddBridgeButtonLeftConstraints;
@property int mBridgeStartRow, mBridgeStartCol, mBridgeEndRow, mBridgeEndCol; //the row/col of the currently drawn bridge

@property (strong, nonatomic) IBOutlet MFGameView *gameView; //UIView that renders the actual game board
@property BOOL mStarPlacementMode;
@property BOOL mHurdleSmasherMode;
@property BOOL mBridgeMode;
@property BOOL mEnableSound;
@property CGPoint mBridgeStartPoint;
@property (strong, nonatomic) IBOutlet ADBannerView *mAdBannerView;
@property BOOL mAdBannerVisible;
@property BOOL mAdsRemoved; //whether ads are removed by user
@property (strong, nonatomic) IBOutlet NSLayoutConstraint *mColorButtonBottomConstaints;
@property (strong, nonatomic) IBOutlet NSLayoutConstraint *mAdBannerBottomConstraints;
@property MFIAPManager *mIAPManager; //The In-App Purchase Manager
@property UIAlertView *failAlertView, *successAlertView, *exitAlertView, *addMovesAlertView, *addStarAlertView, *addHurdleSmasherAlertView, *addCoinsAlertView, *finishedAllLevelsView;
@property long gridHandle; //handle to the grid object in C++ code
@property NSTimer *mStarRotationTimer; //star rotation timer for the game view

//@property (strong, nonatomic) IBOutlet UIView *mLifelineInfoCotainerView;


/**
 * Dialog data that is used to control workflow
 */
#define DIALOG_DATA_NONE 0
#define DIALOG_DATA_FROM_ADD_STAR_DIALOG 1
#define DIALOG_DATA_FROM_ADD_MOVES_DIALOG 2
#define DIALOG_DATA_FROM_ADD_HURDLE_SMASHER_DIALOG 3
#define DIALOG_DATA_FROM_ADD_BRIDGE_DIALOG 4
#define DIALOG_DATA_EXIT 5
@property int mLastDialogData;

@end

@implementation MFGameViewController

- (void)viewDidLoad
{
    NSLog(@"gameviewcontroller, viewdidload started, mAddBannerVisible = %d", self.mAdBannerVisible);
    [super viewDidLoad];
    
    [MFUtils setBackgroundImage:self darkenBackground:NO];

    //set self as delegate for the tap protocol in the MFGameView
    self.gameView.delegate = self;
   
    //setup sound
    [self setupSound];
    
    //set up IAP
    [self setupIAP];
    
    //set up Ads
    [self setupAds];
    
    //let the game begin!
    [self startNewGame:self.gameLevel];
}

-(void)viewDidAppear:(BOOL)animated
{
    /**
     Reset self as the delegate for various other objects
     since we're now coming into the view.
     **/
    if (self.mAdBannerView != nil)
    {
        self.mAdBannerView.delegate = self;
    }
    if (self.gameView != nil)
    {
        self.gameView.delegate = self;
    }
    if (self.mIAPManager != nil)
    {
        self.mIAPManager.mPurchaseDelegate = self;
    }
}

-(void)viewWillDisappear:(BOOL)animated
{
    /**
     Removing the MFGameView object from this controller is essential to
     avoid memory leaks.
     **/
    /*
    [self.gameView removeFromSuperview];
    self.gameView = nil;
     */
    
    /**
     Get rid of ad banner.
     **/
    /*
    [self.mAdBannerView removeFromSuperview];
    self.mAdBannerView.delegate = nil;
    self.mAdBannerView = nil;
     */
    
    [self stopTimer];
}

-(void)viewDidDisappear:(BOOL)animated
{
    /**
     Remove all delegate references so that we can dealloc
     if the view controller is being dismissed.
     **/
    if (self.mAdBannerView != nil)
    {
        self.mAdBannerView.delegate = nil;
    }
    if (self.gameView != nil)
    {
        self.gameView.delegate = nil;
    }
    if (self.mIAPManager != nil)
    {
        self.mIAPManager.mPurchaseDelegate = nil;
    }
}

-(void)viewWillAppear:(BOOL)animated
{
    [self startTimer];
}

/**
 Called when the view controller is about to unload.  Clear resources here.
 **/
-(void)dealloc
{
    //NSLog(@"dealloc, gridHandle = %lx", self.gridHandle);
    if (self.gridHandle != 0)
    {
        deleteGrid(self.gridHandle);
        self.gridHandle = 0;
    }
    
    /**
     Removing the MFGameView object from this controller is essential to
     avoid memory leaks.
     **/
    [self.gameView removeFromSuperview];
    [self.gameView freeGameData];
    self.gameView = nil;
    
    /**
     Get rid of ad banner.
     **/
    [self.mAdBannerView removeFromSuperview];
    self.mAdBannerView.delegate = nil;
    self.mAdBannerView = nil;
}

/*********************  GameView Related **************************/

/**
 Set up a timer that draws a "rotating" star or stars.
 **/
-(void)startTimer
{
    NSLog(@"startTimer");
    self.mStarRotationTimer = [NSTimer scheduledTimerWithTimeInterval:STAR_ANIMATION_INTERVAL
                                                               target:self
                                                             selector:@selector(timerCallback:)
                                                             userInfo:nil
                                                              repeats:YES];
    self.gameView.mCurrentStarSize = STAR_ANIMATION_INITIAL_SIZE;
}

-(void)stopTimer
{
    NSLog(@"stopTimer");
    [self.mStarRotationTimer invalidate];
    self.mStarRotationTimer = nil;
}

/**
 Timer callback that triggers a re-render of the screen.
 **/
-(void)timerCallback:(NSTimer *)timer
{
    /**
     Show a "Blinking Star" effect.  The initial animation shows the star starting
     with a big size and reducing to a regular size to attract the player's attention
     at the start of the game.  Followed by that, the star keeps alternating between
     regular and large sizes to give a "blinking" effect.  The timer interval for the
     first and second phase is different.
     **/
    if (self.gameView.mCurrentStarSize < 0)
    {
        self.gameView.mCurrentStarSize ++;
        
        if (self.gameView.mCurrentStarSize == 0) //star is now normal size, so reset the timer interval
        {
            [self stopTimer];
            
            self.mStarRotationTimer = [NSTimer scheduledTimerWithTimeInterval:STAR_BLINK_INTERVAL
                                                                       target:self
                                                                     selector:@selector(timerCallback:)
                                                                     userInfo:nil
                                                                      repeats:YES];
        }
    }
    else if (self.gameView.mCurrentStarSize == 0)
    {
        self.gameView.mCurrentStarSize = 1;
    }
    else if (self.gameView.mCurrentStarSize == 1)
    {
        self.gameView.mCurrentStarSize = 0;
    }
    [self.gameView setNeedsDisplay];
}

/*********************  Sound Related **************************/

/**
 Load sounds into the cache for later use.
 **/
-(void)setupSound
{
    NSString *buttonPressPath = [[NSBundle mainBundle]
                                 pathForResource:@"button_press_sound" ofType:@"wav"];
    mButtonClickSoundURL = [NSURL fileURLWithPath:buttonPressPath];
    AudioServicesCreateSystemSoundID((__bridge CFURLRef)mButtonClickSoundURL, &mButtonClickSoundID);
    
    NSString *gameFailedPath = [[NSBundle mainBundle]
                                pathForResource:@"game_failed_sound" ofType:@"wav"];
    mGameFailedSoundURL = [NSURL fileURLWithPath:gameFailedPath];
    AudioServicesCreateSystemSoundID((__bridge CFURLRef)mGameFailedSoundURL, &mGameFailedSoundID);
    
    NSString *gameSuccessPath = [[NSBundle mainBundle]
                                 pathForResource:@"game_success_sound" ofType:@"wav"];
    mGameSuccessSoundURL = [NSURL fileURLWithPath:gameSuccessPath];
    AudioServicesCreateSystemSoundID((__bridge CFURLRef)mGameSuccessSoundURL, &mGameSuccessSoundID);
    
    NSString *hurdleSmashedPath = [[NSBundle mainBundle]
                                   pathForResource:@"hurdle_smashed_sound" ofType:@"wav"];
    mHurdleSmashedSoundURL = [NSURL fileURLWithPath:hurdleSmashedPath];
    AudioServicesCreateSystemSoundID((__bridge CFURLRef)mHurdleSmashedSoundURL, &mHurdleSmashedSoundID);
    
    NSString *bridgePlacedPath = [[NSBundle mainBundle]
                                   pathForResource:@"bridge_created_sound" ofType:@"wav"];
    mBridgePlacedSoundURL = [NSURL fileURLWithPath:bridgePlacedPath];
    AudioServicesCreateSystemSoundID((__bridge CFURLRef)mBridgePlacedSoundURL, &mBridgePlacedSoundID);
    
    NSString *starPlacedPath = [[NSBundle mainBundle]
                                pathForResource:@"star_placed_sound" ofType:@"wav"];
    mStarPlacedSoundURL = [NSURL fileURLWithPath:starPlacedPath];
    AudioServicesCreateSystemSoundID((__bridge CFURLRef)mStarPlacedSoundURL, &mStarPlacedSoundID);
    
    //preference
    self.mEnableSound = [[NSUserDefaults standardUserDefaults] boolForKey:@PREFERENCE_SOUND];
    [self refreshSoundButton:self.mSoundButton];
}

/**
 The Sound button was pressed.  Toggle it.
 **/
- (IBAction)soundButtonPressed:(id)sender
{
    self.mEnableSound = [[NSUserDefaults standardUserDefaults] boolForKey:@PREFERENCE_SOUND];

    self.mEnableSound = !self.mEnableSound;
    [[NSUserDefaults standardUserDefaults] setBool:self.mEnableSound forKey:@PREFERENCE_SOUND];
    
    UIButton *button = (UIButton *)sender;
    [self refreshSoundButton:button];
}

/**
 Update the Sound Button to show the On/Off state.
 **/
-(void)refreshSoundButton:(UIButton *)button
{
    if (self.mEnableSound)
    {
        UIImage *btnImage = [UIImage imageNamed:@"ic_button_sound_on_normal"];
        [button setImage:btnImage forState:UIControlStateNormal];
    }
    else
    {
        UIImage *btnImage = [UIImage imageNamed:@"ic_button_sound_off_normal"];
        [button setImage:btnImage forState:UIControlStateNormal];
    }
}

/**
 Actually play the supplied sound.
 **/
-(void) playSound:(SystemSoundID)soundID
{
    if (self.mEnableSound)
    {
        //[self stopSound];
        AudioServicesPlaySystemSound(soundID);
        mCurrentlyPlayingSound = soundID;
    }
}

/**
 Stop sound if something is already playing.  Also, due to 
 a limitation in the way AudioServices Sounds work, we need
 to recache/reload the sounds for next time use.
 **/
-(void) stopSound
{
    if (!self.mEnableSound)
        return;
    
    AudioServicesDisposeSystemSoundID(mCurrentlyPlayingSound);
    if (mCurrentlyPlayingSound == mButtonClickSoundID)
    {
        AudioServicesCreateSystemSoundID((__bridge CFURLRef)mButtonClickSoundURL, &mButtonClickSoundID);
    }
    else if (mCurrentlyPlayingSound == mGameFailedSoundID)
    {
        AudioServicesCreateSystemSoundID((__bridge CFURLRef)mGameFailedSoundURL, &mGameFailedSoundID);
    }
    else if (mCurrentlyPlayingSound == mGameSuccessSoundID)
    {
        AudioServicesCreateSystemSoundID((__bridge CFURLRef)mGameSuccessSoundURL, &mGameSuccessSoundID);
    }
    else if (mCurrentlyPlayingSound == mStarPlacedSoundID)
    {
        AudioServicesCreateSystemSoundID((__bridge CFURLRef)mStarPlacedSoundURL, &mStarPlacedSoundID);
    }
    else if (mCurrentlyPlayingSound == mHurdleSmashedSoundID)
    {
        AudioServicesCreateSystemSoundID((__bridge CFURLRef)mHurdleSmashedSoundURL, &mHurdleSmashedSoundID);
    }
    else if (mCurrentlyPlayingSound == mBridgePlacedSoundID)
    {
        AudioServicesCreateSystemSoundID((__bridge CFURLRef)mBridgePlacedSoundURL, &mBridgePlacedSoundID);
    }
}

/*********************  IAP (In-App Purchase) Related **************************/

/**
 Initialize the In-App Purchase manager.
 **/
-(void) setupIAP
{
    self.mIAPManager = [[MFIAPManager alloc] init];
    [self.mIAPManager initialize];
    self.mIAPManager.mPurchaseDelegate = self;
}

/**
 This is called by the IAP Manager on purchase event.
 **/
-(void)onPurchaseFinished:(NSString *)pid WithStatus:(BOOL)status WithError:(NSError *)error
{
    if (status == YES) //purchase successful!
    {
        if ([pid isEqualToString:@IAP_REMOVE_ADS])
        {
            [self hideAds];
        }
        else
        {
            int numCoins = getCoins();
            if ([pid isEqualToString:@IAP_COINS_FIRST])
            {
                [self updateCoinsEarned:(numCoins + getNumCoinsIAPFirst())];
            }
            else if ([pid isEqualToString:@IAP_COINS_SECOND])
            {
                [self updateCoinsEarned:(numCoins + getNumCoinsIAPSecond())];
            }
            else if ([pid isEqualToString:@IAP_COINS_THIRD])
            {
                [self updateCoinsEarned:(numCoins + getNumCoinsIAPThird())];
            }
            else if ([pid isEqualToString:@IAP_COINS_FOURTH])
            {
                [self updateCoinsEarned:(numCoins + getNumCoinsIAPFourth())];
            }
            
            /**
             If we reached here in the middle of another workflow, try to 
             reinstante that.
             **/
            if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_MOVES_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_MOVES withData:0 withAnimation:NO];
            }
            else if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_STAR_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_STAR withData:0 withAnimation:NO];
            }
            else if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_HURDLE_SMASHER_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_HURDLE_SMASHER withData:0 withAnimation:NO];
            }
            else if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_BRIDGE_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_BRIDGE withData:0 withAnimation:NO];
            }
            self.mLastDialogData = DIALOG_DATA_NONE;
        }
    }
    else //purchase failed or canceled
    {
        if (error.code == SKErrorPaymentCancelled) //user cancelled, so don't show any dialog
        {
            /**
             If we reached here in the middle of another workflow, try to
             reinstante that.
             **/
            if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_MOVES_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_MOVES withData:0 withAnimation:NO];
            }
            else if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_STAR_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_STAR withData:0 withAnimation:NO];
            }
            else if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_HURDLE_SMASHER_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_HURDLE_SMASHER withData:0 withAnimation:NO];
            }
            else if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_BRIDGE_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_BRIDGE withData:0 withAnimation:NO];
            }
            self.mLastDialogData = DIALOG_DATA_NONE;
        }
        else
        {
            /**
             There was a genuine error, so show the dialog.
             **/
            [self showDialogOfType:DIALOG_TYPE_IAP_PURCHASE_FAILED withData:(void *)error withAnimation:NO];
        }
    }
}

/**
 Called when a restore transaction is triggered.
 **/
-(void)onPurchaseRestored:(NSString *)pid WithStatus:(BOOL)status WithError:(NSError *)error
{
    if (status == YES) //purchase successful!
    {
        if ([pid isEqualToString:@IAP_REMOVE_ADS])
        {
            [self hideAds];
        }
    }
    else
    {
        if (error.code != SKErrorPaymentCancelled)
        {
            [self showDialogOfType:DIALOG_TYPE_IAP_RESTORE_FAILED withData:(void *)error withAnimation:NO];
        }
    }
}

/*********************  Ads (iAd) Related **************************/

/**
 Set up Ads (iAd) framework.
 **/
-(void)setupAds
{
    /**
     Check the preference.  If the preference is set to YES (Ads Removed), it means the
     user has actually bought the IAP to remove ads, so we should NOT show
     ads if that's the case.
     **/
    self.mAdsRemoved = [[NSUserDefaults standardUserDefaults] boolForKey:@PREFERENCE_ADS_REMOVED];
    if (!self.mAdsRemoved)
    {
        /**
         The NSLayoutConstraint that sits between the mAdBannerView and the botton layout guide
         and helps adjust the ad banner in or out of view by popping it below the bottom of the screen
         by adjusting the Y position.
         **/
        [self.view removeConstraint: self.mAdBannerBottomConstraints];
        self.mAdBannerBottomConstraints = [NSLayoutConstraint constraintWithItem:self.mAdBannerView
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.bottomLayoutGuide
                                                                         attribute:NSLayoutAttributeTop
                                                                        multiplier:1.0
                                                                          constant:self.mAdBannerView.frame.size.height]; //the banner height ensures the bottom of the Ad View is exactly this much below the bottom layout guide (just hanging below the screen edge)
        [self.view addConstraint:self.mAdBannerBottomConstraints];
        
        /**
         Initially, when we haven't started fetching ads, show the color buttons just off
         the bottom of the screen.
         **/
        [self.view removeConstraint: self.mColorButtonBottomConstaints];
        self.mColorButtonBottomConstaints = [NSLayoutConstraint constraintWithItem:self.mRedButton
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.bottomLayoutGuide
                                                                         attribute:NSLayoutAttributeBottom
                                                                        multiplier:1.0
                                                                          constant:-5.0]; //keep the color button 5.0 points above the screen edge
        
        [self.view addConstraint:self.mColorButtonBottomConstaints];
        
        [self.view setNeedsLayout];
        
        /**
         Start listening to the iAd callbacks
         **/
        self.mAdBannerView.delegate = self;
    }
    else //Ads are removed, so get rid of the Ad Banner view
    {
        [self.mAdBannerView removeFromSuperview];
        self.mAdBannerView.delegate = nil;
        self.mAdBannerView = nil;
        
        /**
         Reset the layout constraint to now work between the color button and the
         bottom layout guide.
         **/
        [self.view removeConstraint: self.mColorButtonBottomConstaints];
        [self.view removeConstraint: self.mAdBannerBottomConstraints];
        
        self.mColorButtonBottomConstaints = [NSLayoutConstraint constraintWithItem:self.mRedButton
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.bottomLayoutGuide
                                                                         attribute:NSLayoutAttributeBottom
                                                                        multiplier:1.0
                                                                          constant:-5.0]; //keep the color button 5.0 points above the screen edge
        [self.view addConstraint:self.mColorButtonBottomConstaints];
        
        [self.view setNeedsLayout];

    }

    self.mRemoveAdsButton.hidden = YES;
    self.mAdBannerVisible = NO;
}

/**
 An Ad was successfully loaded in the banner view.
 Adjust the layout constraint to pop the ad banner back into view
 (if currently not visible)
 **/
- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    NSLog(@"adbanner height = %f", self.mAdBannerView.frame.size.height);
    
    if (!self.mAdBannerVisible)
    {
        /**
         Show the ad banner view just aligned with the bottom
         of the screen.
         **/
        [self.view removeConstraint: self.mAdBannerBottomConstraints];
        self.mAdBannerBottomConstraints = [NSLayoutConstraint constraintWithItem:self.mAdBannerView
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.bottomLayoutGuide
                                                                         attribute:NSLayoutAttributeBottom
                                                                        multiplier:1.0
                                                                          constant:0.0]; //0.0 ensures the bottom of the Ad View aligns with the bottom layout guide
        [self.view addConstraint:self.mAdBannerBottomConstraints];
        
        /**
         Connect the ad banner view and the red button, so the buttons
         are aligned just above the ad banner view.
         **/
        [self.view removeConstraint: self.mColorButtonBottomConstaints];
        self.mColorButtonBottomConstaints = [NSLayoutConstraint constraintWithItem:self.mRedButton
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.mAdBannerView
                                                                         attribute:NSLayoutAttributeTop
                                                                        multiplier:1.0
                                                                          constant:-5.0]; //keep the color button aligned with the top of the ad banner view
        
        [self.view addConstraint:self.mColorButtonBottomConstaints];
        
        [self.view setNeedsLayout];
        
        self.mAdBannerVisible = YES;
        self.mRemoveAdsButton.hidden = NO;
    }
}

/**
 An Ad failed to load in the banner view.
 Adjust the layout constraint to pop the ad banner out of the view
 (if currently visible).
 **/
- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    if (self.mAdBannerVisible)
    {
        /**
         Hide the ad banner view while we try to look for ads, by hanging it
         just off the bottom of the screen.
         **/
        [self.view removeConstraint: self.mAdBannerBottomConstraints];
        self.mAdBannerBottomConstraints = [NSLayoutConstraint constraintWithItem:self.mAdBannerView
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.bottomLayoutGuide
                                                                         attribute:NSLayoutAttributeTop
                                                                        multiplier:1.0
                                                                          constant:self.mAdBannerView.frame.size.height]; //the banner height ensures the bottom of the Ad View is exactly this much below the bottom layout guide (just hanging below the screen edge)
        [self.view addConstraint:self.mAdBannerBottomConstraints];
        
        /**
         Since the ad banner view is hidden, align the color buttons
         just above the bottom of the screen.
         **/
        [self.view removeConstraint: self.mColorButtonBottomConstaints];
        self.mColorButtonBottomConstaints = [NSLayoutConstraint constraintWithItem:self.mRedButton
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.bottomLayoutGuide
                                                                         attribute:NSLayoutAttributeBottom
                                                                        multiplier:1.0
                                                                          constant:-5.0]; //keep the color button 5.0 points above the screen edge
        
        [self.view addConstraint:self.mColorButtonBottomConstaints];
        
        [self.view setNeedsLayout];
        [self.view setNeedsDisplay];
        
        self.mAdBannerVisible = NO;
        self.mRemoveAdsButton.hidden = YES;
    }
}

- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave
{
    NSLog(@"bannerViewActionShouldBegin, ad banner view frame = [x = %f, y = %f, width = %f, height = %f ]", self.mAdBannerView.frame.origin.x, self.mAdBannerView.frame.origin.y, self.mAdBannerView.frame.size.width, self.mAdBannerView.frame.size.height);
    return YES;
}

- (void)bannerViewActionDidFinish:(ADBannerView *)banner
{
    NSLog(@"bannerViewActionDidFinish");
}

- (IBAction)removeAds:(id)sender {
    [self showDialogOfType:DIALOG_TYPE_REMOVE_ADS withData:0 withAnimation:NO];
}

/**
 The user just made an IAP to remove ads.  We must hide the ad banner
 and also set the preference to stop loading ads going forward.
 **/
-(void) hideAds
{
    /**
     get rid of the ad banner view completely.
     **/
    [self.mAdBannerView removeFromSuperview];
    self.mAdBannerView.delegate = nil;
    self.mAdBannerView = nil;
    
    /**
     Update the constraints to now hook the color button with the bottom layout guide
     instead of the ad banner view and the bottom layout guide.
     **/
    [self.view removeConstraint: self.mAdBannerBottomConstraints];
    [self.view removeConstraint: self.mColorButtonBottomConstaints];
    self.mColorButtonBottomConstaints = [NSLayoutConstraint constraintWithItem:self.mRedButton
                                                                     attribute:NSLayoutAttributeBottom
                                                                     relatedBy:NSLayoutRelationEqual
                                                                        toItem:self.bottomLayoutGuide
                                                                     attribute:NSLayoutAttributeBottom
                                                                    multiplier:1.0
                                                                      constant:-5.0]; //keep the color button 5.0 points above the screen edge
    [self.view addConstraint:self.mColorButtonBottomConstaints];
    
    [self.view setNeedsLayout];
        
    self.mAdBannerVisible = NO;
    
    //set the preference to not load ads going forward
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@PREFERENCE_ADS_REMOVED];
    self.mAdsRemoved = YES;
    
    //also, hide the "Remove Ads" button
    self.mRemoveAdsButton.hidden = YES;
    
}

/*********************  Game Logic **************************/

/**
 Start a new game.  This can be called without having to reload the view controller.
 **/
-(void)startNewGame: (int)level
{
    //clear the handle if a game was already underway
    if (self.gridHandle != 0)
    {
        deleteGrid(self.gridHandle);
        self.gridHandle = 0;
    }
    
    /**
     Check if we've reached the last level!
     **/
    if (level > getNumLevels())
    {
        [self showDialogOfType:DIALOG_TYPE_GAME_FINISHED withData:0 withAnimation:NO];
        
        return;
    }
    
    self.gameLevel = level;
    //initialize a new game grid
    self.gridHandle = createNewGrid(self.gameLevel);
    
    //extract data for the game, and then pass on to the UIView for rendering
    int **startPos = getStartPos(self.gridHandle);
    int numStartPos = getNumStartPos(self.gridHandle);
    int **gridData = getGridData(self.gridHandle);
    
    [[self gameView] initializeGameData:gridData WithSize:getGridSize(self.gridHandle) WithNumStartPos:numStartPos WithStartPos:startPos WithMaxMoves:getMaxMoves(self.gridHandle)];
    
    freeGridData(self.gridHandle, gridData);
    freeStartPos(self.gridHandle, startPos);
    gridData = NULL;
    startPos = NULL;

    // initialize the current coins tally
    int numCoins = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_COINS_EARNED];
    setCoins(numCoins);
    
    //initialize the bridge related structures
    self.mBridgeStartPoint = {-1, -1};
    
    // update the various UI elements
    [self updateCoinsLabel:getCoins()];
    [self updateLevelLabel:self.gameLevel];
    [self refreshLifelinesUI];
    [self updateMovesLabel:(getMaxMoves(self.gridHandle) - getCurrMove(self.gridHandle))];
}

/**
 The Add Moves button was pressed.
 **/
- (IBAction)addMoves:(id)sender {
    [self showDialogOfType:DIALOG_TYPE_ADD_MOVES withData:0 withAnimation:NO];
}

/**
 The Add Hurdle Smasher button was pressed.
 **/
- (IBAction)addHurdleSmasher:(id)sender {
    
    if (self.mHurdleSmasherMode)
    {
        /* Cancel the Hurdle Smasher mode */
        [self enableDisableAllButtons:YES];
        
        self.mHurdleSmasherMode = NO;
        
        [self refreshLifelinesUI];
        return;
    }
    
    int numSmashers = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED];
    if (numSmashers == 0)
    {
        [self showDialogOfType:DIALOG_TYPE_ADD_HURDLE_SMASHER withData:0 withAnimation:NO];
    }
    else
    {
        int hurdleSmasherPlacementCount = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_HURDLE_SMASHER_PLACEMENT_COUNT];
        if (hurdleSmasherPlacementCount < MAX_HURDLE_SMASHER_PLACEMENT_DIALOG_COUNT)
        {
            //show the placement info dialog
            [self showDialogOfType:DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO withData:0 withAnimation:NO];
            
            hurdleSmasherPlacementCount++;
            [[NSUserDefaults standardUserDefaults] setInteger:hurdleSmasherPlacementCount forKey: @PREFERENCE_HURDLE_SMASHER_PLACEMENT_COUNT];
        }
        else
        {
            //enter state where game view detects tap on a specific cell
            [self.gameView enableDisableTouchInput:YES];
            self.mHurdleSmasherMode = YES;
            
            [self refreshLifelinesUI];
            
            NSString *title = [NSString stringWithFormat:NSLocalizedString(@"hurdle_smasher_placement_title", @"")];
            [self showDialog:@"LifelinePlacementInfoDialog" withDialogType:0 withData:nil withStrData:title withAnimation:YES autoHide:YES];
        }
    }
}

/**
 The Add Star button was pressed.
 **/
- (IBAction)addStar:(id)sender {
    
    if (self.mStarPlacementMode)
    {
        /** Cancel the star placement mode */
        [self enableDisableAllButtons:YES];
        
        self.mStarPlacementMode = NO;
        
        [self refreshLifelinesUI];
        return;
    }
    
    int numStars = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_STARS_EARNED];
    if (numStars == 0)
    {
        [self showDialogOfType:DIALOG_TYPE_ADD_STAR withData:0 withAnimation:NO];
    }
    else
    {
        int starPlacementCount = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_STAR_PLACEMENT_COUNT];
        if (starPlacementCount < MAX_STAR_PLACEMENT_DIALOG_COUNT)
        {
            //show the placement info dialog
            [self showDialogOfType:DIALOG_TYPE_STAR_PLACEMENT_INFO withData:0 withAnimation:NO];
            
            starPlacementCount++;
            [[NSUserDefaults standardUserDefaults] setInteger:starPlacementCount forKey: @PREFERENCE_STAR_PLACEMENT_COUNT];
        }
        else
        {
            //enter state where game view detects tap on a specific cell
            [self.gameView enableDisableTouchInput:YES];
            self.mStarPlacementMode = YES;
            
            [self refreshLifelinesUI];
            
            NSString *title = [NSString stringWithFormat:NSLocalizedString(@"star_placement_title", @"")];
            [self showDialog:@"LifelinePlacementInfoDialog" withDialogType:0 withData:nil withStrData:title withAnimation:YES autoHide:YES];
        }
    }
}

/**
 The Add Bridge button was pressed.
 **/
- (IBAction)addBridge:(id)sender {
    
    if (self.mBridgeMode)
    {
        /** Cancel the Bridge Mode **/
        [self enableDisableAllButtons:YES];
        
        self.mBridgeMode = NO;
        
        [self refreshLifelinesUI];
        return;
    }
    
    int numBridges = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_BRIDGES_EARNED];
    if (numBridges == 0)
    {
        [self showDialogOfType:DIALOG_TYPE_ADD_BRIDGE withData:0 withAnimation:NO];
    }
    else
    {
        int bridgePlacementCount = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_BRIDGE_PLACEMENT_COUNT];
        if (bridgePlacementCount < MAX_BRIDGE_PLACEMENT_DIALOG_COUNT)
        {
            //show the placement info dialog
            [self showDialogOfType:DIALOG_TYPE_BRIDGE_PLACEMENT_INFO withData:0 withAnimation:NO];
            
            bridgePlacementCount++;
            [[NSUserDefaults standardUserDefaults] setInteger:bridgePlacementCount forKey: @PREFERENCE_BRIDGE_PLACEMENT_COUNT];
        }
        else
        {
            //enter state where game view detects tap on a specific cell
            [self.gameView enableDisableTouchInput:YES];
            self.mBridgeMode = YES;
            
            [self refreshLifelinesUI];
            
            NSString *title = [NSString stringWithFormat:NSLocalizedString(@"bridge_placement_title", @"")];
            [self showDialog:@"LifelinePlacementInfoDialog" withDialogType:0 withData:nil withStrData:title withAnimation:YES autoHide:YES];
        }
    }
}

- (IBAction)cancelLifelinePlacementMode:(id)sender {
    if (self.mStarPlacementMode || self.mHurdleSmasherMode || self.mBridgeMode)
    {
        /** Cancel the star placement mode */
        [self enableDisableAllButtons:YES];
        
        self.mStarPlacementMode = NO;
        self.mHurdleSmasherMode = NO;
        self.mBridgeMode = NO;
        
        [self refreshLifelinesUI];
    }
}

/**
 The Add Coins button was pressed.
 **/
- (IBAction)addCoins:(id)sender
{
    [self addCoinsWithShortfall:0];
}

/**
 Add Coins - can be called if you run out of coins to
 add lifelines.
 **/
-(void)addCoinsWithShortfall:(int)shortfall
{
    [self showDialogOfType:DIALOG_TYPE_ADD_COINS withData:(void *)shortfall withAnimation:NO];
}

/**
 Handler of the menu button on the game board.
 **/
- (IBAction)handleExit:(id)sender {
    
    [self showDialogOfType:DIALOG_TYPE_GAME_MENU withData:0 withAnimation:NO];
}

/**
 One of the color buttons was pressed, so play the next move.
 **/
- (IBAction)colorButtonPressed:(id)sender
{
    //extract the color that was played
    UIButton *button = (UIButton *)sender;
    int colorValue = [self GetColorCodeFromUIButton:button];
    
    //play the move with the new color, and look for result
    int *result = playMove(self.gridHandle, colorValue);
    
    //update moves label
    [self updateMovesLabel:(getMaxMoves(self.gridHandle) - getCurrMove(self.gridHandle))];
    
    /**
     Pass the game data to the game view so it can draw/refresh
     the board with the updated colors.
     **/
    int **gridData = getGridData(self.gridHandle);
    [[self gameView] updateGameData:gridData];
    freeGridData(self.gridHandle, gridData);
    gridData = NULL;
    
    if (result[0] == RESULT_SUCCESS) //success
    {
        [self playSound:mGameSuccessSoundID];
        
        int numCoins = getCoins();
        numCoins += getNumCoinsForSuccessfulGame(getCurrMove(self.gridHandle), getMaxMoves(self.gridHandle));
        [self updateCoinsEarned:numCoins];
        
        //update last completed preference
        int lastCompletedLevel = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_LAST_COMPLETED_LEVEL];
        if (lastCompletedLevel <= self.gameLevel)
        {
            [[NSUserDefaults standardUserDefaults] setInteger:self.gameLevel forKey: @PREFERENCE_LAST_COMPLETED_LEVEL];
        }
        
        //unlock the next level
        int lastUnlockedLevel = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_LAST_UNLOCKED_LEVEL];
        if (lastUnlockedLevel <= self.gameLevel)
        {
            lastUnlockedLevel ++;
            [[NSUserDefaults standardUserDefaults] setInteger:lastUnlockedLevel forKey: @PREFERENCE_LAST_UNLOCKED_LEVEL];
        }
        
        [self showDialogOfType:DIALOG_TYPE_GAME_SUCCESS withData:0 withAnimation:NO];
    }
    else if (result[0] == RESULT_FAILED) //failed
    {
        [self playSound:mGameFailedSoundID];
        
        [self showDialogOfType:DIALOG_TYPE_GAME_FAILED withData:0 withAnimation:NO];
    }
    else
    {
        [self playSound:mButtonClickSoundID];
    }
    
    if (result != NULL)
    {
        free(result);
    }
}

/**
 Extract the integral color code from the UIColor
 **/
-(int)GetColorCodeFromUIButton:(UIButton *)button
{
    NSInteger tag = button.tag;
    switch (tag)
    {
        case 1:
            return GRID_COLOR_RED;
            
        case 2:
            return GRID_COLOR_GREEN;
            
        case 3:
            return GRID_COLOR_BLUE;
            
        case 4:
            return GRID_COLOR_YELLOW;
            
        case 5:
            return GRID_COLOR_ORANGE;
            
        case 6:
            return GRID_COLOR_CYAN;
    }
    
    return GRID_OBSTACLE;
}

-(void)updateCoinsEarned:(int)coins
{
    setCoins(coins);
    
    [self updateCoinsLabel:coins];
    
    //now also udpate the preference
    [[NSUserDefaults standardUserDefaults] setInteger:coins forKey: @PREFERENCE_TOTAL_COINS_EARNED];
}

/**
 After every 5 game completions we prompt the user to rate
 the app.
 **/
-(void)checkRateGameReminder
{
    int rateGame = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_RATE_GAME_REMINDER];
    if (rateGame == 1)
    {
        [self showDialogOfType:DIALOG_TYPE_DO_YOU_LIKE_GAME withData:NULL withAnimation:false];
        
        [[NSUserDefaults standardUserDefaults] setInteger:INITIAL_RATE_GAME_REMINDER forKey: @PREFERENCE_RATE_GAME_REMINDER];
    }
    else if (rateGame > 1)
    {
        rateGame --;
        
        [[NSUserDefaults standardUserDefaults] setInteger:rateGame forKey: @PREFERENCE_RATE_GAME_REMINDER];
    }
}

/**
 Callback from the email composer screen.
 **/
- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{
    //Add an alert in case of failure
    [self dismissViewControllerAnimated:YES completion:nil];
}

/*********************  UI Updates **************************/

/**
 Logic to show/hide the Star or Hurdle Smasher capabilities.
 **/
-(void)refreshLifelinesUI
{
    if (self.gameLevel == getMinLevelToAddStars())
    {
        //show the "Stars Unlocked" dialog, if not ever shown
        BOOL alreadyShown = [[NSUserDefaults standardUserDefaults] boolForKey:@PREFERENCE_STARS_UNLOCKED];
        
        if (!alreadyShown)
        {
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@PREFERENCE_STARS_UNLOCKED];

            [self showDialogOfType:DIALOG_TYPE_INTRODUCE_STARS withData:0 withAnimation:NO];
        }
    }
    else if (self.gameLevel == getMinLevelToAddHurdleSmasher())
    {
        //show the "Hurdle Smashers Unlocked" dialog, if not ever shown
        BOOL alreadyShown = [[NSUserDefaults standardUserDefaults] boolForKey:@PREFERENCE_HURDLE_SMASHERS_UNLOCKED];
        
        if (!alreadyShown)
        {
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@PREFERENCE_HURDLE_SMASHERS_UNLOCKED];

            [self showDialogOfType:DIALOG_TYPE_INTRODUCE_HURDLE_SMASHERS withData:0 withAnimation:NO];
        }
    }
    else if (self.gameLevel == getMinLevelToAddBridge())
    {
        //show the "Bridges Unlocked" dialog, if not ever shown
        BOOL alreadyShown = [[NSUserDefaults standardUserDefaults] boolForKey:@PREFERENCE_BRIDGES_UNLOCKED];
        
        if (!alreadyShown)
        {
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@PREFERENCE_BRIDGES_UNLOCKED];
            
            [self showDialogOfType:DIALOG_TYPE_INTRODUCE_BRIDGES withData:0 withAnimation:NO];
        }
    }
    
    if (self.gameLevel < getMinLevelToAddStars())
    {
        self.mAddStarButton.hidden = YES;
    }
    else
    {
        self.mAddStarButton.hidden = NO;
        self.mAddStarButton.enabled = YES;
        
        [self.mAddStarButton setImage:nil forState:UIControlStateNormal];
        [self.mAddStarButton setImage:nil forState:UIControlStateHighlighted];
        
        int numStars = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_STARS_EARNED];
        if (numStars == 0)
        {
            [self.mAddStarButton setBackgroundImage:[UIImage imageNamed:@"ic_add_star_normal.png"]
                                forState:UIControlStateNormal];
            [self.mAddStarButton setBackgroundImage:[UIImage imageNamed:@"ic_add_star_pressed.png"]
                                           forState:UIControlStateHighlighted];
        }
        else if (numStars == 1)
        {
            [self.mAddStarButton setBackgroundImage:[UIImage imageNamed:@"ic_use_star_1_normal.png"]
                                           forState:UIControlStateNormal];
            [self.mAddStarButton setBackgroundImage:[UIImage imageNamed:@"ic_use_star_1_pressed.png"]
                                           forState:UIControlStateHighlighted];
        }
        else if (numStars == 2)
        {
            [self.mAddStarButton setBackgroundImage:[UIImage imageNamed:@"ic_use_star_2_normal.png"]
                                           forState:UIControlStateNormal];
            [self.mAddStarButton setBackgroundImage:[UIImage imageNamed:@"ic_use_star_2_pressed.png"]
                                           forState:UIControlStateHighlighted];
        }
    }
    
    if (self.gameLevel < getMinLevelToAddHurdleSmasher())
    {
        self.mAddHurdleSmasherButton.hidden = YES;
    }
    else
    {
        self.mAddHurdleSmasherButton.hidden = NO;
        
        /**
         Disable the 'Smash Hurdle' button if there are not hurdles in the current grid!
         **/
        if (hasHurdles(self.gridHandle))
        {
            self.mAddHurdleSmasherButton.enabled = YES;
            
            [self.mAddHurdleSmasherButton setImage:nil forState:UIControlStateNormal];
            [self.mAddHurdleSmasherButton setImage:nil forState:UIControlStateHighlighted];
            
            int numSmashers = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED];
            if (numSmashers == 0)
            {
                [self.mAddHurdleSmasherButton setBackgroundImage:[UIImage imageNamed:@"ic_add_hurdle_smasher_normal.png"]
                                               forState:UIControlStateNormal];
                [self.mAddHurdleSmasherButton setBackgroundImage:[UIImage imageNamed:@"ic_add_hurdle_smasher_pressed.png"]
                                               forState:UIControlStateHighlighted];
            }
            else if (numSmashers == 1)
            {
                [self.mAddHurdleSmasherButton setBackgroundImage:[UIImage imageNamed:@"ic_use_hurdle_smasher_1_normal.png"]
                                               forState:UIControlStateNormal];
                [self.mAddHurdleSmasherButton setBackgroundImage:[UIImage imageNamed:@"ic_use_hurdle_smasher_1_pressed.png"]
                                               forState:UIControlStateHighlighted];
            }
            else if (numSmashers == 2)
            {
                [self.mAddHurdleSmasherButton setBackgroundImage:[UIImage imageNamed:@"ic_use_hurdle_smasher_2_normal.png"]
                                               forState:UIControlStateNormal];
                [self.mAddHurdleSmasherButton setBackgroundImage:[UIImage imageNamed:@"ic_use_hurdle_smasher_2_pressed.png"]
                                               forState:UIControlStateHighlighted];
            }
        }
        else
        {
            self.mAddHurdleSmasherButton.enabled = NO;
        }
        
    }
    
    if (self.gameLevel < getMinLevelToAddBridge())
    {
        self.mAddBridgeButton.hidden = YES;
    }
    else
    {
        self.mAddBridgeButton.hidden = NO;
        
        if (hasSpaces(self.gridHandle))
        {
            self.mAddBridgeButton.enabled = YES;
            
            [self.mAddBridgeButton setImage:nil forState:UIControlStateNormal];
            [self.mAddBridgeButton setImage:nil forState:UIControlStateHighlighted];
            
            int numBridges = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_BRIDGES_EARNED];
            if (numBridges == 0)
            {
                [self.mAddBridgeButton setBackgroundImage:[UIImage imageNamed:@"ic_add_bridge_normal.png"]
                                                 forState:UIControlStateNormal];
                [self.mAddBridgeButton setBackgroundImage:[UIImage imageNamed:@"ic_add_bridge_pressed.png"]
                                                 forState:UIControlStateHighlighted];
            }
            else if (numBridges == 1)
            {
                [self.mAddBridgeButton setBackgroundImage:[UIImage imageNamed:@"ic_use_bridge_1_normal.png"]
                                                 forState:UIControlStateNormal];
                [self.mAddBridgeButton setBackgroundImage:[UIImage imageNamed:@"ic_use_bridge_1_pressed.png"]
                                                 forState:UIControlStateHighlighted];
            }
            else if (numBridges == 2)
            {
                [self.mAddBridgeButton setBackgroundImage:[UIImage imageNamed:@"ic_use_bridge_2_normal.png"]
                                                 forState:UIControlStateNormal];
                [self.mAddBridgeButton setBackgroundImage:[UIImage imageNamed:@"ic_use_bridge_2_pressed.png"]
                                                 forState:UIControlStateHighlighted];
            }
        }
        else
        {
            self.mAddBridgeButton.enabled = NO;
        }
    }
    
    if (self.mStarPlacementMode)
    {
        [self enableDisableAllButtons:NO];
        
        [self.mAddStarButton setBackgroundImage:[UIImage imageNamed:@"ic_star_mode_normal"]
                                       forState:UIControlStateNormal];
        [self.mAddStarButton setBackgroundImage:[UIImage imageNamed:@"ic_star_mode_pressed.png"]
                                       forState:UIControlStateHighlighted];
        self.mAddStarButton.enabled = YES;
        self.mAddHurdleSmasherButton.enabled = NO;
        self.mAddBridgeButton.enabled = NO;
    }
    else if (self.mHurdleSmasherMode)
    {
        [self enableDisableAllButtons:NO];
        
        [self.mAddHurdleSmasherButton setBackgroundImage:[UIImage imageNamed:@"ic_hurdle_smasher_mode_normal"]
                                       forState:UIControlStateNormal];
        [self.mAddHurdleSmasherButton setBackgroundImage:[UIImage imageNamed:@"ic_hurdle_smasher_mode_pressed.png"]
                                       forState:UIControlStateHighlighted];
        
        self.mAddHurdleSmasherButton.enabled = YES;
        self.mAddStarButton.enabled = NO;
        self.mAddBridgeButton.enabled = NO;
    }
    else if (self.mBridgeMode)
    {
        [self enableDisableAllButtons:NO];
        
        [self.mAddBridgeButton setBackgroundImage:[UIImage imageNamed:@"ic_bridge_mode_normal"]
                                       forState:UIControlStateNormal];
        [self.mAddBridgeButton setBackgroundImage:[UIImage imageNamed:@"ic_bridge_mode_pressed.png"]
                                       forState:UIControlStateHighlighted];
        
        self.mAddBridgeButton.enabled = YES;
        self.mAddStarButton.enabled = NO;
        self.mAddHurdleSmasherButton.enabled = NO;
    }
    else
    {
        [self enableDisableAllButtons:YES];
    }
}

/**
 Enable or Disable all buttons.  Used when the user
 is in selection mode to place a star or hurdle smasher.
 **/
-(void) enableDisableAllButtons:(BOOL)enable
{
    self.mRedButton.enabled = enable;
    self.mGreenButton.enabled = enable;
    self.mBlueButton.enabled = enable;
    self.mYellowButton.enabled = enable;
    self.mOrangeButton.enabled = enable;
    self.mCyanButton.enabled = enable;
    
    self.mMenuButton.enabled = enable;
    self.mSoundButton.enabled = enable;
    self.mAddCoinsButton.enabled = enable;
    self.mAddMovesButton.enabled = enable;
    self.mRemoveAdsButton.enabled = enable;
}

-(void)updateCoinsLabel:(int)numCoins
{
    //update the UI to reflect the total coins
    NSString *labeltext = [NSString stringWithFormat:@"%d", numCoins];
    [self.coinsLabel setText:labeltext];
}

-(void)updateMovesLabel:(int)numMoves
{
    NSString *labeltext = [NSString stringWithFormat:@"%d",
                           numMoves];
    [self.movesLable setText:labeltext];
}

-(void)updateLevelLabel:(int)level
{
    NSString *levelLabel = [NSString stringWithFormat:NSLocalizedString(@"level_number", @""), level];
    [self.mLevelsLabel setText:levelLabel];
}

/*********************  MFGameView Protocol Handlers **************************/
-(void)handleDragBeginAtX:(int)x Y:(int)y Row:(int)row Col:(int)col
{
    if (self.mBridgeMode)
    {
        [self.gameView setBridgeValid:NO]; //bridge isn't valid until both points are valid
        
        if (isBridgeEndpointValid(self.gridHandle, row, col))
        {    
            //store the valid start row/col
            self.mBridgeStartRow = row;
            self.mBridgeStartCol = col;
        }
        
        [self.gameView enterExitBrigeBuildingMode:YES ResetData:NO]; //enter the bridge building mode
    }
}

-(void)handleDragMoveAtX:(int)x Y:(int)y Row:(int)row Col:(int)col
{
    if (self.mBridgeMode)
    {
        int **bridgeExtremes = checkBridgeValid(self.gridHandle, self.mBridgeStartRow, self.mBridgeStartCol, row, col);
        if (bridgeExtremes != NULL)
        {
            [self.gameView setBridgeValid:YES];
            
            //store the valid end row/col
            self.mBridgeEndRow = row;
            self.mBridgeEndCol = col;
            
            //update the bridge extremes so we can draw the bridge ghost
            [self.gameView setBridgeExtremesMinRow:bridgeExtremes[0][0] minCol:bridgeExtremes[0][1] maxRow:bridgeExtremes[1][0] maxCol:bridgeExtremes[1][1]];
            freeBridgeExtremes(self.gridHandle, bridgeExtremes);
            bridgeExtremes = NULL;
        }
        else
        {
            [self.gameView setBridgeValid:NO];
        }
    }
}

-(void)handleDragEndAtX:(int)x Y:(int)y Row:(int)row Col:(int)col
{
    if (self.mBridgeMode)
    {
        int **bridgeExtremes = checkBridgeValid(self.gridHandle, self.mBridgeStartRow, self.mBridgeStartCol, row, col);
        if (bridgeExtremes != NULL)
        {
            freeBridgeExtremes(self.gridHandle, bridgeExtremes);
            bridgeExtremes = NULL;
            
            [self.gameView setBridgeValid:YES];
            
            //store the final valid end/row values
            self.mBridgeEndRow = row;
            self.mBridgeEndCol = col;
            
            //finalize and build the bridge
            
            [self playSound:mBridgePlacedSoundID];
            
            self.mBridgeMode = NO;
            
            //actually build the bridge
            buildBridge(self.gridHandle, self.mBridgeStartRow, self.mBridgeStartCol, self.mBridgeEndRow, self.mBridgeEndCol);
            
            int **gridData = getGridData(self.gridHandle);
            [[self gameView] updateGameData:gridData];
            freeGridData(self.gridHandle, gridData);
            gridData = NULL;
            
            /** Update the number of Bridges remaining */
            int numBridges = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_BRIDGES_EARNED];
            numBridges --;
            [[NSUserDefaults standardUserDefaults] setInteger:numBridges forKey: @PREFERENCE_TOTAL_BRIDGES_EARNED];
            
            [self refreshLifelinesUI];
            
            [self.gameView enterExitBrigeBuildingMode:NO ResetData:NO];
        }
        else
        {
            [self.gameView enterExitBrigeBuildingMode:YES ResetData:YES]; //reenter the bridge building mode
        }
    }
}

/**
 The user tapped on the game grid at position x,y.
 **/
-(void)handleGameViewTapAtX:(int)x andY:(int)y
{
    if (self.mStarPlacementMode == YES)
    {
        int result = addStartPos(self.gridHandle, x, y);
        if (result == 1) //successfully added a star.  Update the view to reflect this
        {
            [self playSound:mStarPlacedSoundID];
            
            self.mStarPlacementMode = NO;
            
            int **startPos = getStartPos(self.gridHandle);
            int numStartPos = getNumStartPos(self.gridHandle);
            
            [[self gameView] updateStartPos:startPos withNum:numStartPos];
            freeStartPos(self.gridHandle, startPos);
            startPos = NULL;
            
            /** Update the number of Stars Remaining */
            int numStars = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_STARS_EARNED];
            numStars --;
            [[NSUserDefaults standardUserDefaults] setInteger:numStars forKey: @PREFERENCE_TOTAL_STARS_EARNED];
            
            [self refreshLifelinesUI];
        }
        else //couldn't place the star, so keep trying
        {
            [self showDialogOfType:DIALOG_TYPE_STAR_PLACEMENT_TRY_AGAIN withData:0 withAnimation:NO];
        }
    }
    else if (self.mHurdleSmasherMode == YES)
    {
        int result = smashHurdle(self.gridHandle, x, y);
        if (result == 1) //successfully used the smasher to crack a hurdle.  Update the view to reflect this
        {
            [self playSound:mHurdleSmashedSoundID];
            
            self.mHurdleSmasherMode = NO;
            
            int **gridData = getGridData(self.gridHandle);
            [[self gameView] updateGameData:gridData];
            freeGridData(self.gridHandle, gridData);
            gridData = NULL;
            
            /** Update the number of Hurdle Smashers remaining */
            int numSmashers = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED];
            numSmashers --;
            [[NSUserDefaults standardUserDefaults] setInteger:numSmashers forKey: @PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED];
            
            [self refreshLifelinesUI];
        }
        else //couldn't find a hurdle.  So keep trying
        {
            [self showDialogOfType:DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_TRY_AGAIN withData:0 withAnimation:NO];
        }
    }
}

/*********************  Dialog Handling **************************/

-(void)showDialogOfType:(int)dialogType withData:(void *)data withAnimation:(BOOL)animate
{
    switch (dialogType)
    {
        case DIALOG_TYPE_ADD_MOVES:
            [self showDialog:@"AddMovesDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_ADD_STAR:
            [self showDialog:@"AddStarDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_ADD_HURDLE_SMASHER:
            [self showDialog:@"AddHurdleSmasherDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_ADD_BRIDGE:
            [self showDialog:@"AddBridgeDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_ADD_COINS:
            [self showDialog:@"AddCoinsDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_REMOVE_ADS:
            [self showDialog:@"RemoveAdsDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_GAME_SUCCESS:
            [self showDialog:@"GameSuccessDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_GAME_FAILED:
            [self showDialog:@"GameFailedDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_GAME_FINISHED:
            [self showDialog:@"GameFinishedDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_GAME_MENU:
            [self showDialog:@"GameMenuDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_STAR_PLACEMENT_INFO:
            [self showDialog:@"StarPlacementInfoDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_STAR_PLACEMENT_TRY_AGAIN:
            [self showDialog:@"StarPlacementTryAgainDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO:
            [self showDialog:@"HurdleSmasherPlacementInfoDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_TRY_AGAIN:
            [self showDialog:@"HurdleSmasherPlacementTryAgainDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_BRIDGE_PLACEMENT_INFO:
            [self showDialog:@"BridgePlacementInfoDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_BRIDGE_PLACEMENT_TRY_AGAIN:
            [self showDialog:@"BridgePlacementTryAgainDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_IAP_PURCHASE_FAILED:
            [self showDialog:@"IAPPurchaseFailedDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_IAP_RESTORE_FAILED:
            [self showDialog:@"IAPRestoreFailedDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_INTRODUCE_STARS:
            [self showDialog:@"IntroduceStarsDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_INTRODUCE_HURDLE_SMASHERS:
            [self showDialog:@"IntroduceHurdleSmashersDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_INTRODUCE_BRIDGES:
            [self showDialog:@"IntroduceBridgesDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_DO_YOU_LIKE_GAME:
            [self showDialog:@"DoYouLikeGameDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
        case DIALOG_TYPE_RATE_GAME:
            [self showDialog:@"RateGameDialog" withDialogType:dialogType withData:data withStrData:nil withAnimation:animate autoHide:NO];
            break;
    }
}

/**
 Show the specific dialog using the storyBoardID.
 **/
-(void)showDialog:(NSString *)storyBoardID withDialogType:(int)dialogType withData:(void *)data withStrData:(NSString *)strData withAnimation:(BOOL)animate autoHide:(BOOL)autoHide
{
    MFGameDialogController *controller = [self.storyboard instantiateViewControllerWithIdentifier:storyBoardID];
    controller.dialogType = dialogType;
    
    //set the delegate
    controller.delegate = self;
    controller.mIAPManager = self.mIAPManager;
    controller.data = data;
    controller.strData = strData;
    controller.autoHide = autoHide;
    
    /**
     Show the dialog view on top of the current view as an overlay
     **/
    UIViewController *dst = controller;
    UIViewController *src = self;
    
    [src addChildViewController:dst];
    [src.view addSubview:dst.view];
    [src.view bringSubviewToFront:dst.view];
    
    CGRect frame;
    
    frame.size.height = src.view.frame.size.height;
    frame.size.width = src.view.frame.size.width;
    
    frame.origin.x = src.view.bounds.origin.x;
    frame.origin.y = src.view.bounds.origin.y;
    
    dst.view.frame = frame;
    
    /**
     Animate the dialog view to show, to give a nice effect.
     **/
    float animationDelay = 0.3f;
    if (animate)
    {
        animationDelay = 1.0f;
    }
    
    [UIView animateWithDuration:animationDelay animations:^{
        
        //dst.view.alpha = 0.5f;
        dst.view.alpha = 1.0f;
        
        NSLog(@"%@", NSStringFromCGRect(dst.view.frame));
    }];
    
}

/**
 Called when a dialog button was selected (and dialog was dismissed).
 **/
-(void) gameDialogOptionSelected:(int)dialogType WithOption:(int) option
{
    //stop any sound that might be playing
    [self stopSound];
    
    if (dialogType == DIALOG_TYPE_ADD_MOVES)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) //Add Moves selected
        {
            int numCoins = getCoins();
            int numCoinsForMoves = getNumCoinsForMoves();
            if (numCoins >= numCoinsForMoves)
            {
                numCoins -= numCoinsForMoves;
                [self updateCoinsEarned:numCoins];
                
                int maxMoves = getMaxMoves(self.gridHandle);
                maxMoves += 5;
                setMaxMoves(self.gridHandle, maxMoves);
                //update moves label
                [self updateMovesLabel:(getMaxMoves(self.gridHandle) - getCurrMove(self.gridHandle))];
            }
            else
            {
                //show the add coins dialog
                [self addCoinsWithShortfall:(numCoinsForMoves - numCoins)];
                
                self.mLastDialogData = DIALOG_DATA_FROM_ADD_MOVES_DIALOG;
            }
        }
        else if (option == GAME_DIALOG_NEGATIVE_ACTION_1)
        {
            /**
             if the user landed here after having "failed" the game,
             show him the game menu dialog again.
             **/
            if (getCurrMove(self.gridHandle) == getMaxMoves(self.gridHandle))
            {
                [self showDialogOfType:DIALOG_TYPE_GAME_MENU withData:0 withAnimation:NO];
            }
        }
    }
    else if (dialogType == DIALOG_TYPE_GAME_MENU) // Game Menu / Exit dialog
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) // Replay Level
        {
            [self startNewGame:self.gameLevel];
        }
        else if (option == GAME_DIALOG_POSITIVE_ACTION_2) // View Levels
        {
            [self dismissViewControllerAnimated:NO completion:nil];
        }
        else if (option == GAME_DIALOG_NEGATIVE_ACTION_1)
        {
            /** If hte uesr landed here after having failed the game,
             then take him back to the levels screen.
             **/
            if (getCurrMove(self.gridHandle) == getMaxMoves(self.gridHandle))
            {
                [self dismissViewControllerAnimated:NO completion:nil];
            }
        }
    }
    else if (dialogType == DIALOG_TYPE_GAME_SUCCESS)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) // Next Game
        {
            [self startNewGame:(self.gameLevel + 1)];
            
            [self checkRateGameReminder];
        }
        else if (option == GAME_DIALOG_NEGATIVE_ACTION_1) //View Levels
        {
            [self dismissViewControllerAnimated:NO completion:nil];
        }
    }
    else if (dialogType == DIALOG_TYPE_GAME_FAILED)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) // Play On
        {
            [self showDialogOfType:DIALOG_TYPE_ADD_MOVES withData:0 withAnimation:NO];
        }
        else if (option == GAME_DIALOG_NEGATIVE_ACTION_1) // End Game
        {
            [self showDialogOfType:DIALOG_TYPE_GAME_MENU withData:0 withAnimation:NO];
        }
    }
    else if (dialogType == DIALOG_TYPE_ADD_STAR)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1 || option == GAME_DIALOG_POSITIVE_ACTION_2) // Add Star(s)
        {
            int numStarsToBuy = 0;
            if (option == GAME_DIALOG_POSITIVE_ACTION_1)
            {
                numStarsToBuy = 1;
            }
            else if (option == GAME_DIALOG_POSITIVE_ACTION_2)
            {
                numStarsToBuy = 2;
            }
            int numCoins = getCoins();
            int numCoinsForStar = getNumCoinsForStar(numStarsToBuy);
            if (numCoins >= numCoinsForStar)
            {
                numCoins -= numCoinsForStar;
                [self updateCoinsEarned:numCoins];
                
                /*
                //enter state where game view detects tap on a specific cell
                [self.gameView enableDisableTouchInput:YES];
                self.mStarPlacementMode = YES;
                
                [self showDialogOfType:DIALOG_TYPE_STAR_PLACEMENT_INFO withData:0 withAnimation:NO];
                */
                int numStars = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_STARS_EARNED];
                numStars += numStarsToBuy;
                [[NSUserDefaults standardUserDefaults] setInteger:numStars forKey: @PREFERENCE_TOTAL_STARS_EARNED];
                
                [self refreshLifelinesUI];
            }
            else
            {
                [self addCoinsWithShortfall:(numCoinsForStar - numCoins)];
                
                self.mLastDialogData = DIALOG_DATA_FROM_ADD_STAR_DIALOG;
            }
        }
    }
    else if (dialogType == DIALOG_TYPE_ADD_HURDLE_SMASHER)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1 || option == GAME_DIALOG_POSITIVE_ACTION_2) //Add Hurdle Smasher
        {
            int numSmashersToBuy = 0;
            if (option == GAME_DIALOG_POSITIVE_ACTION_1)
            {
                numSmashersToBuy = 1;
            }
            else if (option == GAME_DIALOG_POSITIVE_ACTION_2)
            {
                numSmashersToBuy = 2;
            }
            
            int numCoins = getCoins();
            int numCoinsForHurdleSmasher = getNumCoinsForHurdleSmasher(numSmashersToBuy);
            if (numCoins >= numCoinsForHurdleSmasher)
            {
                numCoins -= numCoinsForHurdleSmasher;
                [self updateCoinsEarned:numCoins];
                
                //enter state where game view detects tap on a specific cell
                /*
                [self.gameView enableDisableTouchInput:YES];
                self.mHurdleSmasherMode = YES;
                
                [self showDialogOfType:DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO withData:0 withAnimation:NO];
                 */
                int numSmashers = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED];
                numSmashers += numSmashersToBuy;
                [[NSUserDefaults standardUserDefaults] setInteger:numSmashers forKey: @PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED];
                
                [self refreshLifelinesUI];
            }
            else
            {
                [self addCoinsWithShortfall:(numCoinsForHurdleSmasher - numCoins)];
                
                self.mLastDialogData = DIALOG_DATA_FROM_ADD_HURDLE_SMASHER_DIALOG;
            }
        }
    }
    else if (dialogType == DIALOG_TYPE_ADD_BRIDGE)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1 || option == GAME_DIALOG_POSITIVE_ACTION_2) //Add Bridge
        {
            int numBridgesToBuy = 0;
            if (option == GAME_DIALOG_POSITIVE_ACTION_1)
            {
                numBridgesToBuy = 1;
            }
            else if (option == GAME_DIALOG_POSITIVE_ACTION_2)
            {
                numBridgesToBuy = 2;
            }
            
            int numCoins = getCoins();
            int numCoinsForBridge = getNumCoinsForBridge(numBridgesToBuy);
            if (numCoins >= numCoinsForBridge)
            {
                numCoins -= numCoinsForBridge;
                [self updateCoinsEarned:numCoins];
                
                //enter state where game view detects tap on a specific cell
                /*
                [self.gameView enableDisableTouchInput:YES];
                self.mBridgeMode = YES;
                
                [self showDialogOfType:DIALOG_TYPE_BRIDGE_PLACEMENT_INFO withData:0 withAnimation:NO];
                */
                int numBridges = (int)[[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_TOTAL_BRIDGES_EARNED];
                numBridges += numBridgesToBuy;
                [[NSUserDefaults standardUserDefaults] setInteger:numBridges forKey: @PREFERENCE_TOTAL_BRIDGES_EARNED];
                
                [self refreshLifelinesUI];
            }
            else
            {
                [self addCoinsWithShortfall:(numCoinsForBridge - numCoins)];
                
                self.mLastDialogData = DIALOG_DATA_FROM_ADD_BRIDGE_DIALOG;
            }
        }
    }
    else if (dialogType == DIALOG_TYPE_ADD_COINS)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) //Add 500 Coins
        {
            [self.mIAPManager startPurchase:@ IAP_COINS_FIRST];
        }
        else if (option == GAME_DIALOG_POSITIVE_ACTION_2)
        {
            [self.mIAPManager startPurchase:@ IAP_COINS_SECOND];
        }
        else if (option == GAME_DIALOG_POSITIVE_ACTION_3)
        {
            [self.mIAPManager startPurchase:@ IAP_COINS_THIRD];
        }
        else if (option == GAME_DIALOG_POSITIVE_ACTION_4)
        {
            [self.mIAPManager startPurchase:@ IAP_COINS_FOURTH];
        }
        else if (option == GAME_DIALOG_NEGATIVE_ACTION_1)
        {
            //reset this as the user cancelled the purchase
            self.mLastDialogData = DIALOG_DATA_NONE;
            
            /**
             if the user landed here after having "failed" the game,
             show him the game menu dialog again.
             **/
            if (getCurrMove(self.gridHandle) == getMaxMoves(self.gridHandle))
            {
                [self showDialogOfType:DIALOG_TYPE_GAME_MENU withData:0 withAnimation:NO];
            }
        }
    }
    else if (dialogType == DIALOG_TYPE_IAP_PURCHASE_FAILED)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1)
        {
            /**
             If we reached here in the middle of another workflow, try to
             reinstante that.
             **/
            if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_MOVES_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_MOVES withData:0 withAnimation:NO];
            }
            else if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_STAR_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_STAR withData:0 withAnimation:NO];
            }
            else if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_HURDLE_SMASHER_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_HURDLE_SMASHER withData:0 withAnimation:NO];
            }
            else if (self.mLastDialogData == DIALOG_DATA_FROM_ADD_BRIDGE_DIALOG)
            {
                [self showDialogOfType:DIALOG_TYPE_ADD_BRIDGE withData:0 withAnimation:NO];
            }
            self.mLastDialogData = DIALOG_DATA_NONE;
        }
    }
    else if (dialogType == DIALOG_TYPE_REMOVE_ADS)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1)
        {
            [self.mIAPManager startPurchase:@ IAP_REMOVE_ADS];
        }
        else if (option == GAME_DIALOG_POSITIVE_ACTION_2)
        {
            [self.mIAPManager restorePurchases];
        }
    }
    else if (dialogType == DIALOG_TYPE_GAME_FINISHED) //end of entire game, go back to levels
    {
        [self dismissViewControllerAnimated:NO completion:nil];
    }
    else if (dialogType == DIALOG_TYPE_STAR_PLACEMENT_INFO)
    {
        /** Enter the star placement mode **/
        
        [self.gameView enableDisableTouchInput:YES];
        self.mStarPlacementMode = YES;
        
        [self refreshLifelinesUI];
    }
    else if (dialogType == DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO)
    {
        /** Enter the hurdle smasher placement mode **/
        
        [self.gameView enableDisableTouchInput:YES];
        self.mHurdleSmasherMode = YES;
        
        [self refreshLifelinesUI];
    }
    else if (dialogType == DIALOG_TYPE_BRIDGE_PLACEMENT_INFO)
    {
        /** Enter the bridge placement mode **/
        
        [self.gameView enableDisableTouchInput:YES];
        self.mBridgeMode = YES;
        
        [self refreshLifelinesUI];
    }
    else if (dialogType == DIALOG_TYPE_DO_YOU_LIKE_GAME)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) //Love It
        {
            [self showDialogOfType:DIALOG_TYPE_RATE_GAME withData:NULL withAnimation:NO];
        }
        else if (option == GAME_DIALOG_NEGATIVE_ACTION_1) // Don't love it
        {
            //show the email composer window
            if ([MFMailComposeViewController canSendMail]) {
                MFMailComposeViewController *composeViewController = [[MFMailComposeViewController alloc] initWithNibName:nil bundle:nil];
                [composeViewController setMailComposeDelegate:self];
                [composeViewController setToRecipients:@[@FEEDBACK_EMAIL]];
                NSString *subject = nil;
                if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
                {
                    
                    subject = [NSString stringWithFormat:NSLocalizedString(@"feedback_email_subject", @""), "iPad"];
                }
                else
                {
                    subject = [NSString stringWithFormat:NSLocalizedString(@"feedback_email_subject", @""), "iPhone"];
                }
                [composeViewController setSubject:subject];
                
                [self presentViewController:composeViewController animated:YES completion:nil];
            }
        }
    }
    else if (dialogType == DIALOG_TYPE_RATE_GAME)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) //Rate It Now
        {
            int rateGame = 0; //don't want this dialog to come up again
            
            [[NSUserDefaults standardUserDefaults] setInteger:rateGame forKey: @PREFERENCE_RATE_GAME_REMINDER];
            
            NSString *iTunesLink = @ITUNES_APP_URL;
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:iTunesLink]];
        }
        else if (option == GAME_DIALOG_POSITIVE_ACTION_2) //Remind me later
        {
            int rateGame = INITIAL_RATE_GAME_REMINDER;
                
            [[NSUserDefaults standardUserDefaults] setInteger:rateGame forKey: @PREFERENCE_RATE_GAME_REMINDER];
        }
        else if (option == GAME_DIALOG_POSITIVE_ACTION_3) //Already Rated
        {
            int rateGame = 0; //don't want this dialog to come up again
            
            [[NSUserDefaults standardUserDefaults] setInteger:rateGame forKey: @PREFERENCE_RATE_GAME_REMINDER];
        }
    }
}

/*********************  System Callbacks **************************/

//hide status bar during game play
- (BOOL)prefersStatusBarHidden {
    return YES;
}

@end
