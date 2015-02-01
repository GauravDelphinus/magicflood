//
//  MFViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MFGameViewController.h"

@interface MFViewController : UIViewController <UIPageViewControllerDataSource>
- (IBAction)startWalkthrough:(id)sender;
@property (strong, nonatomic) UIPageViewController *pageViewController;
@property int numLevels;
-(void)initializeInAppPurchase;
@end


