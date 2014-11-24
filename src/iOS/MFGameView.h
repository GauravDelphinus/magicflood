//
//  MFGameView.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MFGameViewController.h"

@interface MFGameView : UIView
{
    int **myGrid; //2-D array containing the grid colors.  Note: this is a heap-based array of integer pointers
    int gridSize; // order of game board
    int startPos[2]; //0 = x, 1 = y
    int maxMoves; // max number of moves in this game
}

-(CGColorRef)getColorFromGridForX:(int)x andY:(int)y;
-(void)initializeGameData:(int **)grid WithSize:(int)size WithStartPos:(int *)startpos WithMaxMoves:(int)maxmoves;
-(void)updateGameData:(int **)grid;
@end