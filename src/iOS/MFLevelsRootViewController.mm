//
//  MFLevelsRootViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 14/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFLevelsRootViewController.h"
#import "MFGlobalInterface.h"
#import "MFGridInterface.h"
#import "MFUtils.h"

@interface MFLevelsRootViewController ()
@property (strong, nonatomic) IBOutlet UIButton *mCancelButton;
@property (strong, nonatomic) IBOutlet UILabel *mTitleLabel;
@property (strong, nonatomic) UIPageViewController *pageViewController;
@property int numLevels;
@end

@implementation MFLevelsRootViewController

/*********************  Init / Setup Routines **************************/

- (void)viewDidLoad {
    [super viewDidLoad];

    self.numLevels = getNumLevels();
    
    [self setupPageViewController];
    
    [MFUtils setBackgroundImage:self];
}

-(void)setupPageViewController
{
    // Create page view controller
    self.pageViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"PageViewController"];
    self.pageViewController.dataSource = self;
    
    //set up children
    MFLevelsViewController *startingViewController = [self viewControllerAtIndex:0];
    NSArray *viewControllers = @[startingViewController];
    [self.pageViewController setViewControllers:viewControllers direction:UIPageViewControllerNavigationDirectionForward animated:NO completion:nil];
    self.pageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
    
    //add to root view controller
    [self addChildViewController:self.pageViewController];
    [self.view addSubview: self.pageViewController.view];
    [self.view bringSubviewToFront:self.pageViewController.view];
    
    //now bring the cancel button and title label to the front, so we can SEE them!
    [self.view bringSubviewToFront:self.mCancelButton];
    [self.view bringSubviewToFront:self.mTitleLabel];
    
    //set up page control's color
    [MFUtils setupPageControl:self.pageViewController];
}

/*********************  User Actions **************************/

- (IBAction)dismissScreen:(id)sender {
    [self dismissViewControllerAnimated:NO completion:nil];
}

/*********************  Page View Controller Callbacks **************************/

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerBeforeViewController:(UIViewController *)viewController
{
    NSUInteger index = ((MFLevelsViewController *) viewController).pageIndex;
    if ((index == 0) || (index == NSNotFound)) {
        return nil;
    }
    
    index--;
    return [self viewControllerAtIndex:index];
}

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController
{
    NSUInteger index = ((MFLevelsViewController*) viewController).pageIndex;
    
    if (index == NSNotFound) {
        return nil;
    }
    
    int numScreens = [MFUtils getNumScreensFromNumLevels:self.numLevels WithPerScreen:NUM_LEVELS_PER_SCREEN];
    index++;
    if (index == numScreens) {
        return nil;
    }
    return [self viewControllerAtIndex:index];
}

- (MFLevelsViewController *)viewControllerAtIndex:(NSUInteger)index
{
    int numScreens = [MFUtils getNumScreensFromNumLevels:self.numLevels WithPerScreen:NUM_LEVELS_PER_SCREEN];
    if (index >= numScreens) {
        return nil;
    }
    
    // Create a new view controller and pass suitable data.
    MFLevelsViewController *pageContentViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"PageContentViewController"];
    
    pageContentViewController.pageIndex = index;
    pageContentViewController.numLevels = self.numLevels;
    
    return pageContentViewController;
}

- (NSInteger)presentationCountForPageViewController:(UIPageViewController *)pageViewController
{
    int numScreens = [MFUtils getNumScreensFromNumLevels:self.numLevels WithPerScreen:NUM_LEVELS_PER_SCREEN];
    return numScreens;
}

- (NSInteger)presentationIndexForPageViewController:(UIPageViewController *)pageViewController
{
    return 0;
}

/*********************  System Callbacks **************************/

//hide status bar
- (BOOL)prefersStatusBarHidden {
    return YES;
}

@end
