//
//  MFGameView.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import "MFGameViewController.h"

@protocol GameViewTapHandler
@required
// list of required methods
-(void)handleGameViewTapAtX:(int)x andY:(int)y;
@end

@interface MFGameView : UIView
{
    int **myGrid; //2-D array containing the grid colors.  Note: this is a heap-based array of integer pointers
    int gridSize; // order of game board
    int mNumStartPos; //number of start positions
    int **startPos; //array of start positions, each array has 2 integers. 0 = x, 1 = y
    int maxMoves; // max number of moves in this game
    id <GameViewTapHandler> _delegate;
}

@property (nonatomic,strong) id delegate;

-(CGColorRef)getColorFromGridForX:(int)x andY:(int)y;
-(void)initializeGameData:(int **)grid WithSize:(int)size WithNumStartPos:(int)numStartPos WithStartPos:(int **)startpos WithMaxMoves:(int)maxmoves;
-(void)updateGameData:(int **)grid;
-(void)updateStartPos:(int **)startPos withNum:(int)numStartPos;
-(void)drawStarWithLeft:(int)left WithTop:(int)top WithSize:(int)cellSize;
-(void)enableDisableTouchInput:(BOOL)enable;
@end

