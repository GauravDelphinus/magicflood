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
@end

/**
 The actual UIView that renders the game grid
 **/
@interface MFGameView : UIView

@property (nonatomic,strong) id <GameViewTapHandler> delegate; //the delegate that implements the GameViewTapHandler protocol
@property int mCurrentAngleOfStartPosition; //current rotation angle

-(void)initializeGameData:(int **)grid WithSize:(int)size WithNumStartPos:(int)numStartPos WithStartPos:(int **)startpos WithMaxMoves:(int)maxmoves;
-(void)updateGameData:(int **)grid;
-(void)updateStartPos:(int **)startPos withNum:(int)numStartPos;
-(void)enableDisableTouchInput:(BOOL)enable;

@end


