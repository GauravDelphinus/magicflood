//
//  MFGameViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import "MFGameViewController.h"
#import "MFGlobalInterface.h"
#import "MFGameView.h"
#import "MFGridInterface.h"

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
- (IBAction)addCoins:(id)sender {

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
