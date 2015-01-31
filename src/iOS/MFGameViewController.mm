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
 #import <StoreKit/StoreKit.h>
#import <StoreKit/SKPaymentQueue.h>

@interface MFGameViewController ()
@property (strong, nonatomic) IBOutlet UILabel *coinsLabel;
@property (strong, nonatomic) IBOutlet UILabel *movesLable; //UILabel that displays the Moves header
@property (strong, nonatomic) IBOutlet MFGameView *gameView; //UIView that renders the actual game board
@end

@implementation MFGameViewController
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
    
    //self.products = response.products;
    
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
    
    SKProduct *product0 = [response.products objectAtIndex:0];
    SKProduct *product1 = [response.products objectAtIndex:1];
    SKProduct *product2 = [response.products objectAtIndex:2];
    SKProduct *product3 = [response.products objectAtIndex:3];

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
                                              cancelButtonTitle:@"New Game"
                                              otherButtonTitles:@"Menu", @"Resume Game", nil];
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
    int colorValue = [self GetColorCodeFromUIColor:button.backgroundColor];

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
        setCoins(getCoins());
        
    updateCoinsLabel:getCoins();
        
        if (self.successAlertView == nil)
        {
            self.successAlertView = [[UIAlertView alloc] initWithTitle:@"Great job!"
                                                            message:@"Well done - you nailed it!"
                                                           delegate:self
                                                  cancelButtonTitle:@"Next Game"
                                                  otherButtonTitles:@"Menu", nil];
        }
        [self.successAlertView show];
    }
    else if (result[0] == RESULT_FAILED) //failed
    {
        //end game (failed)
        if (self.failAlertView == nil)
        {
            self.failAlertView = [[UIAlertView alloc] initWithTitle:@"Oops!"
                                                          message:@"Sorry, you ran out of moves."
                                                         delegate:self
                                                cancelButtonTitle:@"New Game"
                                                otherButtonTitles:@"Menu", nil];
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
    
    self.gridHandle = 0;
    
    [self startNewGame];
    
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
}

/**
 Start a new game.
 **/
-(void)startNewGame
{
    //clear the handle if a game was already underway
    NSLog(@"startNewGame, gridHandle = %lx", self.gridHandle);
    if (self.gridHandle != 0)
    {
        deleteGrid(self.gridHandle);
        self.gridHandle = 0;
    }
    
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
-(int)GetColorCodeFromUIColor:(UIColor *)color
{
    if ([color isEqual:[UIColor redColor]])
    {
        return GRID_COLOR_RED;
    }
    else if ([color isEqual:[UIColor greenColor]])
    {
        return GRID_COLOR_GREEN;
    }
    else if ([color isEqual:[UIColor blueColor]])
    {
        return GRID_COLOR_BLUE;
    }
    else if ([color isEqual:[UIColor yellowColor]])
    {
        return GRID_COLOR_YELLOW;
    }
    else if ([color isEqual:[UIColor orangeColor]])
    {
        return GRID_COLOR_ORANGE;
    }
    else if ([color isEqual:[UIColor cyanColor]])
    {
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
    if (alertView == self.failAlertView) // show when the user fails the game
    {
        switch (buttonIndex)
        {
            case 0: //New Game
                [self startNewGame];
                break;
            case 1: //Menu
                [self dismissViewControllerAnimated:NO completion:nil];
                break;
        }
    }
    else if (alertView == self.successAlertView) //shown on successful completion of the game
    {
        switch (buttonIndex)
        {
            case 0: //New Game
                [self startNewGame];
                break;
            case 1: //Menu
                [self dismissViewControllerAnimated:NO completion:nil];
                break;
        }
    }
    else if (alertView == self.exitAlertView) //shown when the user clicks on the X button
    {
        switch (buttonIndex)
        {
            case 0: //New Game
                [self startNewGame];
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
                break;
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

@end
