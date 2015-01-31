//
//  MFGameViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MFGameView.h"
#import <StoreKit/StoreKit.h>

@interface MFGameViewController : UIViewController <UIAlertViewDelegate, GameViewTapHandler, SKProductsRequestDelegate>
{
}

@property int gameLevel; //set by the calling MFViewController
@property BOOL mStarPlacementMode;
@property BOOL mHurdleSmasherMode;
@property NSArray *products;

-(int)GetColorCodeFromUIColor:(UIColor *)color;
-(void)startNewGame;
-(void)updateCoinsLabel:(int)numCoins;
-(NSString *)formatIAPPrice:(NSNumber *)price WithLocale:(NSLocale *)locale;

@property UIAlertView *failAlertView, *successAlertView, *exitAlertView, *addMovesAlertView, *addStarAlertView, *addHurdleSmasherAlertView, *addCoinsAlertView;

@property long gridHandle; //handle to the grid object in C++ code
@end