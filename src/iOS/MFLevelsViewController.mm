//
//  MFLevelsViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 31/1/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFLevelsViewController.h"
#import "MFGridInterface.h"
#import "MFGlobalInterface.h"
#import "MFGameViewController.h"
#import "MFGameConstants.h"
#import "MFUtils.h"

@interface MFLevelsViewController ()
{
    NSArray *mLevelButtons;
    NSArray *mLevelLabels;
    NSArray *mLevelImageViews;
}

@property (strong, nonatomic) IBOutlet UILabel *mTitleLabel;

@property (strong, nonatomic) IBOutlet UIButton *mLevelButton1;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton2;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton3;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton4;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton5;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton6;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton7;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton8;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton9;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton10;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton11;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton12;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton13;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton14;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton15;
@property (strong, nonatomic) IBOutlet UIButton *mLevelButton16;

@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel1;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel2;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel3;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel4;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel5;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel6;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel7;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel8;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel9;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel10;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel11;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel12;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel13;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel14;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel15;
@property (strong, nonatomic) IBOutlet UILabel *mLevelLabel16;

@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView1;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView2;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView3;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView4;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView5;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView6;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView7;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView8;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView9;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView10;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView11;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView12;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView13;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView14;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView15;
@property (strong, nonatomic) IBOutlet UIImageView *mLevelImageView16;

@end

@implementation MFLevelsViewController


/*********************  Init / Setup Routines **************************/

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setupLists];
    
    [self setupUI];
}

-(void)setupLists
{
    /**
     Initialize the buttons, lables and imageview arrays
     **/
    mLevelButtons = [NSArray arrayWithObjects:self.mLevelButton1, self.mLevelButton2, self.mLevelButton3, self.mLevelButton4,
                     self.mLevelButton5, self.mLevelButton6, self.mLevelButton7, self.mLevelButton8,
                     self.mLevelButton9, self.mLevelButton10, self.mLevelButton11, self.mLevelButton12,
                     self.mLevelButton13, self.mLevelButton14, self.mLevelButton15, self.mLevelButton16, nil];
    mLevelLabels = [NSArray arrayWithObjects:self.mLevelLabel1, self.mLevelLabel2, self.mLevelLabel3, self.mLevelLabel4,
                    self.mLevelLabel5, self.mLevelLabel6, self.mLevelLabel7, self.mLevelLabel8,
                    self.mLevelLabel9, self.mLevelLabel10, self.mLevelLabel11, self.mLevelLabel12,
                    self.mLevelLabel13, self.mLevelLabel14, self.mLevelLabel15, self.mLevelLabel16, nil];
    mLevelImageViews = [NSArray arrayWithObjects:self.mLevelImageView1, self.mLevelImageView2, self.mLevelImageView3, self.mLevelImageView4,
                        self.mLevelImageView5, self.mLevelImageView6, self.mLevelImageView7, self.mLevelImageView8,
                        self.mLevelImageView9, self.mLevelImageView10, self.mLevelImageView11, self.mLevelImageView12,
                        self.mLevelImageView13, self.mLevelImageView14, self.mLevelImageView15, self.mLevelImageView16, nil];
}

/**
 Set up the UI for current page.
 **/
-(void)setupUI
{
    /**
     Determine the number of level buttons to be shown
     on the current screen.
     **/
    int numScreens = [MFUtils getNumScreensFromNumLevels:self.numLevels WithPerScreen:NUM_LEVELS_PER_SCREEN];
    int numLevelsOnThisScreen = 0;
    if (self.pageIndex + 1 < numScreens)
    {
        numLevelsOnThisScreen = NUM_LEVELS_PER_SCREEN;
    }
    else
    {
        if (self.numLevels % NUM_LEVELS_PER_SCREEN == 0)
        {
            numLevelsOnThisScreen = NUM_LEVELS_PER_SCREEN;
        }
        else
        {
            numLevelsOnThisScreen = self.numLevels % NUM_LEVELS_PER_SCREEN;
        }
    }
    
    /**
     Image used to indicate level status.
     **/
    UIImage *lockImage = [UIImage imageNamed:@"ic_iap_lock.png"];
    UIImage *completedImage = [UIImage imageNamed:@"ic_iap_tick.png"];
    UIImage *playedImage = [UIImage imageNamed:@"ic_iap_unlocked.png"];
    
    /**
     Read preferences to get the last played level and the last completed level
     **/
    NSUserDefaults * defaults = [NSUserDefaults standardUserDefaults];
    int lastUnlockedLevel = (int)[defaults integerForKey:@PREFERENCE_LAST_UNLOCKED_LEVEL];
    int lastCompletedLevel = (int)[defaults integerForKey:@PREFERENCE_LAST_COMPLETED_LEVEL];
    
    /**
     Now, set up each level button with appropriate label (level number),
     lock status, and visibility status.
     **/
    for (int i = 1 ; i <= NUM_LEVELS_PER_SCREEN; i++)
    {
        UIButton *button = [mLevelButtons objectAtIndex:i-1];
        UILabel *label = [mLevelLabels objectAtIndex:i-1];
        UIImageView *imageView = [mLevelImageViews objectAtIndex:i-1];
        
        int thisLevel = (int) self.pageIndex * NUM_LEVELS_PER_SCREEN + i;
        
        if (i <= numLevelsOnThisScreen)
        {
            button.hidden = NO;
            label.text = [NSString stringWithFormat:@"%d", thisLevel];
            
            //check for lock status
            if (true) //(thisLevel <= lastCompletedLevel)
            {
                [imageView setImage:completedImage];
                
                button.userInteractionEnabled = YES;
            }
            else if (thisLevel <= lastUnlockedLevel)
            {
                [imageView setImage:playedImage];
                
                button.userInteractionEnabled = YES;
            }
            else
            {
                [imageView setImage:lockImage];
                
                button.userInteractionEnabled = NO;
            }
        }
        else
        {
            button.hidden = YES;
        }
    }
}

/*********************  User Actions **************************/

/**
 A Level Button was tapped.
 **/
- (IBAction)startLevel:(id)sender {
    UIButton *button = (UIButton *)sender;
    MFGameViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"GameViewController"];
    controller.gameLevel = (int)self.pageIndex * NUM_LEVELS_PER_SCREEN + (int)button.tag;
    
    [self presentViewController:controller animated:YES completion:nil];
}

/**
 The X button was tapped.
 **/
- (IBAction)handleBackButton:(id)sender {
    [self dismissViewControllerAnimated:NO completion:nil];
}

@end
