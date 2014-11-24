//
//  MFGameView.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import "MFGameView.h"
#import "MFGridInterface.h"

@implementation MFGameView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

/**
 Main init function called when the MFGameView is loaded.
 **/
- (id)initWithCoder:(NSCoder *)decoder
{
    self = [super initWithCoder:decoder];
    
    myGrid = NULL;
    
    return self;
}

/**
 Initialize the Game View with the data required to draw the game board.
 grid: 2-D array of color values, must be copied into local data structure
 size: Order of the game board
 startpos: integer array with two elements, the x and y coordinates of the start position of the game
 maxmoves: the maximum number of moves allowed for this game
 **/
-(void)initializeGameData:(int **)grid WithSize:(int)size WithStartPos:(int *)startpos WithMaxMoves:(int)maxmoves
{
    //allocate a local data structure, if not already present
    if (myGrid == NULL)
    {
        myGrid = (int **) malloc (size * sizeof(int *));
        for (int i = 0; i < size; i++)
        {
            myGrid[i] = (int *) malloc (size * sizeof(int));
        }
        NSLog(@"initializeGameData, allocated new myGrid = %p", myGrid);
    }
    
    //copy grid to local data structure
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            myGrid[i][j] = grid[i][j];
        }
    }
    
    gridSize = size;
    maxMoves = maxmoves;
    
    startPos[0] = startpos[0];
    startPos[1] = startpos[1];
    
    [self setNeedsDisplay];
}

/**
 Update the game data with updated values after a move was played.
 **/
-(void)updateGameData:(int **)grid
{
    //copy grid to local data structure
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            myGrid[i][j] = grid[i][j];
        }
    }
    
    [self setNeedsDisplay];
}


/**
 Retrun the CGColorRef value of the particular cell in the grid.
 **/
-(CGColorRef)getColorFromGridForX:(int)x andY:(int)y
{
    int gridColor = myGrid[x][y];
    switch (gridColor)
    {
        case GRID_COLOR_RED:
            return [UIColor redColor].CGColor;
            break;
        case GRID_COLOR_GREEN:
            return [UIColor greenColor].CGColor;
            break;
        case GRID_COLOR_BLUE:
            return [UIColor blueColor].CGColor;
            break;
        case GRID_COLOR_YELLOW:
            return [UIColor yellowColor].CGColor;
            break;
        case GRID_COLOR_ORANGE:
            return [UIColor orangeColor].CGColor;
            break;
        case GRID_COLOR_CYAN:
            return [UIColor cyanColor].CGColor;
            break;
        case GRID_OBSTACLE: //obstacle
            return [UIColor grayColor].CGColor;
            break;
    }
    
    return [UIColor blackColor].CGColor;
}

/**
 Main drawing routine that draws the game board.
 **/
- (void)drawRect:(CGRect)rect
{
    CGRect screenBound = [self bounds];
    CGSize screenSize = screenBound.size;
    CGFloat screenWidth = screenSize.width ;
    
    //NSLog(@"screenWidth = %f, screenHeight = %f, scale= %f", screenWidth, screenHeight, scale);
    
    int horizontalGap = 20;
    int vOffset = 80;
    int cellSize = (screenWidth - horizontalGap)/gridSize;
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetLineWidth(context, 1.0);

    int hOffset = horizontalGap / 2;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            CGRect rectangle = CGRectMake(hOffset + i*cellSize, vOffset + j*cellSize, cellSize, cellSize);
            CGContextAddRect(context, rectangle);
            CGContextStrokePath(context);
            CGContextSetFillColorWithColor(context, [self getColorFromGridForX:i andY:j]);
            CGContextFillRect(context, rectangle);
        }
    }
    
    //show the start position
    CGRect rectangle = CGRectMake(hOffset + startPos[0] * cellSize, vOffset + startPos[1] * cellSize, cellSize, cellSize);
    CGContextAddRect(context, rectangle);
    CGContextSetLineWidth(context, 3.0);
    CGContextStrokePath(context);
}

@end
