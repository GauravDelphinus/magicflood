//
//  MFGameView.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import "MFGameView.h"
#import "MFGridInterface.h"
#import "MFGameConstants.h"
#import <math.h>
#import "MFUtils.h"

#define SHADOW_THICKNESS 5

/**
 Direction of Linear Gradient for Shadow
 **/
#define LINEAR_GRADIENT_DIRECTION_NORTH  1
#define LINEAR_GRADIENT_DIRECTION_EAST  2
#define LINEAR_GRADIENT_DIRECTION_SOUTH 3
#define LINEAR_GRADIENT_DIRECTION_WEST  4

/**
 Direction of Radial Gradient (whether outward or inward) for Shadow
 **/
#define RADIAL_GRADIENT_DIRECTION_NORTH_EAST 1
#define RADIAL_GRADIENT_DIRECTION_SOUTH_EAST 2
#define RADIAL_GRADIENT_DIRECTION_SOUTH_WEST 3
#define RADIAL_GRADIENT_DIRECTION_NORTH_WEST 4

@interface MFGameView ()
{
    int **myGrid; //2-D array containing the grid colors.  Note: this is a heap-based array of integer pointers
    int gridSize; // order of game board
    int mNumStartPos; //number of start positions
    int **startPos; //array of start positions, each array has 2 integers. 0 = x, 1 = y
    int maxMoves; // max number of moves in this game
}

@property int mFlashCellX, mFlashCellY; //flash this cell when non-zero
@end

@implementation MFGameView

/*********************  Init / Setup Routines **************************/

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
        for (int i = 0; i < gridSize; i++)
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

/*********************  Update Game Routines **************************/

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
 Update the stars!
 **/
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

/*********************  Util Routines **************************/

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

/*********************  Drawing Routines **************************/

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
    int gridlength = MIN(screenSize.height, screenWidth) - gap - SHADOW_THICKNESS;
    int cellSize = gridlength/gridSize;
    
    //adjusted gridlength (reduced due to rounding off of each cell)
    gridlength = gridSize * cellSize;
    
    //NSLog(@"screenWidth = %f, screenHeight = %f, scale= %f", screenWidth, screenHeight, scale);
    
    int horizontalGap = screenWidth - gridlength - SHADOW_THICKNESS;
    
    int vOffset = (screenHeight - gridlength - SHADOW_THICKNESS)/2;
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetLineWidth(context, 1.0);

    int hOffset = horizontalGap / 2;

    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (myGrid[i][j] == GRID_OBSTACLE) //draw hurdle gradient
            {
                [self drawHurdleWithLeft:hOffset + j * cellSize WithTop:vOffset + i * cellSize WithSize:cellSize WithX:i WithY:j];
            }
            else if (myGrid[i][j] == GRID_SPACE)
            {
                //do nothing
            }
            else //draw color cell
            {
                [self drawColorWithLeft:hOffset + j * cellSize WithTop:vOffset + i * cellSize WithSize:cellSize WithX:i WithY:j];
            }
        }
    }
    
    //show the start position
    for (int i = 0; i < mNumStartPos; i++)
    {
        [self drawStarWithLeft:hOffset + startPos[i][1] * cellSize WithTop:vOffset + startPos[i][0] * cellSize WithSize:cellSize WithX:startPos[i][0] WithY:startPos[i][1]];
    }
    
    /**
     Draw the shadow
     **/
    
    [self drawGridShadowWithLeft:hOffset withTop:vOffset WithGridLength:gridlength WithCellSize:cellSize];
}

/**
 Draw the shadow around the grid.  Generic implementation.
 **/
