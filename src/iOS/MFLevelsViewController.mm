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

#define UIColorFromRGB(rgbValue) \
[UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0x00FF00) >>  8))/255.0 \
blue:((float)((rgbValue & 0x0000FF) >>  0))/255.0 \
alpha:1.0]

#define UIColorFromARGB(argbValue) \
[UIColor colorWithRed:((float)((argbValue & 0x00FF0000) >> 16))/255.0 \
green:((float)((argbValue & 0x0000FF00) >>  8))/255.0 \
blue:((float)((argbValue & 0x000000FF) >>  0))/255.0 \
alpha:((float)((argbValue & 0xFF000000) >>  0))/255.0]

@interface MFLevelsViewController ()

@property (strong, nonatomic) IBOutlet UILabel *mTitleLabel;
@property (strong, nonatomic) IBOutlet UIButton *mBackButton;

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
- (IBAction)handleBackButton:(id)sender {
    [self dismissViewControllerAnimated:NO completion:nil];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSLog(@"viewDidLoad, index = %d", self.pageIndex);
    // Do any additional setup after loading the view.
    self.mTitleLabel.text = self.titleText;
    
    UIPageControl *pageControl = [UIPageControl appearance];
    pageControl.pageIndicatorTintColor = [UIColor lightGrayColor];
    pageControl.currentPageIndicatorTintColor = [UIColor blackColor];
    pageControl.backgroundColor = [UIColor whiteColor];
    
    /**
     Now correct all the button for this page index.
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
    
    int numScreens = self.numLevels / NUM_LEVELS_PER_SCREEN;
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
    
    UIImage *lockImage = [UIImage imageNamed:@"ic_iap_lock.png"];
    UIImage *completedImage = [UIImage imageNamed:@"ic_iap_tick.png"];
    UIImage *playedImage = [UIImage imageNamed:@"ic_iap_unlocked.png"];
    
    [self.mTitleLabel setFont:[UIFont fontWithName:@"ArchitectsDaughter" size:15]];
    [self.mBackButton.titleLabel setFont:[UIFont fontWithName:@"ArchitectsDaughter" size:15]];
    
    /**
     Read preferences to get the last played level and the last completed level
     **/
    NSUserDefaults * defaults = [NSUserDefaults standardUserDefaults];
    int lastUnlockedLevel = [defaults integerForKey:@PREFERENCE_LAST_UNLOCKED_LEVEL];
    int lastCompletedLevel = [defaults integerForKey:@PREFERENCE_LAST_COMPLETED_LEVEL];
    
    
    for (int i = 1 ; i <= NUM_LEVELS_PER_SCREEN; i++)
    {
        UIButton *button = [mLevelButtons objectAtIndex:i-1];
        UILabel *label = [mLevelLabels objectAtIndex:i-1];
        UIImageView *imageView = [mLevelImageViews objectAtIndex:i-1];
        
        int thisLevel = self.pageIndex * NUM_LEVELS_PER_SCREEN + i;
        
        if (i <= numLevelsOnThisScreen)
        {
            button.hidden = NO;
            //button.titleLabel.text = [NSString stringWithFormat:@"%d", (self.pageIndex * NUM_LEVELS_PER_SCREEN + i)];
            label.text = [NSString stringWithFormat:@"%d", thisLevel];
            label.textColor = [UIColor whiteColor];
            [label setFont:[UIFont fontWithName:@"ArchitectsDaughter" size:25]];
            
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
            
            //some visual touch-ups
            button.layer.cornerRadius = 5;
            button.layer.masksToBounds = YES;
            [button setBackgroundColor:[[UIColor blackColor] colorWithAlphaComponent:0.5f]];
            
        }
        else
        {
            button.hidden = YES;
        }
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)startLevel:(id)sender {
    UIButton *button = (UIButton *)sender;
    MFGameViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"GameViewController"];
    controller.gameLevel = self.pageIndex * NUM_LEVELS_PER_SCREEN + button.tag;
    
    //[button setBackgroundColor:[UIColor yellowColor]];
    
    [self presentViewController:controller animated:YES completion:nil];
    NSLog(@"startLevel, finished");
}

@end
