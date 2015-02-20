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

@interface MFGameViewController ()
{
    SystemSoundID mCurrentlyPlayingSound, mButtonClickSoundID, mGameSuccessSoundID, mGameFailedSoundID, mHurdleSmashedSoundID, mStarPlacedSoundID;
    NSURL *mCurrentlyPlayingSoundURL, *mButtonClickSoundURL, *mGameSuccessSoundURL, *mGameFailedSoundURL, *mHurdleSmashedSoundURL, *mStarPlacedSoundURL;
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
@property (strong, nonatomic) IBOutlet MFGameView *gameView; //UIView that renders the actual game board
@property BOOL mStarPlacementMode;
@property BOOL mHurdleSmasherMode;
@property BOOL mEnableSound;
@property (strong, nonatomic) IBOutlet ADBannerView *mAdBannerView;
@property BOOL mAdBannerVisible;
@property BOOL mAdsRemoved; //whether ads are removed by user
@property (strong, nonatomic) IBOutlet NSLayoutConstraint *mColorButtonBottomConstaints;
@property MFIAPManager *mIAPManager; //The In-App Purchase Manager
@property UIAlertView *failAlertView, *successAlertView, *exitAlertView, *addMovesAlertView, *addStarAlertView, *addHurdleSmasherAlertView, *addCoinsAlertView, *finishedAllLevelsView;
@property long gridHandle; //handle to the grid object in C++ code

@end

@implementation MFGameViewController

- (void)viewDidLoad
{
    NSLog(@"gameviewcontroller, viewdidload started, mAddBannerVisible = %d", self.mAdBannerVisible);
    [super viewDidLoad];
    
    [MFUtils setBackgroundImage:self];

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
     self.gameView = nil;
    
    /**
     Get rid of ad banner.
     **/
     [self.mAdBannerView removeFromSuperview];
     self.mAdBannerView.delegate = nil;
     self.mAdBannerView = nil;
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
-(void)onPurchaseFinished:(NSString *)pid WithStatus:(BOOL)status
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
        }
    }
    else //purchase failed or canceled
    {
        [self showDialogOfType:DIALOG_TYPE_IAP_PURCHASE_FAILED withData:0];
    }
}

/**
 Called when a restore transaction is triggered.
 **/
-(void)onPurchaseRestored:(NSString *)pid WithStatus:(BOOL)status
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
        [self showDialogOfType:DIALOG_TYPE_IAP_RESTORE_FAILED withData:0];
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
        [self.view removeConstraint: self.mColorButtonBottomConstaints];
        self.mColorButtonBottomConstaints = [NSLayoutConstraint constraintWithItem:self.mAdBannerView
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.bottomLayoutGuide
                                                                         attribute:NSLayoutAttributeBottom
                                                                        multiplier:1.0
                                                                          constant:self.mAdBannerView.frame.size.height];
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
    if (!self.mAdBannerVisible)
    {
        [self.view removeConstraint: self.mColorButtonBottomConstaints];
        self.mColorButtonBottomConstaints = [NSLayoutConstraint constraintWithItem:self.mAdBannerView
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.bottomLayoutGuide
                                                                         attribute:NSLayoutAttributeBottom
                                                                        multiplier:1.0
                                                                          constant:0.0]; //0.0 ensures the bottom of the Ad View aligns with the bottom layout guide
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
        [self.view removeConstraint: self.mColorButtonBottomConstaints];
        self.mColorButtonBottomConstaints = [NSLayoutConstraint constraintWithItem:self.mAdBannerView
                                                                         attribute:NSLayoutAttributeBottom
                                                                         relatedBy:NSLayoutRelationEqual
                                                                            toItem:self.bottomLayoutGuide
                                                                         attribute:NSLayoutAttributeTop
                                                                        multiplier:1.0
                                                                          constant:self.mAdBannerView.frame.size.height]; //the banner height ensures the bottom of the Ad View is exactly this much below the bottom layout guide (just hanging below the screen edge)
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
    [self showDialogOfType:DIALOG_TYPE_REMOVE_ADS withData:0];
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
        [self showDialogOfType:DIALOG_TYPE_GAME_FINISHED withData:0];
        
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
    [self showDialogOfType:DIALOG_TYPE_ADD_MOVES withData:0];
}