-(void)drawGridShadowWithLeft:(int)left withTop:(int)top WithGridLength:(int)gridlength WithCellSize:(int)cellSize
{
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if ([self isEmptyAtX:j AndY:i]) //only draw shadow around a real colored cell
            {
                continue;
            }
            
            int cellLeft = left + j * cellSize;
            int cellTop = top + i * cellSize;
            
            if ([self isEmptyAtX:j AndY:i+1]) //below cell is empty
            {
                if (![self isEmptyAtX:j-1 AndY:i]) //left cell is not empty, so just draw the bottom shadow
                {
                    //bottom shadow with full cell width
                    CGRect shadowRect = CGRectMake(cellLeft, cellTop + cellSize, cellSize, SHADOW_THICKNESS);
                    [self drawLinearGradient:shadowRect withDirection:LINEAR_GRADIENT_DIRECTION_SOUTH];
                }
                else //left cell is empty, so the shadow starts here.  so draw the bottom shadow but
                    //with a rounded offset
                {
                    //bottom left corner shadow
                    CGRect cornerRect = CGRectMake(cellLeft, cellTop + cellSize, SHADOW_THICKNESS, SHADOW_THICKNESS);
                    [self drawRadialGradient:cornerRect withDirection:RADIAL_GRADIENT_DIRECTION_SOUTH_WEST isOutward:YES];
                    
                    //bottom shadow offsetted by the shadow thickness
                    CGRect shadowRect = CGRectMake(cellLeft + SHADOW_THICKNESS, cellTop + cellSize, cellSize - SHADOW_THICKNESS, SHADOW_THICKNESS);
                    [self drawLinearGradient:shadowRect withDirection:LINEAR_GRADIENT_DIRECTION_SOUTH];
                }
            }
            
            if ([self isEmptyAtX:j+1 AndY:i]) //right cell is empty
            {
                if (![self isEmptyAtX:j AndY:i-1]) //upper cell is not empty, so just draw the right shadow
                {
                    //right shadow with full height
                    CGRect shadowRect = CGRectMake(cellLeft + cellSize, cellTop, SHADOW_THICKNESS, cellSize);
                    [self drawLinearGradient:shadowRect withDirection:LINEAR_GRADIENT_DIRECTION_EAST];
                }
                else //upper cell is empty, so the shadow starts here.  So draw the offsetted shadow
                    //with rounded corner
                {
                    //top right corner shadow
                    CGRect cornerRect = CGRectMake(cellLeft + cellSize, cellTop, SHADOW_THICKNESS, SHADOW_THICKNESS);
                    [self drawRadialGradient:cornerRect withDirection:RADIAL_GRADIENT_DIRECTION_NORTH_EAST isOutward:YES];
                    
                    //right shadow offsetted by shadow thickness's height
                    CGRect shadowRect = CGRectMake(cellLeft + cellSize, cellTop + SHADOW_THICKNESS, SHADOW_THICKNESS, cellSize - SHADOW_THICKNESS);
                    [self drawLinearGradient:shadowRect withDirection:LINEAR_GRADIENT_DIRECTION_EAST];
                }
            }
            
            if ([self isEmptyAtX:j AndY:i+1] && [self isEmptyAtX:j+1 AndY:i]) //bottom right corner
            {
                /**
                 the right and bottom shadows would have been drawn already (above), so just draw
                 the bottom right radial shadow.
                 **/
                CGRect cornerRect = CGRectMake(cellLeft + cellSize, cellTop + cellSize, SHADOW_THICKNESS, SHADOW_THICKNESS);
                [self drawRadialGradient:cornerRect withDirection:RADIAL_GRADIENT_DIRECTION_SOUTH_EAST isOutward:YES];
            }
        }
    }
    
}

/**
 Check if the cell at this position is "empty".
 **/
-(BOOL)isEmptyAtX:(int) x AndY:(int)y
{
    if (x < 0 || y < 0 || x >= gridSize || y >= gridSize)
        return YES;
    
    if (myGrid[y][x] == GRID_SPACE)
    {
        return YES;
    }
    
    return NO;
}

/**
 Draw a linear gradient in the given rect with the given direction.
 See direction values at the top of this file.
 **/
-(void)drawLinearGradient:(CGRect) rect withDirection:(int)direction
{
    CGContextRef context = UIGraphicsGetCurrentContext();

    CGContextSaveGState(context);

    CGContextBeginPath(context);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGFloat locations[] = { 0.0, 1.0 };
    
    NSArray *colors = @[(__bridge id) [UIColor blackColor].CGColor, (__bridge id) [UIColor clearColor].CGColor];
    
    CGGradientRef gradient = CGGradientCreateWithColors(colorSpace, (__bridge CFArrayRef) colors, locations);
    
    CGPoint startPoint, endPoint;
    
    if (direction == LINEAR_GRADIENT_DIRECTION_EAST)
    {
        startPoint = CGPointMake(rect.origin.x, rect.origin.y);
        endPoint = CGPointMake(rect.origin.x + rect.size.width, rect.origin.y);
    }
    else if (direction == LINEAR_GRADIENT_DIRECTION_NORTH)
    {
        startPoint = CGPointMake(rect.origin.x, rect.origin.y + rect.size.height);
        endPoint = CGPointMake(rect.origin.x, rect.origin.y);
    }
    else if (direction == LINEAR_GRADIENT_DIRECTION_WEST)
    {
        startPoint = CGPointMake(rect.origin.x + rect.size.width, rect.origin.y);
        endPoint = CGPointMake(rect.origin.x, rect.origin.y);
    }
    else
    {
        //south
        startPoint = CGPointMake(rect.origin.x, rect.origin.y);
        endPoint = CGPointMake(rect.origin.x, rect.origin.y + rect.size.height);
    }
    
    CGContextAddRect(context, rect);
    CGContextClip(context);
    
    CGContextDrawLinearGradient(context, gradient, startPoint, endPoint, 0);
    
    CGContextRestoreGState(context);
}

