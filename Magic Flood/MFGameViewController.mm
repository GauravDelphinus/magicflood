//
//  MFGameViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import "MFGameViewController.h"
#import "MFGameView.h"
#import "MFGridInterface.h"

@interface MFGameViewController ()
@property (strong, nonatomic) IBOutlet UILabel *movesLable; //UILabel that displays the Moves header
@property (strong, nonatomic) IBOutlet MFGameView *gameView; //UIView that renders the actual game board
@end

@implementation MFGameViewController

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
    int result = playMove(self.gridHandle, colorValue);
    
    //update moves label
    NSString *labeltext = [NSString stringWithFormat:@"%d / %d",
                           getCurrMove(self.gridHandle), getMaxMoves(self.gridHandle)];
    [self.movesLable setText:labeltext];

    /**
     Pass the game data to the game view so it can draw/refresh
     the board with the updated colors.
     **/
    int **gridData = getGridData(self.gridHandle);
    [[self gameView] updateGameData:gridData];
    freeGridData(self.gridHandle, gridData);

    if (result == RESULT_SUCCESS) //success
    {
        if (self.successAlertView == nil)
        {
            self.successAlertView = [[UIAlertView alloc] initWithTitle:@"Great job!"
                                                            message:@"Well done - you completed the game!"
                                                           delegate:self
                                                  cancelButtonTitle:@"Next Game"
                                                  otherButtonTitles:@"Menu", nil];
        }
        [self.successAlertView show];
    }
    else if (result == RESULT_FAILED) //failed
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

}

/**
 Start a new game.
 **/
-(void)startNewGame
{
    //clear the gandle if a game was already underway
    if (self.gridHandle != 0)
    {
        deleteGrid(self.gridHandle);
        self.gridHandle = 0;
    }
    
    //initialize a new game grid
    self.gridHandle = createNewGrid(self.gameLevel);
    
    //extract data for the game, and then pass on to the UIView for rendering
    int *startPos = getStartPos(self.gridHandle);
    int **gridData = getGridData(self.gridHandle);
    
    [[self gameView] initializeGameData:gridData WithSize:getGridSize(self.gridHandle) WithStartPos:startPos WithMaxMoves:getMaxMoves(self.gridHandle)];
    freeGridData(self.gridHandle, gridData);
    freeStartPos(self.gridHandle, startPos);
    
    //update the UI to reflect the game moves
    NSString *labeltext = [NSString stringWithFormat:@"%d / %d", getCurrMove(self.gridHandle), getMaxMoves(self.gridHandle)];
    [self.movesLable setText:labeltext];
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
}

/**
 Called when the view controller is about to unload.  Clear resources here.
 **/
-(void)dealloc
{
    if (self.gridHandle != 0)
    {
        deleteGrid(self.gridHandle);
        self.gridHandle = 0;
    }
}

@end