/**
 The Add Hurdle Smasher button was pressed.
 **/
- (IBAction)addHurdleSmasher:(id)sender {
    [self showDialogOfType:DIALOG_TYPE_ADD_HURDLE_SMASHER withData:0];
}

/**
 The Add Star button was pressed.
 **/
- (IBAction)addStar:(id)sender {
    [self showDialogOfType:DIALOG_TYPE_ADD_STAR withData:0];
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
    [self showDialogOfType:DIALOG_TYPE_ADD_COINS withData:shortfall];
}

/**
 Handler of the menu button on the game board.
 **/
- (IBAction)handleExit:(id)sender {
    [self showDialogOfType:DIALOG_TYPE_GAME_MENU withData:0];
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
        
        [self showDialogOfType:DIALOG_TYPE_GAME_SUCCESS withData:0];
    }
    else if (result[0] == RESULT_FAILED) //failed
    {
        [self playSound:mGameFailedSoundID];
        
        [self showDialogOfType:DIALOG_TYPE_GAME_FAILED withData:0];
    }
    else
    {
        [self playSound:mButtonClickSoundID];
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

/*********************  UI Updates **************************/

/**
 Logic to show/hide the Star or Hurdle Smasher capabilities.
 **/
-(void)refreshLifelinesUI
{
    if (self.gameLevel == getMinLevelToAddStars())
    {
        [self showDialogOfType:DIALOG_TYPE_INTRODUCE_STARS withData:0];
    }
    else if (self.gameLevel == getMinLevelToAddHurdleSmasher())
    {
        [self showDialogOfType:DIALOG_TYPE_INTRODUCE_HURDLE_SMASHERS withData:0];
    }
    
    if (self.gameLevel < getMinLevelToAddStars())
    {
        self.mAddStarButton.hidden = YES;
    }
    else
    {
        self.mAddStarButton.hidden = NO;
    }
    
    if (self.gameLevel < getMinLevelToAddHurdleSmasher())
    {
        self.mAddHurdleSmasherButton.hidden = YES;
    }
    else
    {
        self.mAddHurdleSmasherButton.hidden = NO;
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
    self.mAddStarButton.enabled = enable;
    self.mAddHurdleSmasherButton.enabled = enable;
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
            
            [self enableDisableAllButtons:YES];
        }
        else //couldn't place the star, so keep trying
        {
            [self showDialogOfType:DIALOG_TYPE_STAR_PLACEMENT_TRY_AGAIN withData:0];
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
            
            [self enableDisableAllButtons:YES];
        }
        else //couldn't find a hurdle.  So keep trying
        {
            [self showDialogOfType:DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_TRY_AGAIN withData:0];
        }
    }
}

/*********************  Dialog Handling **************************/

