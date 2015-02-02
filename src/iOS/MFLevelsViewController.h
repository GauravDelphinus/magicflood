//
//  MFLevelsViewController.h
//  Magic Flood
//
//  Created by Anukrity Jain on 31/1/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MFLevelsViewController : UIViewController
{
    NSArray *mLevelButtons;
    NSArray *mLevelLabels;
    NSArray *mLevelImageViews;
}

@property NSUInteger pageIndex;
@property NSString *titleText;
@property NSUInteger numLevels;

-(void) initialize;
@end
