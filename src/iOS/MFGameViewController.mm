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

@interface MFGameViewController ()
@property (strong, nonatomic) IBOutlet UIButton *mSoundButton;
@property (strong, nonatomic) IBOutlet UILabel *mLevelsLabel;
@property (strong, nonatomic) IBOutlet UILabel *coinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *movesLable; //UILabel that displays the Moves header
@property (strong, nonatomic) IBOutlet MFGameView *gameView; //UIView that renders the actual game board
@end

@implementation MFGameViewController
- (IBAction)soundButtonPressed:(id)sender
{
    self.mEnableSound = [[NSUserDefaults standardUserDefaults] boolForKey:@PREFERENCE_SOUND];

    self.mEnableSound = !self.mEnableSound;
    [[NSUserDefaults standardUserDefaults] setBool:self.mEnableSound forKey:@PREFERENCE_SOUND];
    
    UIButton *button = (UIButton *)sender;
    [self refreshSoundButton:button];
}

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

- (IBAction)removeAds:(id)sender {
}

- (IBAction)addHurdleSmasher:(id)sender {
    //ask the user what he wants to do next
    [self showDialogOfType:DIALOG_TYPE_ADD_HURDLE_SMASHER];
}
- (IBAction)addStar:(id)sender {
    //ask the user what he wants to do next
    [self showDialogOfType:DIALOG_TYPE_ADD_STAR];
}

- (IBAction)addCoins:(id)sender
{
    if ([SKPaymentQueue canMakePayments])
    {
        SKProductsRequest *productsRequest = [[SKProductsRequest alloc]
                                              initWithProductIdentifiers:[NSSet setWithArray:self.products]];
        productsRequest.delegate = self;
        [productsRequest start];
    }
    else
    {
        [self showDialogOfType:DIALOG_TYPE_NOT_CONNECTED];
    }

    
    
}

// SKProductsRequestDelegate protocol method
- (void)productsRequest:(SKProductsRequest *)request
     didReceiveResponse:(SKProductsResponse *)response
{
    BOOL allIsWell = YES;
    
    
    for (NSString *invalidIdentifier in response.invalidProductIdentifiers) {
        for (int i = 0; i < [self.products count]; i++)
        {
            if ([[self.products objectAtIndex:i] isEqualToString:invalidIdentifier])
            {
                //something's wrong
                allIsWell = NO;
                break;
            }
        }
        
        if (!allIsWell)
        {
            break;
        }
    }
    
    if (!allIsWell)
    {
        [self showDialogOfType:DIALOG_TYPE_NOT_CONNECTED];
        
        return;
    }
    
    self.products = response.products;

    [self addCoins];
}

-(void)addCoins
{
    SKProduct *product0 = [self.products objectAtIndex:0];
    SKProduct *product1 = [self.products objectAtIndex:1];
    SKProduct *product2 = [self.products objectAtIndex:2];
    SKProduct *product3 = [self.products objectAtIndex:3];
    
    NSString *formattedPrice0 = [self formatIAPPrice:product0.price WithLocale:product0.priceLocale];
    NSString *iap_first_price = @"Add 500 Coins";
    iap_first_price = [iap_first_price stringByAppendingString:formattedPrice0];
    
    NSString *formattedPrice1 = [self formatIAPPrice:product0.price WithLocale:product1.priceLocale];
    NSString *iap_second_price = @"Add 1000 Coins";
    iap_second_price = [iap_second_price stringByAppendingString:formattedPrice1];
    
    NSString *formattedPrice2 = [self formatIAPPrice:product0.price WithLocale:product2.priceLocale];
    NSString *iap_third_price = @"Add 2500 Coins";
    iap_third_price = [iap_third_price stringByAppendingString:formattedPrice2];
    
    NSString *formattedPrice3 = [self formatIAPPrice:product0.price WithLocale:product3.priceLocale];
    NSString *iap_fourth_price = @"Add 5000 Coins";
    iap_fourth_price = [iap_fourth_price stringByAppendingString:formattedPrice3];
    
    
    [self showDialogOfType:DIALOG_TYPE_ADD_COINS];
}