-(void)showDialogOfType:(int)dialogType withData:(int)data
{
    switch (dialogType)
    {
        case DIALOG_TYPE_ADD_MOVES:
            [self showDialog:@"AddMovesDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_ADD_STAR:
            [self showDialog:@"AddStarDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_ADD_HURDLE_SMASHER:
            [self showDialog:@"AddHurdleSmasherDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_ADD_COINS:
            [self showDialog:@"AddCoinsDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_REMOVE_ADS:
            [self showDialog:@"RemoveAdsDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_GAME_SUCCESS:
            [self showDialog:@"GameSuccessDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_GAME_FAILED:
            [self showDialog:@"GameFailedDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_GAME_FINISHED:
            [self showDialog:@"GameFinishedDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_GAME_MENU:
            [self showDialog:@"GameMenuDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_NOT_CONNECTED:
            [self showDialog:@"NotConnectedDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_STAR_PLACEMENT_INFO:
            [self showDialog:@"StarPlacementInfoDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_STAR_PLACEMENT_TRY_AGAIN:
            [self showDialog:@"StarPlacementTryAgainDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO:
            [self showDialog:@"HurdleSmasherPlacementInfoDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_TRY_AGAIN:
            [self showDialog:@"HurdleSmasherPlacementTryAgainDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_IAP_PURCHASE_FAILED:
            [self showDialog:@"IAPPurchaseFailedDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_IAP_CONSUME_FAILED:
            [self showDialog:@"IAPConsumeFailedDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_IAP_QUERY_FAILED:
            [self showDialog:@"IAPQueryFailedDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_IAP_RESTORE_FAILED:
            [self showDialog:@"IAPRestoreFailedDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_INTRODUCE_STARS:
            [self showDialog:@"IntroduceStarsDialog" withDialogType:dialogType withData:data];
            break;
        case DIALOG_TYPE_INTRODUCE_HURDLE_SMASHERS:
            [self showDialog:@"IntroduceHurdleSmashersDialog" withDialogType:dialogType withData:data];
            break;
    }
}

/**
 Show the specific dialog using the storyBoardID.
 **/
-(void)showDialog:(NSString *)storyBoardID withDialogType:(int)dialogType withData:(int)data
{
    MFGameDialogController *controller = [self.storyboard instantiateViewControllerWithIdentifier:storyBoardID];
    controller.dialogType = dialogType;
    
    //set the delegate
    controller.delegate = self;
    controller.mIAPManager = self.mIAPManager;
    controller.data = data;
    
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
    [UIView animateWithDuration:0.3f animations:^{
        
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
                [self showDialogOfType:DIALOG_TYPE_GAME_MENU withData:0];
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
            [self showDialogOfType:DIALOG_TYPE_ADD_MOVES withData:0];
        }
        else if (option == GAME_DIALOG_NEGATIVE_ACTION_1) // End Game
        {
            [self showDialogOfType:DIALOG_TYPE_GAME_MENU withData:0];
        }
    }
    else if (dialogType == DIALOG_TYPE_ADD_STAR)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) // Add Star
        {
            int numCoins = getCoins();
            int numCoinsForStar = getNumCoinsForStar();
            if (numCoins >= numCoinsForStar)
            {
                numCoins -= numCoinsForStar;
                [self updateCoinsEarned:numCoins];
                
                //enter state where game view detects tap on a specific cell
                [self.gameView enableDisableTouchInput:YES];
                self.mStarPlacementMode = YES;
                
                [self showDialogOfType:DIALOG_TYPE_STAR_PLACEMENT_INFO withData:0];
                
                [self enableDisableAllButtons:NO];
            }
            else
            {
                [self addCoinsWithShortfall:(numCoinsForStar - numCoins)];
            }
        }
    }
    else if (dialogType == DIALOG_TYPE_ADD_HURDLE_SMASHER)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) //Add Hurdle Smasher
        {
            int numCoins = getCoins();
            int numCoinsForHurdleSmasher = getNumCoinsForHurdleSmasher();
            if (numCoins >= numCoinsForHurdleSmasher)
            {
                numCoins -= numCoinsForHurdleSmasher;
                [self updateCoinsEarned:numCoins];
                
                //enter state where game view detects tap on a specific cell
                [self.gameView enableDisableTouchInput:YES];
                self.mHurdleSmasherMode = YES;
                
                [self showDialogOfType:DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO withData:0];
                
                [self enableDisableAllButtons:NO];
            }
            else
            {
                [self addCoinsWithShortfall:(numCoinsForHurdleSmasher - numCoins)];
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
            /**
             if the user landed here after having "failed" the game,
             show him the game menu dialog again.
             **/
            if (getCurrMove(self.gridHandle) == getMaxMoves(self.gridHandle))
            {
                [self showDialogOfType:DIALOG_TYPE_GAME_MENU withData:0];
            }
        }
    }
    else if (dialogType == DIALOG_TYPE_IAP_PURCHASE_FAILED)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1)
        {
            //do nothing beyond dismissing the dialog
        }
    }
    else if (dialogType == DIALOG_TYPE_REMOVE_ADS)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1)
        {
            [self.mIAPManager startPurchase:@ IAP_REMOVE_ADS];
        }
    }
}

/*********************  System Callbacks **************************/

//hide status bar during game play
- (BOOL)prefersStatusBarHidden {
    return YES;
}

@end
