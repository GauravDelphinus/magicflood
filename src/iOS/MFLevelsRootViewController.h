//
//  MFLevelsRootViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 14/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MFLevelsViewController.h"

@interface MFLevelsRootViewController : UIViewController <UIPageViewControllerDataSource>

@property (strong, nonatomic) UIPageViewController *pageViewController;
@property int numLevels;
@end
