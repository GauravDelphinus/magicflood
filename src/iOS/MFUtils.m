//
//  MFUtils.m
//  Magic Flood
//
//  Created by Anukrity Jain on 19/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MFUtils.h"

@implementation MFUtils : NSObject

+(UIImageView *)getBackgroundImage:(UIViewController *)controller
{
    //add background image
    UIImage* _backGround = [UIImage imageNamed:@"bg_sky_blue.png"];
    UIImageView* backgroundView = [[UIImageView alloc] initWithImage:_backGround];
    
    backgroundView.frame = controller.view.frame;
    backgroundView.contentMode = UIViewContentModeScaleToFill;
    
    return backgroundView;
}

+(void)setupPageControl:(UIPageViewController *)controller
{
    NSArray *subviews = controller.view.subviews;
    UIPageControl *pageControl = nil;
    for (int i=0; i<[subviews count]; i++) {
        if ([[subviews objectAtIndex:i] isKindOfClass:[UIPageControl class]]) {
            pageControl = (UIPageControl *)[subviews objectAtIndex:i];
            
            pageControl.pageIndicatorTintColor = [UIColor darkGrayColor];
            pageControl.currentPageIndicatorTintColor = [UIColor whiteColor];
            pageControl.backgroundColor = [UIColor clearColor];
        }
    }
}

@end