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


@interface MFGameViewController ()
@property (strong, nonatomic) IBOutlet UILabel *mLevelsLabel;
@property (strong, nonatomic) IBOutlet UILabel *coinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *movesLable; //UILabel that displays the Moves header
@property (strong, nonatomic) IBOutlet MFGameView *gameView; //UIView that renders the actual game board
@end

@implementation MFGameViewController
- (IBAction)soundButtonPressed:(id)sender
{
    
}
- (IBAction)removeAds:(id)sender {
}
- (IBAction)addHurdleSmasher:(id)sender {
    //ask the user what he wants to do next
    if (self.addHurdleSmasherAlertView == nil)
    {
        self.addHurdleSmasherAlertView = [[UIAlertView alloc] initWithTitle:@"Add Hurdle Smasher"
                                                           message:@"Redeem 1500 Coins for a Hurdle Smasher"
                                                          delegate:self
                                                 cancelButtonTitle:@"Cancel"
                                                 otherButtonTitles:@"Add Hurdle Smasher", nil];
    }
    [self.addHurdleSmasherAlertView dismissWithClickedButtonIndex:0 animated:YES];
    [self.addHurdleSmasherAlertView show];
}
- (IBAction)addStar:(id)sender {
    //ask the user what he wants to do next
    if (self.addStarAlertView == nil)
    {
        self.addStarAlertView = [[UIAlertView alloc] initWithTitle:@"Add Star"
                                                            message:@"Redeem 1000 Coins for a Star"
                                                           delegate:self
                                                  cancelButtonTitle:@"Cancel"
                                                  otherButtonTitles:@"Add Star", nil];
    }
    [self.addStarAlertView dismissWithClickedButtonIndex:0 animated:YES];
    [self.addStarAlertView show];
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
        UIAlertView *notConnectedView = [[UIAlertView alloc] initWithTitle:@"Oh Shoot!"
                                                           message:@"It appears you are not connected to the iTunes Store.  Please come back later!"
                                                          delegate:self
                                                 cancelButtonTitle:@"Cancel"
                                                 otherButtonTitles:nil];
        
        [notConnectedView dismissWithClickedButtonIndex:0 animated:YES];
        [notConnectedView show];
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
        UIAlertView *notConnectedView = [[UIAlertView alloc] initWithTitle:@"Oh Shoot!"
                                                                   message:@"There was some problem getting the product information from iTunes Store.  Please come back later!"
                                                                  delegate:self
                                                         cancelButtonTitle:@"Cancel"
                                                         otherButtonTitles:nil];
        
        [notConnectedView dismissWithClickedButtonIndex:0 animated:YES];
        [notConnectedView show];

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
    
    if (self.addCoinsAlertView == nil)
    {
        self.addCoinsAlertView = [[UIAlertView alloc] initWithTitle:@"Add Coins"
                                                            message:@"Add Coins"
                                                           delegate:self
                                                  cancelButtonTitle:@"Cancel"
                                                  otherButtonTitles:iap_first_price, iap_second_price,
                                  iap_third_price, iap_fourth_price, nil];
    }
    [self.addCoinsAlertView dismissWithClickedButtonIndex:0 animated:YES];
    [self.addCoinsAlertView show];
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

- (IBAction)addMoves:(id)sender {
    //ask the user what he wants to do next
    if (self.addMovesAlertView == nil)
    {
        self.addMovesAlertView = [[UIAlertView alloc] initWithTitle:@"Add Moves"
                                              message:@"Redeem 500 Coins for 5 Moves"
                                             delegate:self
                                    cancelButtonTitle:@"Cancel"
                                    otherButtonTitles:@"Add Moves", nil];
    }
   [self.addMovesAlertView dismissWithClickedButtonIndex:0 animated:YES];
    [self.addMovesAlertView show];
}

/**
 Handler of the "X" button on the game board.
 **/
- (IBAction)handleExit:(id)sender {
    //ask the user what he wants to do next
    if (self.exitAlertView == nil)
    {
        self.exitAlertView = [[UIAlertView alloc] initWithTitle:@"Exit?"
                                                        message:@"What would you like to do?"
                                                       delegate:self
                                              cancelButtonTitle:@"Resume Game"
                                              otherButtonTitles:@"View Levels", @"Replay Level", nil];
    }
    [self.exitAlertView dismissWithClickedButtonIndex:2 animated:YES];
    [self.exitAlertView show];
}

/**
 One of the color buttons was pressed, so play the next move.
 **/
- (IBAction)colorButtonPressed:(id)sender
{
    //extract the color that was played
    UIButton *button = (UIButton *)sender;
    int colorValue = [self GetColorCodeFromUIButton:button];

    [self playSound:mButtonClickSoundID];
    
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
        
        if (self.successAlertView == nil)
        {
            self.successAlertView = [[UIAlertView alloc] initWithTitle:@"Great job!"
                                                            message:@"Well done - you nailed it!"
                                                           delegate:self
                                                  cancelButtonTitle:@"View Levels"
                                                  otherButtonTitles:@"Next Game", nil];
        }
        [self.successAlertView show];
    }
    else if (result[0] == RESULT_FAILED) //failed
    {
        [self playSound:mGameFailedSoundID];
        
        //end game (failed)
        if (self.failAlertView == nil)
        {
            self.failAlertView = [[UIAlertView alloc] initWithTitle:@"Oops!"
                                                          message:@"Sorry, you ran out of moves."
                                                         delegate:self
                                                cancelButtonTitle:@"End Game"
                                                otherButtonTitles:@"Play On", nil];
        }
        [self.failAlertView show];
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
}

-(void)viewDidDisappear:(BOOL)animated
{
    if (self.gridHandle != 0)
    {
        deleteGrid(self.gridHandle);
        self.gridHandle = 0;
    }
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
        if (self.finishedAllLevelsView == nil)
        {
            self.finishedAllLevelsView = [[UIAlertView alloc] initWithTitle:@"Superio!"
                                                                message:@"You have finished all levels!"
                                                               delegate:self
                                                      cancelButtonTitle:nil
                                                    otherButtonTitles:@"Got it!", nil
                                                      ];
        }
        [self.finishedAllLevelsView dismissWithClickedButtonIndex:0 animated:YES];
        [self.finishedAllLevelsView show];
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

/**
 Various Alert View handlers.
 **/
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    //NSLog(@"buttonIndex = %d", buttonIndex);

    //stop any sound that might be playing
    [self stopSound];
    
    if (alertView == self.failAlertView) // show when the user fails the game
    {
        switch (buttonIndex)
        {
            case 0: //End Game
                //take to the exit menu
                if (self.exitAlertView == nil)
                {
                    self.exitAlertView = [[UIAlertView alloc] initWithTitle:@"Exit?"
                                                                    message:@"What would you like to do?"
                                                                   delegate:self
                                                          cancelButtonTitle:@"Resume Game"
                                                          otherButtonTitles:@"View Levels", @"Replay Level", nil];
                }
                [self.exitAlertView dismissWithClickedButtonIndex:2 animated:YES];
                [self.exitAlertView show];
                
                break;
            case 1: //Play On
                //ask the user what he wants to do next
                if (self.addMovesAlertView == nil)
                {
                    self.addMovesAlertView = [[UIAlertView alloc] initWithTitle:@"Add Moves"
                                                                        message:@"Redeem 500 Coins for 5 Moves"
                                                                       delegate:self
                                                              cancelButtonTitle:@"Cancel"
                                                              otherButtonTitles:@"Add Moves", nil];
                }
                [self.addMovesAlertView dismissWithClickedButtonIndex:0 animated:YES];
                [self.addMovesAlertView show];
                
                break;
        }
    }
    else if (alertView == self.successAlertView) //shown on successful completion of the game
    {
        switch (buttonIndex)
        {
            case 0: //View Levels
                [self dismissViewControllerAnimated:NO completion:nil];
                break;
            case 1: //Next Game
                [self startNewGame:(self.gameLevel + 1)];
                break;
        }
    }
    else if (alertView == self.exitAlertView) //shown when the user clicks on the X button
    {
        NSLog(@"buttonIndex = %d", buttonIndex);
        switch (buttonIndex)
        {
            case 2: //Replay
                [self startNewGame:self.gameLevel];
                break;
            case 1: //Menu
                [self dismissViewControllerAnimated:NO completion:nil];
                break;
        }
    }
    else if (alertView == self.addMovesAlertView) //shown when the user clicks on the Add Moves button
    {
        switch (buttonIndex)
        {
            case 1: //Add Moves
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
                break;
            }
            case 0: //cancel
            {
                /**
                 if the user landed here after having "failed" the game,
                 show him the game menu dialog again.
                 **/
                if (getCurrMove(self.gridHandle) == getMaxMoves(self.gridHandle))
                {
                    if (self.exitAlertView == nil)
                    {
                        self.exitAlertView = [[UIAlertView alloc] initWithTitle:@"Exit?"
                                                                        message:@"What would you like to do?"
                                                                       delegate:self
                                                              cancelButtonTitle:@"Resume Game"
                                                              otherButtonTitles:@"View Levels", @"Replay Level", nil];
                    }
                    [self.exitAlertView dismissWithClickedButtonIndex:2 animated:YES];
                    [self.exitAlertView show];
                }
            }
        }
    }
    else if (alertView == self.addStarAlertView) //shown when the user clicks on the Add Star button
    {
        switch (buttonIndex)
        {
            case 1: //Add Star
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
                }
                else
                {
                    [self addCoins];
                }
                break;
            }
          
        }
    }
    else if (alertView == self.addHurdleSmasherAlertView) //shown when the user clicks on the Add Hurdle Smasher button
    {
        switch (buttonIndex)
        {
            case 1: //Add Hurdle Smasher
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
                }
                else
                {
                    [self addCoins];
                }
                break;
            }
        }
    }
    else if (alertView == self.addCoinsAlertView) //shown when the user clicks on the Add Coins button
    {
        switch (buttonIndex)
        {
            case 1: //Add 500 Coins
            {
                SKProduct *product = [self.products objectAtIndex:0];
                SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:product];
                payment.quantity = 1;
                
                [[SKPaymentQueue defaultQueue] addPayment:payment];

                break;
            }
            case 0: //cancel
            {
                /**
                 if the user landed here after having "failed" the game,
                 show him the game menu dialog again.
                 **/
                if (getCurrMove(self.gridHandle) == getMaxMoves(self.gridHandle))
                {
                    if (self.exitAlertView == nil)
                    {
                        self.exitAlertView = [[UIAlertView alloc] initWithTitle:@"Exit?"
                                                                        message:@"What would you like to do?"
                                                                       delegate:self
                                                              cancelButtonTitle:@"Resume Game"
                                                              otherButtonTitles:@"View Levels", @"Replay Level", nil];
                    }
                    [self.exitAlertView dismissWithClickedButtonIndex:2 animated:YES];
                    [self.exitAlertView show];
                }
            }
        }
    }

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
        }
        else
        {
            UIAlertView *errorView = [[UIAlertView alloc] initWithTitle:@"Try Again"
                                                                        message:@"Couldn't detect a start position, please try again."
                                                                       delegate:self
                                                              cancelButtonTitle:@"Cancel" otherButtonTitles: nil];
            [errorView show];
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
        }
        else
        {
            UIAlertView *errorView = [[UIAlertView alloc] initWithTitle:@"Try Again"
                                                                message:@"Couldn't detect a hurdle, please try again."
                                                               delegate:self
                                                      cancelButtonTitle:@"Cancel" otherButtonTitles: nil];
            [errorView show];
        }
    }
}

-(void) enableDisableAllButtons:(BOOL)enable
{
    
}

-(void) playSound:(SystemSoundID)soundID
{
    //[self stopSound];
    AudioServicesPlaySystemSound(soundID);
    mCurrentlyPlayingSound = soundID;
}

-(void) stopSound
{
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

@end
