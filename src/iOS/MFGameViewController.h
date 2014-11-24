//
//  MFGameViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MFGameViewController : UIViewController <UIAlertViewDelegate>

@property int gameLevel; //set by the calling MFViewController
-(int)GetColorCodeFromUIColor:(UIColor *)color;
-(void)startNewGame;

@property UIAlertView *failAlertView, *successAlertView, *exitAlertView;

@property long gridHandle; //handle to the grid object in C++ code
@end