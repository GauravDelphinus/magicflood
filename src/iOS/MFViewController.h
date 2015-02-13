//
//  MFViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MFGameViewController.h"

@interface MFViewController : UIViewController
@property (strong, nonatomic) IBOutlet UIButton *mAboutButton;
@property (strong, nonatomic) IBOutlet UIButton *mHowToPlayButton;
@property (strong, nonatomic) IBOutlet UIButton *mPlayButton;
- (IBAction)startWalkthrough:(id)sender;

@property int numLevels;
-(void)initializeInAppPurchase;
-(void)initializePreferences;
@end


