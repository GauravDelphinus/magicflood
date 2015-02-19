//
//  MFUIButton.m
//  Magic Flood
//
//  Created by Anukrity Jain on 8/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFUIButton.h"
#import "MFUtils.h"

@interface MFUIButton ()
@property UIColor *normalColor; //normal color (non-pressed) picked from the XIB
@end

@implementation MFUIButton

- (id)initWithCoder:(NSCoder *)decoder
{
    self = [super initWithCoder:decoder];

    self.normalColor = self.backgroundColor;
    self.layer.cornerRadius = 5;
    self.layer.masksToBounds = YES;
    
    return self;
}

/**
 Show a different tinge when button is pressed.
 **/
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