-(NSString *)formatIAPPrice:(NSNumber *)price WithLocale:(NSLocale *)locale
{
    NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
    [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
    [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [numberFormatter setLocale:locale];
    NSString *formattedPrice = [numberFormatter stringFromNumber:price];
    
    return formattedPrice;

}

- (void)request:(SKRequest *)request
didFailWithError:(NSError *)error
{
    NSLog(@"request didFailWithError called");
}

-(void)showDialogOfType:(int)dialogType
{
    switch (dialogType)
    {
        case DIALOG_TYPE_ADD_MOVES:
            [self showDialog:@"AddMovesDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_ADD_STAR:
            [self showDialog:@"AddStarDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_ADD_HURDLE_SMASHER:
            [self showDialog:@"AddHurdleSmasherDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_ADD_COINS:
            [self showDialog:@"AddCoinsDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_REMOVE_ADS:
            [self showDialog:@"RemoveAdsDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_GAME_SUCCESS:
            [self showDialog:@"GameSuccessDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_GAME_FAILED:
            [self showDialog:@"GameFailedDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_GAME_FINISHED:
            [self showDialog:@"GameFinishedDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_GAME_MENU:
            [self showDialog:@"GameMenuDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_NOT_CONNECTED:
            [self showDialog:@"NotConnectedDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_STAR_PLACEMENT_INFO:
            [self showDialog:@"StarPlacementInfoDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_STAR_PLACEMENT_TRY_AGAIN:
            [self showDialog:@"StarPlacementTryAgainDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO:
            [self showDialog:@"HurdleSmasherPlacementInfoDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_TRY_AGAIN:
            [self showDialog:@"HurdleSmasherPlacementTryAgainDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_IAP_PURCHASE_FAILED:
            [self showDialog:@"IAPPurchaseFailedDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_IAP_CONSUME_FAILED:
            [self showDialog:@"IAPConsumeFailedDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_IAP_QUERY_FAILED:
            [self showDialog:@"IAPQueryFailedDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_INTRODUCE_STARS:
            [self showDialog:@"IntroduceStarsDialog" withDialogType:dialogType];
            break;
        case DIALOG_TYPE_INTRODUCE_HURDLE_SMASHERS:
            [self showDialog:@"IntroduceHurdleSmashersDialog" withDialogType:dialogType];
            break;
    }
}

-(void)showDialog:(NSString *)storyBoardID withDialogType:(int)dialogType
{
    MFGameDialogController *controller = [self.storyboard instantiateViewControllerWithIdentifier:storyBoardID];
    controller.dialogType = dialogType;
    
    //set the delegate
    controller.delegate = self;

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
    
    
    
    [UIView animateWithDuration:0.3f animations:^{
        
        //dst.view.alpha = 0.5f;
        dst.view.alpha = 1.0f;
        
        NSLog(@"%@", NSStringFromCGRect(dst.view.frame));
    }];

}
- (IBAction)addMoves:(id)sender {
    [self showDialogOfType:DIALOG_TYPE_ADD_MOVES];
}

/**
 Handler of the "X" button on the game board.
 **/
- (IBAction)handleExit:(id)sender {
    [self showDialogOfType:DIALOG_TYPE_GAME_MENU];
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
        
        setCoins(getCoins());
        
        updateCoinsLabel:getCoins();
        
        //update last completed preference
        int lastCompletedLevel = [[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_LAST_COMPLETED_LEVEL];
        if (lastCompletedLevel <= self.gameLevel)
        {
            [[NSUserDefaults standardUserDefaults] setInteger:self.gameLevel forKey: @PREFERENCE_LAST_COMPLETED_LEVEL];
        }
        
        //unlock the next level
        int lastUnlockedLevel = [[NSUserDefaults standardUserDefaults] integerForKey:@PREFERENCE_LAST_UNLOCKED_LEVEL];
        if (lastUnlockedLevel <= self.gameLevel)
        {
            lastUnlockedLevel ++;
            [[NSUserDefaults standardUserDefaults] setInteger:lastUnlockedLevel forKey: @PREFERENCE_LAST_UNLOCKED_LEVEL];
        }
        
        [self showDialogOfType:DIALOG_TYPE_GAME_SUCCESS];
    }
    else if (result[0] == RESULT_FAILED) //failed
    {
        [self playSound:mGameFailedSoundID];
        
        [self showDialogOfType:DIALOG_TYPE_GAME_FAILED];
    }
    else
    {
        [self playSound:mButtonClickSoundID];
    }
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    //self.gridHandle = 0;
    
    [self startNewGame:self.gameLevel];
    
    //set self as delegate for the tap protocol in the MFGameView
    self.gameView.delegate = self;
    
    //load the bundled product list
    NSString *id_iap_remove_ads = @IAP_REMOVE_ADS;
    NSString *id_iap_coins_first = @ IAP_COINS_FIRST;
    NSString *id_iap_coins_second = @ IAP_COINS_SECOND;
    NSString *id_iap_coins_third = @ IAP_COINS_THIRD;
    NSString *id_iap_coins_fourth = @ IAP_COINS_FOURTH;
    self.products = [NSArray arrayWithObjects: id_iap_remove_ads, id_iap_coins_first, id_iap_coins_second,
                     id_iap_coins_third, id_iap_coins_fourth, nil];
    
    //set font typefaces
    [self.mLevelsLabel setFont:[UIFont fontWithName:@"ArchitectsDaughter" size:15]];
    [self.coinsLabel setFont:[UIFont fontWithName:@"ArchitectsDaughter" size:15]];
    [self.movesLable setFont:[UIFont fontWithName:@"ArchitectsDaughter" size:15]];
    
    //add background image
    UIImage* _backGround = [UIImage imageNamed:@"bg_sky_blue.png"];
    UIImageView* _backGroundView = [[UIImageView alloc] initWithImage:_backGround];
    
    _backGroundView.frame = self.view.frame;
    _backGroundView.contentMode = UIViewContentModeScaleToFill;
    
    [self.view addSubview:_backGroundView];
    [self.view sendSubviewToBack:_backGroundView];
    
    //setup sound
    [self setupSound];
}

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

-(void)setupAds
{
    //[self.mAdBannerView removeFromSuperview];
   //self.mAdBannerView.frame = CGRectOffset(self.mAdBannerView.frame, 0, -self.mAdBannerView.frame.size.height);
    //[self.view addSubview:self.mAdBannerView];
    
    //[self.view addSubview:adView];
    
    //self.mAdBannerVisible = YES;
    
    self.mAdBannerView = [[ADBannerView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height, 320, 50)];
    //self.mAdBannerView.frame = CGRectMake(0, self.view.frame.size.height, 320, 50);

    [self.view addSubview:self.mAdBannerView];
    self.mAdBannerView.delegate = self;
}

-(void)viewDidDisappear:(BOOL)animated
{
    if (self.gridHandle != 0)
    {
        deleteGrid(self.gridHandle);
        self.gridHandle = 0;
    }
}

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    [self setupAds];
}

/**
 Start a new game.
 **/
-(void)startNewGame: (int)level
{
    //clear the handle if a game was already underway
    NSLog(@"startNewGame, level = %d, gridHandle = %lx", self.gameLevel, self.gridHandle);
    if (self.gridHandle != 0)
    {
        deleteGrid(self.gridHandle);
        self.gridHandle = 0;
    }
    
    /**
     Check if we've reached the last level!
     **/
    if (level  > getNumLevels())
    {
        [self showDialogOfType:DIALOG_TYPE_GAME_FINISHED];
        
        return;
    }
    
    self.gameLevel = level;
    //initialize a new game grid
    self.gridHandle = createNewGrid(self.gameLevel);
    NSLog(@"startNewGame, created new gridHandle = %lx", self.gridHandle);
    
    //extract data for the game, and then pass on to the UIView for rendering
    int **startPos = getStartPos(self.gridHandle);
    int numStartPos = getNumStartPos(self.gridHandle);
    int **gridData = getGridData(self.gridHandle);
    
    [[self gameView] initializeGameData:gridData WithSize:getGridSize(self.gridHandle) WithNumStartPos:numStartPos WithStartPos:startPos WithMaxMoves:getMaxMoves(self.gridHandle)];
    
    freeGridData(self.gridHandle, gridData);
    freeStartPos(self.gridHandle, startPos);
    gridData = NULL;
    startPos = NULL;
    
    //update the UI to reflect the game moves
    [self updateMovesLabel:(getMaxMoves(self.gridHandle) - getCurrMove(self.gridHandle))];

    
    //update the coins label
    NSString *coinsLabel = [NSString stringWithFormat:@"%d", getCoins()];
    [self.coinsLabel setText:coinsLabel];
    
    NSString *levelLabel = [NSString stringWithFormat:@"Level %d", self.gameLevel];
    [self.mLevelsLabel setText:levelLabel];
    
    [self refreshLifelinesUI];
}

-(void)refreshLifelinesUI
{
    if (self.gameLevel == getMinLevelToAddStars())
    {
        [self showDialogOfType:DIALOG_TYPE_INTRODUCE_STARS];
    }
    else if (self.gameLevel == getMinLevelToAddHurdleSmasher())
    {
        [self showDialogOfType:DIALOG_TYPE_INTRODUCE_HURDLE_SMASHERS];
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

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

/**
 Extract the integral color code from the UIColor
 **/
-(int)GetColorCodeFromUIButton:(UIButton *)button
{
    int tag = button.tag;
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
/**
 Called when the view controller is about to unload.  Clear resources here.
 **/
-(void)dealloc
{
    NSLog(@"dealloc, gridHandle = %lx", self.gridHandle);
    if (self.gridHandle != 0)
    {
        deleteGrid(self.gridHandle);
        self.gridHandle = 0;
    }
}

-(void)handleGameViewTapAtX:(int)x andY:(int)y
{
    if (self.mStarPlacementMode == YES)
    {
        int result = addStartPos(self.gridHandle, x, y);
        if (result == 1)
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
        else
        {
            [self showDialogOfType:DIALOG_TYPE_STAR_PLACEMENT_TRY_AGAIN];
        }
    }
    else if (self.mHurdleSmasherMode == YES)
    {
        int result = smashHurdle(self.gridHandle, x, y);
        if (result == 1)
        {
            [self playSound:mHurdleSmashedSoundID];
            
            self.mHurdleSmasherMode = NO;
            
            int **gridData = getGridData(self.gridHandle);
            [[self gameView] updateGameData:gridData];
            freeGridData(self.gridHandle, gridData);
            gridData = NULL;
            
            [self enableDisableAllButtons:YES];
        }
        else
        {
            [self showDialogOfType:DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_TRY_AGAIN];
        }
    }
}

-(void) playSound:(SystemSoundID)soundID
{
    if (self.mEnableSound)
    {
    //[self stopSound];
        AudioServicesPlaySystemSound(soundID);
        mCurrentlyPlayingSound = soundID;
    }
}

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

- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    if (!self.mAdBannerVisible)
    {
        [UIView beginAnimations:@"animateAdBannerOn" context:NULL];
        
        // Assumes the banner view is just off the bottom of the screen.
        banner.frame = CGRectOffset(banner.frame, 0, -banner.frame.size.height);
        
        [UIView commitAnimations];
        
        self.mAdBannerVisible = YES;
    }
}

- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    NSLog(@"Failed to retrieve ad");
    
    if (self.mAdBannerVisible)
    {
        [UIView beginAnimations:@"animateAdBannerOff" context:NULL];
        
        // Assumes the banner view is placed at the bottom of the screen.
        banner.frame = CGRectOffset(banner.frame, 0, banner.frame.size.height);
        
        [UIView commitAnimations];
        
        self.mAdBannerVisible = NO;
    }
}

-(void) gameDialogOptionSelected:(int)dialogType WithOption:(int) option
{
    //stop any sound that might be playing
    [self stopSound];
    
    NSLog(@"gameDialogOptionSelected, dialogType = %d, option = %d", dialogType, option);
    if (dialogType == DIALOG_TYPE_ADD_MOVES)
    {
        if (option == GAME_DIALOG_POSITIVE_ACTION_1) //Add Moves selected
        {
            int numCoins = getCoins();
            int numCoinsForMoves = getNumCoinsForMoves();
            if (numCoins >= numCoinsForMoves)
            {
                numCoins -= numCoinsForMoves;
                setCoins(numCoins);
                
                [self updateCoinsLabel:(numCoins)];
                
                int maxMoves = getMaxMoves(self.gridHandle);
                maxMoves += 5;
                setMaxMoves(self.gridHandle, maxMoves);
                //update moves label
                [self updateMovesLabel:(getMaxMoves(self.gridHandle) - getCurrMove(self.gridHandle))];
            }
            else
            {
                //show the add coins dialog
                [self addCoins];
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
                [self showDialogOfType:DIALOG_TYPE_GAME_MENU];
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
            [self showDialogOfType:DIALOG_TYPE_ADD_MOVES];
        }
        else if (option == GAME_DIALOG_NEGATIVE_ACTION_1) // End Game
        {
            [self showDialogOfType:DIALOG_TYPE_GAME_MENU];
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
                setCoins(numCoins);
                
                [self updateCoinsLabel:(numCoins)];
                
                //enter state where game view detects tap on a specific cell
                [self.gameView enableDisableTouchInput:YES];
                self.mStarPlacementMode = YES;
                
                [self showDialogOfType:DIALOG_TYPE_STAR_PLACEMENT_INFO];
                
                [self enableDisableAllButtons:NO];
            }
            else
            {
                [self addCoins];
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
                setCoins(numCoins);
                
                [self updateCoinsLabel:(numCoins)];
                
                //enter state where game view detects tap on a specific cell
                [self.gameView enableDisableTouchInput:YES];
                self.mHurdleSmasherMode = YES;
                
                [self showDialogOfType:DIALOG_TYPE_HURDLE_SMASHER_PLACEMENT_INFO];
                
                [self enableDisableAllButtons:NO];
            }
            else
            {
                [self addCoins];
            }
        }
    }
}

@end
