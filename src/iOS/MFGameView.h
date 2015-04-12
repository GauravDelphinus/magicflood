//
//  MFGameView.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>


@protocol GameViewTapHandler
@required
// list of required methods
-(void)handleGameViewTapAtX:(int)x andY:(int)y;
-(void)handleDragBeginAtX:(int)x Y:(int)y Row:(int)row Col:(int)col;
-(void)handleDragMoveAtX:(int)x Y:(int)y Row:(int)row Col:(int)col;
-(void)handleDragEndAtX:(int)x Y:(int)y Row:(int)row Col:(int)col;
-(BOOL)isBridgeValidWithStartRow:(int)startRow startCol:(int)startCol endRow:(int)endRow endCol:(int)endCol;
-(void)finalizeBridgeWithStartRow:(int) startRow startCol:(int)startCol endRow:(int)endRow endCol:(int)endCol;
@end

/**
 The actual UIView that renders the game grid
 **/
@interface MFGameView : UIView

@property (nonatomic,strong) id <GameViewTapHandler> delegate; //the delegate that implements the GameViewTapHandler protocol
@property int mCurrentAngleOfStartPosition; //current rotation angle
@property int mCurrentStarSize; //current star size.  -5 to -1 == initial, 0 == regular, 1 == large (will start with initial for a few seconds, and then star alternating between regular and large to give a "blink" effect)

-(void)initializeGameData:(int **)grid WithSize:(int)size WithNumStartPos:(int)numStartPos WithStartPos:(int **)startpos WithMaxMoves:(int)maxmoves;
-(void)freeGameData;
-(void)updateGameData:(int **)grid;
-(void)updateStartPos:(int **)startPos withNum:(int)numStartPos;
-(void)enableDisableTouchInput:(BOOL)enable;
-(void)enterExitBrigeBuildingMode:(BOOL)enter ResetData:(BOOL)reset;
-(void)setBridgeValid:(BOOL)valid;
-(void)setBridgeExtremesMinRow:(int)minRow minCol:(int)minCol maxRow:(int)maxRow maxCol:(int)maxCol;
@end


