//
//  MFGameView.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import "MFGameView.h"
#import "MFGridInterface.h"
#define UIColorFromRGB(rgbValue) \
[UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0x00FF00) >>  8))/255.0 \
blue:((float)((rgbValue & 0x0000FF) >>  0))/255.0 \
alpha:1.0]

#define UIColorFromARGB(argbValue) \
[UIColor colorWithRed:((float)((argbValue & 0x00FF0000) >> 16))/255.0 \
green:((float)((argbValue & 0x0000FF00) >>  8))/255.0 \
blue:((float)((argbValue & 0x000000FF) >>  0))/255.0 \
alpha:((float)((argbValue & 0xFF000000) >>  0))/255.0]

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
-(void)initializeGameData:(int **)grid WithSize:(int)size WithNumStartPos:(int)numStartPos WithStartPos:(int **)startpos WithMaxMoves:(int)maxmoves
{
    //free old grid, if present
    if (myGrid != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            free(myGrid[i]);
        }
        
        free(myGrid);
        myGrid = NULL;
    }
    
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
    
    mNumStartPos = numStartPos;
    startPos = (int **) malloc (numStartPos * sizeof(int *));
    for (int i = 0; i < numStartPos; i++)
    {
        startPos[i] = (int *) malloc (2 * sizeof(int));
        startPos[i][0] = startpos[i][0];
        startPos[i][1] = startpos[i][1];
    }
    
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

-(void)updateStartPos:(int **)startpos withNum:(int)numStartPos
{
    //free existing array
    for (int i = 0; i < mNumStartPos; i++)
    {
        free(startPos[i]);
    }
    free(startPos);
    
    //allocate new and update the array
    mNumStartPos = numStartPos;
    startPos = (int **) malloc (numStartPos * sizeof(int *));
    for (int i = 0; i < numStartPos; i++)
    {
        startPos[i] = (int *) malloc (2 * sizeof(int));
        startPos[i][0] = startpos[i][0];
        startPos[i][1] = startpos[i][1];
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
            return UIColorFromRGB(0xDB4D4D).CGColor;
            break;
        case GRID_COLOR_GREEN:
            return UIColorFromRGB(0x7ACC7A).CGColor;
            break;
        case GRID_COLOR_BLUE:
            return UIColorFromRGB(0x33CCFF).CGColor;
            break;
        case GRID_COLOR_YELLOW:
            return UIColorFromRGB(0xFFFF66).CGColor;
            break;
        case GRID_COLOR_ORANGE:
            return UIColorFromRGB(0xFFA347).CGColor;
            break;
        case GRID_COLOR_CYAN:
            return UIColorFromRGB(0xDB4DFF).CGColor;
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
    CGFloat screenHeight = screenSize.height;
    
    int gap = 0;
    int gridlength = MIN(screenSize.height, screenWidth) - gap;
    
    //NSLog(@"screenWidth = %f, screenHeight = %f, scale= %f", screenWidth, screenHeight, scale);
    
    int horizontalGap = screenWidth - gridlength;
    
    int vOffset = (screenHeight - gridlength)/2;
    
    int cellSize = (screenWidth - horizontalGap)/gridSize;
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetLineWidth(context, 1.0);

    int hOffset = horizontalGap / 2;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            CGRect rectangle = CGRectMake(hOffset + j*cellSize, vOffset + i*cellSize, cellSize, cellSize);
            CGContextAddRect(context, rectangle);
            CGContextStrokePath(context);
            CGContextSetFillColorWithColor(context, [self getColorFromGridForX:i andY:j]);
            CGContextFillRect(context, rectangle);
        }
    }
    
    //show the start position
    for (int i = 0; i < mNumStartPos; i++)
    {
        [self drawStarWithLeft:hOffset + startPos[i][1] * cellSize WithTop:vOffset + startPos[i][0] * cellSize WithSize:cellSize];
    }
}

-(void)drawStarWithLeft:(int)left WithTop:(int)top WithSize:(int)cellSize
{
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGRect rectangle = CGRectMake(left, top, cellSize, cellSize);
    CGContextAddRect(context, rectangle);
    CGContextSetLineWidth(context, 3.0);
    CGContextStrokePath(context);
}

-(void)enableDisableTouchInput:(BOOL)enable
{
    if (enable == YES)
    {
        [self setMultipleTouchEnabled:YES];
    }
    else
    {
        [self setMultipleTouchEnabled:NO];
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint location = [touch locationInView:touch.view];
    NSLog(@"touchesEnded called with x = %d, y = %d", (int)location.x, (int)location.y);

    CGRect screenBound = [self bounds];
    CGSize screenSize = screenBound.size;
    CGFloat screenWidth = screenSize.width ;
    
    //NSLog(@"screenWidth = %f, screenHeight = %f, scale= %f", screenWidth, screenHeight, scale);
    
    int horizontalGap = 20;
    int vOffset = 80;
    int cellSize = (screenWidth - horizontalGap)/gridSize;
    
    
    int hOffset = horizontalGap / 2;
    
    int xOffset = (int)location.x - hOffset;
    int yOffset = (int)location.y - vOffset;
    
    int gridx = xOffset / cellSize;
    int gridy = yOffset / cellSize;
    
    [self.delegate handleGameViewTapAtX:gridy andY:gridx];
}

@end
