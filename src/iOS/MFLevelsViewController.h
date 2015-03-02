//
//  MFLevelsViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 31/1/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MFLevelsViewController : UIViewController

@property NSUInteger pageIndex; //page index of this view controller (in its parent page view controller)
@property NSUInteger numLevels; //total number of levels (used by this controller to determine how to show the level buttons)

@end

#define NUM_LEVELS_PER_SCREEN 16