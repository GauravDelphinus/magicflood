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

@interface MFLevelsViewController ()
@property (strong, nonatomic) IBOutlet UILabel *mTitleLabel;

@end

@implementation MFLevelsViewController
- (IBAction)handleBackButton:(id)sender {
    [self dismissViewControllerAnimated:NO completion:nil];
}
- (IBAction)launchGame:(id)sender {
    //MFGameViewController *controller = (MFGameViewController *)segue.destinationViewController;
    MFGameViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"GameViewController"];
    UIButton *button = (UIButton *)sender;
    controller.gameLevel = self.pageIndex * NUM_LEVELS_PER_SCREEN + button.tag;
    
    [self presentViewController:controller animated:YES completion:nil];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        [self initialize];
    }
    return self;
}

-(void) initialize
{

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
    
    for (int i = 1 ; i <= NUM_LEVELS_PER_SCREEN; i++)
    {
        UIButton *button = [mLevelButtons objectAtIndex:i-1];
        if (i <= numLevelsOnThisScreen)
        {
            button.hidden = NO;
            button.titleLabel.text = [NSString stringWithFormat:@"%d", (self.pageIndex * NUM_LEVELS_PER_SCREEN + i)];
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

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