/**
 Draw an radial gradient with the given direction
 in the given rect.  Refer direction values at the top of this file.
 Outward means from dark to clear.  Inward means from clear to dark.
 **/
-(void)drawRadialGradient:(CGRect) rect withDirection:(int)direction isOutward:(BOOL)isOutward
{
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGFloat locations[] = { 0.0, 1.0 };
    
    NSArray *colors;
    
    if (!isOutward)
    {
        colors = @[(__bridge id) [UIColor clearColor].CGColor, (__bridge id) [UIColor blackColor].CGColor];
    }
    else
    {
        colors = @[(__bridge id) [UIColor blackColor].CGColor, (__bridge id) [UIColor clearColor].CGColor];
    }
    
    CGGradientRef gradient = CGGradientCreateWithColors(colorSpace, (__bridge CFArrayRef) colors, locations);
    
    CGMutablePathRef path = CGPathCreateMutable();
    
    CGPoint centerPoint;
    
    if (direction == RADIAL_GRADIENT_DIRECTION_SOUTH_WEST)
    {
        CGPathMoveToPoint(path, NULL, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
        CGPathAddArc(path, NULL, rect.origin.x + rect.size.width, rect.origin.y, SHADOW_THICKNESS, M_PI / 2, M_PI, 0);
        CGPathAddLineToPoint(path, NULL, rect.origin.x, rect.origin.y);
        CGPathAddLineToPoint(path, NULL, rect.origin.x + rect.size.width, rect.origin.y);
        centerPoint = CGPointMake(rect.origin.x + rect.size.width, rect.origin.y);
    }
    else if (direction == RADIAL_GRADIENT_DIRECTION_SOUTH_EAST)
    {
        CGPathMoveToPoint(path, NULL, rect.origin.x + rect.size.width, rect.origin.y);
        CGPathAddArc(path, NULL, rect.origin.x, rect.origin.y, SHADOW_THICKNESS, 0, M_PI / 2, 0);
        CGPathAddLineToPoint(path, NULL, rect.origin.x, rect.origin.y);
        CGPathAddLineToPoint(path, NULL, rect.origin.x + rect.size.width, rect.origin.y);
        centerPoint = CGPointMake(rect.origin.x, rect.origin.y);
    }
    else if (direction == RADIAL_GRADIENT_DIRECTION_NORTH_EAST)
    {
        CGPathMoveToPoint(path, NULL, rect.origin.x, rect.origin.y);
        CGPathAddArc(path, NULL, rect.origin.x, rect.origin.y + rect.size.height, SHADOW_THICKNESS, 3 * M_PI / 2, 0, 0);
        CGPathAddLineToPoint(path, NULL, rect.origin.x, rect.origin.y + rect.size.height);
        CGPathAddLineToPoint(path, NULL, rect.origin.x, rect.origin.y);
        centerPoint = CGPointMake(rect.origin.x, rect.origin.y + rect.size.height);
    }
    else
    {
        //north west
        CGPathMoveToPoint(path, NULL, rect.origin.x, rect.origin.y + rect.size.height);
        CGPathAddArc(path, NULL, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height, SHADOW_THICKNESS, M_PI, 3 * M_PI / 2, 0);
        CGPathAddLineToPoint(path, NULL, rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
        CGPathAddLineToPoint(path, NULL, rect.origin.x, rect.origin.y + rect.size.height);
        centerPoint = CGPointMake(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
    }
    
    CGContextAddPath(context, path);
    CGPathCloseSubpath(path);
    CGContextClip(context);
    
    CGContextDrawRadialGradient (context, gradient, centerPoint,
                                 0, centerPoint, SHADOW_THICKNESS,
                                 0);
    CGContextRestoreGState(context);
}

-(void)drawColorWithLeft:(int)left WithTop:(int)top WithSize:(int)cellSize WithX:(int)x WithY:(int)y
{
    int shadowThickness = 1;
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    
    CGRect rectangle = CGRectMake(left, top, cellSize - shadowThickness, cellSize - shadowThickness);
    CGContextAddRect(context, rectangle);

    CGContextSetFillColorWithColor(context, [self getColorFromGridForX:x andY:y]);
    CGContextFillRect(context, rectangle);
    
    /** Draw the shadow on top and bottom edge **/

    CGRect borderRect = CGRectMake(left, top, cellSize, cellSize);
    CGContextAddRect(context, borderRect);
    
    CGContextSetStrokeColorWithColor(context, [UIColor whiteColor].CGColor);
    CGContextSetLineWidth(context, shadowThickness);
    CGContextStrokeRect(context, borderRect);
    
    CGContextMoveToPoint(context, left + cellSize - shadowThickness, top);
    CGContextAddLineToPoint(context, left + cellSize - shadowThickness, top + cellSize - shadowThickness);
    CGContextAddLineToPoint(context, left, top + cellSize - shadowThickness);
    CGContextSetStrokeColorWithColor(context, [UIColor darkGrayColor].CGColor);
    CGContextSetLineWidth(context, shadowThickness);
    CGContextStrokePath(context);
    
    CGContextRestoreGState(context);
}

-(void)drawHurdleWithLeft:(int)left WithTop:(int)top WithSize:(int)cellSize WithX:(int)x WithY:(int)y
{
    int shadowThickness = 1;
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    
    /**
     Note: the reason the clip rect has been expanded in all four directions by 1 pixel is because of the
     way clip rect works.  What it does is it removes the boundary rect along with all surrounding area, which
     renders the resulting clip 1 pixel smaller in all directions.  So, we're trying to compensate for that loss.
     **/
    CGRect rectangle = CGRectMake(left - 1, top - 1, cellSize - shadowThickness + 2, cellSize - shadowThickness + 2);
    CGContextAddRect(context, rectangle);
    
    CGContextClip(context);
    CGPoint startPoint = CGPointMake(left + cellSize / 2, top + cellSize / 2);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGFloat locations[] = { 0.0, 1.0 };
    
    NSArray *colors = @[(__bridge id) UIColorFromRGB(HURDLE_GRADIENT_START_COLOR).CGColor, (__bridge id) UIColorFromRGB(HURDLE_GRADIENT_END_COLOR).CGColor];
    
    CGGradientRef gradient = CGGradientCreateWithColors(colorSpace, (__bridge CFArrayRef) colors, locations);
    
    CGContextDrawRadialGradient (context, gradient, startPoint,
                                 0, startPoint, cellSize,
                                 kCGGradientDrawsAfterEndLocation);
    
    /** Draw the shadow on top and bottom edge **/
    CGRect borderRect = CGRectMake(left, top, cellSize, cellSize);
    CGContextAddRect(context, borderRect);
    
    CGContextSetStrokeColorWithColor(context, [UIColor whiteColor].CGColor);
    CGContextSetLineWidth(context, shadowThickness);
    CGContextStrokeRect(context, borderRect);
    
    CGContextMoveToPoint(context, left + cellSize - shadowThickness, top);
    CGContextAddLineToPoint(context, left + cellSize - shadowThickness, top + cellSize - shadowThickness);
    CGContextAddLineToPoint(context, left, top + cellSize - shadowThickness);
    CGContextSetStrokeColorWithColor(context, [UIColor darkGrayColor].CGColor);
    CGContextSetLineWidth(context, shadowThickness);
    CGContextStrokePath(context);
    
    CGContextRestoreGState(context);
}

/**
 Draw a star given the various attributes.
 **/
-(void)drawStarWithLeft:(int)left WithTop:(int)top WithSize:(int)cellSize WithX:(int)x WithY:(int)y
{
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSaveGState(context);
    
    int gap = 2;
    left = left + gap;
    top = top + gap;
    int d = cellSize - gap * 2; //diameter
    int r = d/2; //radius of star spikes
    int s = r/2; //radius of star troughs
    double theta = 72 * M_PI / 180; //degrees
    double phi = 36 * M_PI / 180; //degrees
    
    /**
     Get ready to draw the star itself
     **/
    double costheta = cos(theta);
    double cosphi = cos(phi);
    double sintheta = sin(theta);
    double sinphi = sin(phi);
    
    
    // Move to the center of the rectangle:
    CGContextTranslateCTM(context, left + r, top + r);
    // Rotate:
    CGContextRotateCTM(context, self.mCurrentAngleOfStartPosition * M_PI / 90.0);
    CGContextTranslateCTM(context, -(left + r), -(top + r));
    
    double x1 = left + d;
    double y1 = top + r;
    double x3 = left + r + (r * costheta);
    double y3 = top + r - (r * sintheta);
    double x5 = left + r - (r * cosphi);
    double y5 = top + r - (r * sinphi);
    double x7 = left + r - (r * cosphi);
    double y7 = top + r + (r * sinphi);
    double x9 = left + r + (r * costheta);
    double y9 = top + r + (r * sintheta);
    double x2 = left + r + (s * cosphi);
    double y2 = top + r - (s * sinphi);
    double x4 = left + r - (s * costheta);
    double y4 = top + r - (s * sintheta);
    double x6 = left + r - s;
    double y6 = top + r;
    double x8 = left + r - (s * costheta);
    double y8 = top + r + (s * sintheta);
    double x10 = left + r + (s * cosphi);
    double y10 = top + r + (s * sinphi);
    
    CGMutablePathRef pathRef = CGPathCreateMutable();
    
    CGPathMoveToPoint(pathRef, NULL, x1, y1);
    CGPathAddLineToPoint(pathRef, NULL, x2, y2);
    CGPathAddLineToPoint(pathRef, NULL, x3, y3);
    CGPathAddLineToPoint(pathRef, NULL, x4, y4);
    CGPathAddLineToPoint(pathRef, NULL, x5, y5);
    CGPathAddLineToPoint(pathRef, NULL, x6, y6);
    CGPathAddLineToPoint(pathRef, NULL, x7, y7);
    CGPathAddLineToPoint(pathRef, NULL, x8, y8);
    CGPathAddLineToPoint(pathRef, NULL, x9, y9);
    CGPathAddLineToPoint(pathRef, NULL, x10, y10);
    CGPathAddLineToPoint(pathRef, NULL, x1, y1);
    CGPathCloseSubpath(pathRef);
    
    CGContextBeginPath(context);
    CGContextSetFillColorWithColor(context,
                                   [UIColor whiteColor].CGColor);
    CGContextAddPath(context, pathRef);
    CGContextFillPath(context);
    

    /**
     Draw the black star border (stroke)
     **/
    CGContextSetLineWidth(context, 1);
    CGContextSetStrokeColorWithColor(context, [UIColor
                                                   grayColor].CGColor);
    CGContextAddPath(context, pathRef);
    CGContextStrokePath(context);
    
    CGPathRelease(pathRef);
    
    CGContextRestoreGState(context);
}

/*********************  User Action Routines **************************/

/**
 Enable or disable touch input, a request that comes from
 the controller.
 **/
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

/**
 Flash/Indicate thsi particular cell.  Used currently during the bridge
 placement mode when the first point has been selected and the second is
 in the process of being selected.
 **/
-(void)flashCellWithX:(int)x withY:(int)y Enable:(BOOL)enable
{
    if (enable)
    {
        self.mFlashCellX = x;
        self.mFlashCellY = y;
    }
    else
    {
        self.mFlashCellX = 0;
        self.mFlashCellY = 0;
    }
}

/**
 Touch callback when you need to allow user to tap and select
 a particular cell in the grid.
 **/
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint location = [touch locationInView:touch.view];
    NSLog(@"touchesEnded called with x = %d, y = %d", (int)location.x, (int)location.y);

    CGRect screenBound = [self bounds];
    CGSize screenSize = screenBound.size;
    CGFloat screenWidth = screenSize.width;
    CGFloat screenHeight = screenSize.height;
    
    int gap = 0;
    int gridlength = MIN(screenSize.height, screenWidth) - gap - SHADOW_THICKNESS;
    int cellSize = gridlength/gridSize;
    
    //adjusted gridlength (reduced due to rounding off of each cell)
    gridlength = gridSize * cellSize;
    
    //NSLog(@"screenWidth = %f, screenHeight = %f, scale= %f", screenWidth, screenHeight, scale);
    
    int horizontalGap = screenWidth - gridlength - SHADOW_THICKNESS;
    
    int vOffset = (screenHeight - gridlength - SHADOW_THICKNESS)/2;
    int hOffset = horizontalGap / 2;

    int xOffset = (int)location.x - hOffset;
    int yOffset = (int)location.y - vOffset;
    
    int gridx = xOffset / cellSize;
    int gridy = yOffset / cellSize;
    
    if (gridx >= 0 && gridx < gridSize && gridy >= 0 && gridy < gridSize)
    {
        [self.delegate handleGameViewTapAtX:gridy andY:gridx];
    }
}

@end
