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

#define SHADOW_THICKNESS 10


@interface MFGameView ()
{
    int **myGrid; //2-D array containing the grid colors.  Note: this is a heap-based array of integer pointers
    int gridSize; // order of game board
    int mNumStartPos; //number of start positions
    int **startPos; //array of start positions, each array has 2 integers. 0 = x, 1 = y
    int maxMoves; // max number of moves in this game
}

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
    
    [self drawGridShadowWithLeft:hOffset withTop:vOffset WithGridLength:gridlength];
}

/**
 Draw the shadow around the grid.
 **/
-(void)drawGridShadowWithLeft:(int)left withTop:(int)top WithGridLength:(int)gridlength
{
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    /** Right Shadow **/
    
    CGContextBeginPath(context);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGFloat locations[] = { 0.0, 1.0 };
    
    NSArray *colors = @[(__bridge id) [UIColor blackColor].CGColor, (__bridge id) [UIColor clearColor].CGColor];
    
    CGGradientRef gradient = CGGradientCreateWithColors(colorSpace, (__bridge CFArrayRef) colors, locations);
    
    CGContextSaveGState(context);
    CGRect rightShadowRect = CGRectMake(left + gridlength, top + SHADOW_THICKNESS, SHADOW_THICKNESS, gridlength - SHADOW_THICKNESS);
    
    CGPoint startPoint = CGPointMake(left + gridlength, top + SHADOW_THICKNESS);
    CGPoint endPoint = CGPointMake(left + gridlength + SHADOW_THICKNESS, top + SHADOW_THICKNESS);
    
    CGContextAddRect(context, rightShadowRect);
    CGContextClip(context);
    
    CGContextDrawLinearGradient(context, gradient, startPoint, endPoint, 0);
    
    CGContextRestoreGState(context);
    //CGContextSetLineWidth(context, 0.5);
    //CGContextSetStrokeColorWithColor(context, [UIColor
     //                                          blackColor].CGColor);
    //CGContextStrokePath(context);
    
    /** Bottom Shadow **/
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    CGRect bottomShadowRect = CGRectMake(left + SHADOW_THICKNESS, top + gridlength, gridlength - SHADOW_THICKNESS, SHADOW_THICKNESS);
     startPoint = CGPointMake(left + SHADOW_THICKNESS, top + gridlength);
 endPoint = CGPointMake(left + SHADOW_THICKNESS, top + gridlength + SHADOW_THICKNESS);
    
    CGContextAddRect(context, bottomShadowRect);
    CGContextClip(context);
    
    CGContextDrawLinearGradient(context, gradient, startPoint, endPoint, 0);
    CGContextRestoreGState(context);
   
    /** Left Corner **/
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    CGMutablePathRef path = CGPathCreateMutable();
    CGFloat startAngle = M_PI / 2;
    CGFloat endAngle = M_PI;
    CGPathMoveToPoint(path, NULL, left + SHADOW_THICKNESS, top + gridlength + SHADOW_THICKNESS);
    CGPathAddArc(path, NULL, left + SHADOW_THICKNESS, top + gridlength, SHADOW_THICKNESS, startAngle, endAngle, 0);
    CGPathAddLineToPoint(path, NULL, left, top + gridlength);
    CGPathAddLineToPoint(path, NULL, left + SHADOW_THICKNESS, top + gridlength);
    CGContextAddPath(context, path);
    CGPathCloseSubpath(path);
    CGContextClip(context);
    startPoint = CGPointMake(left + SHADOW_THICKNESS, top + gridlength);
    CGContextDrawRadialGradient (context, gradient, startPoint,
                                 0, startPoint, SHADOW_THICKNESS,
                                 0);
    CGContextRestoreGState(context);
    
    /** Bottom Right Corner **/
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    path = CGPathCreateMutable();
    startAngle = 0;
    endAngle = M_PI / 2;
    CGPathMoveToPoint(path, NULL, left + gridlength + SHADOW_THICKNESS, top + gridlength);
    CGPathAddArc(path, NULL, left + gridlength, top + gridlength, SHADOW_THICKNESS, startAngle, endAngle, 0);
    CGPathAddLineToPoint(path, NULL, left + gridlength, top + gridlength);
    CGPathAddLineToPoint(path, NULL, left + gridlength + SHADOW_THICKNESS, top + gridlength);
    CGContextAddPath(context, path);
    CGPathCloseSubpath(path);
    CGContextClip(context);
    startPoint = CGPointMake(left + gridlength, top + gridlength);
    CGContextDrawRadialGradient (context, gradient, startPoint,
                                 0, startPoint, SHADOW_THICKNESS,
                                 0);
    CGContextRestoreGState(context);

    /** Top Right Corner **/
    CGContextSaveGState(context);
    CGContextBeginPath(context);
    path = CGPathCreateMutable();
    startAngle = 3 * M_PI / 2;
    endAngle = 0;
    CGPathMoveToPoint(path, NULL, left + gridlength, top);
    CGPathAddArc(path, NULL, left + gridlength, top + SHADOW_THICKNESS, SHADOW_THICKNESS, startAngle, endAngle, 0);
    CGPathAddLineToPoint(path, NULL, left + gridlength, top + SHADOW_THICKNESS);
    CGPathAddLineToPoint(path, NULL, left + gridlength, top);
    CGContextAddPath(context, path);
    CGPathCloseSubpath(path);
    CGContextClip(context);
    startPoint = CGPointMake(left + gridlength, top + SHADOW_THICKNESS);
    CGContextDrawRadialGradient (context, gradient, startPoint,
                                 0, startPoint, SHADOW_THICKNESS,
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
    /*
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGRect rectangle = CGRectMake(left, top, cellSize, cellSize);
    CGContextAddRect(context, rectangle);
    CGContextSetLineWidth(context, 3.0);
    CGContextStrokePath(context);
     */
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
     Draw the gradient behind the star (in case of yellow cell) to improve
     visual identification of star.
     **/
    /*
    if (myGrid[x][y] == GRID_COLOR_YELLOW)
    {
        CGGradientRef gradient;
        CGColorSpaceRef colorspace;
        CGFloat locations[2] = { 0.0, 1.0};
        
        NSArray *colors = @[(id)UIColorFromRGB(0xFDFDFD).CGColor,
                            (id)[UIColor clearColor].CGColor];
        colorspace = CGColorSpaceCreateDeviceRGB();
        
        gradient = CGGradientCreateWithColors(colorspace,
                                              (CFArrayRef)colors, locations);
        
        CGPoint startPoint, endPoint;
        CGFloat startRadius, endRadius;
        startPoint.x = left + r;
        startPoint.y = top + r;
        endPoint.x = left + r;
        endPoint.y = top + r;
        startRadius = 0;
        endRadius = r;
        
        
        CGContextDrawRadialGradient (context, gradient, startPoint,
                                     startRadius, endPoint, endRadius,
                                     0);
    }
     */
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
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetLineWidth(context, 1.0);
    
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
