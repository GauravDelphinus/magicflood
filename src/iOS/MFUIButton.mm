//
//  MFUIButton.m
//  Magic Flood
//
//  Created by Anukrity Jain on 8/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFUIButton.h"

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

@implementation MFUIButton

- (id)initWithCoder:(NSCoder *)decoder
{
    self = [super initWithCoder:decoder];

    self.normalColor = self.backgroundColor;
    self.layer.cornerRadius = 5;
    self.layer.masksToBounds = YES;
    
    return self;
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
    //[super drawRect:rect];
    NSLog(@"drawRect called");
    //if (self.highlighted == YES)
    {
        CGContextRef context = UIGraphicsGetCurrentContext();
        CGRect rectangle = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, self.frame.size.height);
        CGContextAddRect(context, rectangle);
        //CGContextSetLineWidth(context, 2);
        //CGContextSetStrokeColorWithColor(context, [UIColor whiteColor].CGColor);
        //CGContextStrokePath(context);
        CGContextSetFillColorWithColor(context, [UIColor redColor].CGColor);
        CGContextFillRect(context, rectangle);
    }
}
*/
- (void) setHighlighted:(BOOL)highlighted {
    [super setHighlighted:highlighted];
    
    if (highlighted) {
        self.backgroundColor = UIColorFromARGB(0x99FFCC00); //slight golden transparent highlight color
    }
    else {
        self.backgroundColor = self.normalColor;
    }
}

@end
