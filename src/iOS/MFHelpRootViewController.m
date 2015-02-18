//
//  MFHelpRootViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 12/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFHelpRootViewController.h"
#import "MFHelpScreenViewController.h"
#import "MFGameConstants.h"
#import "MFUtils.h"

@interface MFHelpRootViewController ()
@property (strong, nonatomic) IBOutlet UIButton *mCancelButton;
@property (strong, nonatomic) UIPageViewController *helpPageViewController;
@end

@implementation MFHelpRootViewController

/*********************  Init / Setup Routines **************************/

- (void)viewDidLoad {
    [super viewDidLoad];

    [self setupPageViewController];
    
    [self setupBackground];
}

-(void)setupBackground
{
    //add background image
    UIImageView *_backGroundView = [MFUtils getBackgroundImage:self];
    [self.view addSubview:_backGroundView];
    [self.view sendSubviewToBack:_backGroundView];
}

-(void)setupPageViewController
{
    // Create page view controller
    self.helpPageViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"HelpPageViewController"];
    self.helpPageViewController.dataSource = self;
    
    // set up children
    MFHelpScreenViewController *startingViewController = [self helpViewControllerAtIndex:0];
    NSArray *viewControllers = @[startingViewController];
    [self.helpPageViewController setViewControllers:viewControllers direction:UIPageViewControllerNavigationDirectionForward animated:NO completion:nil];
    self.helpPageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
    
    // add to root view controller
    [self addChildViewController:self.helpPageViewController];
    [self.view addSubview: self.helpPageViewController.view];
    [self.view bringSubviewToFront:self.helpPageViewController.view];
    
    //now bring the cancel button to the front, so we can SEE it!
    [self.view bringSubviewToFront:self.mCancelButton];
    
    //set up page control's color
    [MFUtils setupPageControl:self.helpPageViewController];
}

/*********************  User Actions **************************/

/**
 Cancel button pressed.
 **/
- (IBAction)dismissScreen:(id)sender {
    [self dismissViewControllerAnimated:NO completion:nil];
}

/*********************  Page View Controller Callbacks **************************/

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerBeforeViewController:(UIViewController *)viewController
{
    NSUInteger index = ((MFHelpScreenViewController*) viewController).pageIndex;
    
    if ((index == 0) || (index == NSNotFound)) {
        return nil;
    }
    
    index --;
    
    return [self helpViewControllerAtIndex:index];
}

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController
{
    NSUInteger index = ((MFHelpScreenViewController*) viewController).pageIndex;
    
    index ++;
    if (index == NUM_HELP_SCREENS)
    {
        return nil;
    }
    
    return [self helpViewControllerAtIndex:index];
}


- (MFHelpScreenViewController *)helpViewControllerAtIndex:(NSUInteger)index
{
    if (index >= NUM_HELP_SCREENS) {
        return nil;
    }
    
    // Create a new view controller and pass suitable data.
    NSString *boardID = [NSString stringWithFormat:@"HelpScreenViewController%lu", index + 1];
    MFHelpScreenViewController *pageContentViewController = [self.storyboard instantiateViewControllerWithIdentifier:boardID];
    pageContentViewController.pageIndex = index;
    
    return pageContentViewController;
}

- (NSInteger)presentationCountForPageViewController:(UIPageViewController *)pageViewController
{
    return NUM_HELP_SCREENS;
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
