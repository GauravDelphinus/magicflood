//
//  MFUtils.h
//  Magic Flood
//
//  Created by Anukrity Jain on 19/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#ifndef Magic_Flood_MFUtils_h
#define Magic_Flood_MFUtils_h

#import <Foundation/Foundation.h>

@interface MFUtils : NSObject
+(void)setBackgroundImage:(UIViewController *)controller darkenBackground:(BOOL)darken;
+(void)setupPageControl:(UIPageViewController *)controller;
+(NSString *)formatIAPPrice:(NSNumber *)price WithLocale:(NSLocale *)locale;
+(int)getNumScreensFromNumLevels:(int)numLevels WithPerScreen:(int)numLevelsPerScreen;
@end

#define UIColorFromRGB(rgbValue) \
[UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0x00FF00) >>  8))/255.0 \
blue:((float)((rgbValue & 0x0000FF) >>  0))/255.0 \
alpha:1.0]

#define UIColorFromARGB(argbValue) \
[UIColor colorWithRed:((float)((argbValue & 0x00FF0000) >> 16))/255.0 \
green:((float)((argbValue & 0x0000FF00) >>  8))/255.0 \
blue:((float)((argbValue & 0x000000FF) >>  0))/255.0 \
alpha:((float)((argbValue & 0xFF000000) >>  24))/255.0]

#endif
