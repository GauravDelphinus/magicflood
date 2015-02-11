//
//  MFViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import "MFViewController.h"
#import "MFGameViewController.h"
#import "MFIAPInterface.h"
#import "MFGridInterface.h"
#import "MFLevelsViewController.h"
#import "MFGlobalInterface.h"
#import "MFGameConstants.h"
#import "MFHelpScreenViewController.h"

@interface MFViewController ()
@property (strong, nonatomic) IBOutlet UIImageView *mLogoImageView;

@end

@implementation MFViewController
- (IBAction)launchGame:(id)sender {
    [self launchLevelsViewController];
}

- (IBAction)launchHelpScreens:(id)sender {
    // Create page view controller
    self.helpPageViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"HelpPageViewController"];
    self.helpPageViewController.dataSource = self;
    
    MFHelpScreenViewController *startingViewController = [self helpViewControllerAtIndex:0];
    NSArray *viewControllers = @[startingViewController];
    [self.helpPageViewController setViewControllers:viewControllers direction:UIPageViewControllerNavigationDirectionForward animated:NO completion:nil];
    
    // Change the size of page view controller
    //self.pageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height - 30);
    self.helpPageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
    //self.pageViewController.view.backgroundColor = [[UIColor blueColor] colorWithAlphaComponent:0.5f];
    //self.pageViewController.view.backgroundColor = [UIColor blueColor];
    
    [self presentViewController:self.helpPageViewController animated:YES completion:nil];
    
    /*
     [self addChildViewController:_pageViewController];
     [self.view addSubview:_pageViewController.view];
     [self.pageViewController didMoveToParentViewController:self];
     */
    
    //find the UIPageControl and set the number of pages
    /*
    NSArray *subviews = self.helpPageViewController.view.subviews;
    UIPageControl *thisControl = nil;
    for (int i=0; i<[subviews count]; i++) {
        if ([[subviews objectAtIndex:i] isKindOfClass:[UIPageControl class]]) {
            thisControl = (UIPageControl *)[subviews objectAtIndex:i];
            
            thisControl.numberOfPages = NUM_HELP_SCREENS;
        }
    }
    */
    
    UIPageControl *pageControl = [UIPageControl appearance];
    pageControl.pageIndicatorTintColor = [UIColor lightGrayColor];
    pageControl.currentPageIndicatorTintColor = [UIColor whiteColor];
    pageControl.backgroundColor = [UIColor clearColor];
}

- (IBAction)launchAboutScreen:(id)sender {
    UIViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"AboutViewController"];
    
    //[button setBackgroundColor:[UIColor yellowColor]];
    //add background image
    UIImage* _backGround = [UIImage imageNamed:@"bg_sky_blue.png"];
    UIImageView* _backGroundView = [[UIImageView alloc] initWithImage:_backGround];
    
    _backGroundView.frame = self.view.frame;
    _backGroundView.contentMode = UIViewContentModeScaleToFill;
    
    [controller.view addSubview:_backGroundView];
    [controller.view sendSubviewToBack:_backGroundView];
    
    [self presentViewController:controller animated:YES completion:nil];

}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    [self initializeInAppPurchase];
    
    [self initializePreferences];
    
    UIImage *logoImage = [UIImage imageNamed:@"iOS/iPhone/ic_logo_big"];
    [self.mLogoImageView initWithImage:logoImage];
    
    self.numLevels = getNumLevels();

    //[self launchLevelsViewController];
    
    //[self.view setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"bg_sky_blue.png"]]];
    UIImage* _backGround = [UIImage imageNamed:@"bg_sky_blue.png"];
    UIImageView* _backGroundView = [[UIImageView alloc] initWithImage:_backGround];
    
    _backGroundView.frame = self.view.frame;
    _backGroundView.contentMode = UIViewContentModeScaleToFill;
    
    [self.view addSubview:_backGroundView];
    [self.view sendSubviewToBack:_backGroundView];
    
    //some visual touch-ups
    self.mPlayButton.layer.cornerRadius = 5;
    self.mPlayButton.layer.masksToBounds = YES;
    [self.mPlayButton setBackgroundColor:[[UIColor blackColor] colorWithAlphaComponent:0.5f]];
    
    self.mHowToPlayButton.layer.cornerRadius = 5;
    self.mHowToPlayButton.layer.masksToBounds = YES;
    [self.mHowToPlayButton setBackgroundColor:[[UIColor blackColor] colorWithAlphaComponent:0.5f]];
    
    self.mAboutButton.layer.cornerRadius = 5;
    self.mAboutButton.layer.masksToBounds = YES;
    [self.mAboutButton setBackgroundColor:[[UIColor blackColor] colorWithAlphaComponent:0.5f]];
}

-(void)initializePreferences
{
    NSString *defaultPrefsFile = [[NSBundle mainBundle] pathForResource:@PREFERENCE_KEY ofType:@"plist"];
    NSDictionary *defaultPreferences = [NSDictionary dictionaryWithContentsOfFile:defaultPrefsFile];
    [[NSUserDefaults standardUserDefaults] registerDefaults:defaultPreferences];
}

-(void)launchLevelsViewController
{
    // Create page view controller
    self.pageViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"PageViewController"];
    self.pageViewController.dataSource = self;
    
    MFLevelsViewController *startingViewController = [self viewControllerAtIndex:0];
    NSArray *viewControllers = @[startingViewController];
    [self.pageViewController setViewControllers:viewControllers direction:UIPageViewControllerNavigationDirectionForward animated:NO completion:nil];
    
    // Change the size of page view controller
    NSLog(@"launchLevels, width = %d, height = %d", self.view.frame.size.width, self.view.frame.size.height);
    //self.pageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height - 30);
    self.pageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
    //self.pageViewController.view.backgroundColor = [[UIColor blueColor] colorWithAlphaComponent:0.5f];
    
    
    [self presentViewController:self.pageViewController animated:YES completion:nil];
    
    /*
    [self addChildViewController:_pageViewController];
    [self.view addSubview:_pageViewController.view];
    [self.pageViewController didMoveToParentViewController:self];
     */
    
    //page control's color
    UIPageControl *pageControl = [UIPageControl appearance];
    pageControl.pageIndicatorTintColor = [UIColor lightGrayColor];
    pageControl.currentPageIndicatorTintColor = [UIColor whiteColor];
    pageControl.backgroundColor = [UIColor clearColor];

}

-(void)initializeInAppPurchase
{
    addInAppProduct(IAP_REMOVE_ADS, "Remove Ads", "Remove Ads", "0", "0", false);
    addInAppProduct(IAP_COINS_FIRST, "Add 500 Coins", "Add 500 Coins", "0", "0",  false);
    addInAppProduct(IAP_COINS_SECOND, "Add 1000 Coins", "Add 1000 Coins", "0", "0",  false);
    addInAppProduct(IAP_COINS_THIRD, "Add 2500 Coins", "Add 2500 Coins", "0", "0",  false);
    addInAppProduct(IAP_COINS_FOURTH, "Add 5000 Coins", "Add 5000 Coins", "0", "0",  false);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/**
 Called when the view controller is about to load the MFGameViewController
 **/
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    UIButton *button = (UIButton *)sender;
    if (button.tag == 100)
    {
        [self launchLevelsViewController];
    }
    else{
    MFGameViewController *controller = (MFGameViewController *)segue.destinationViewController;
    
    //controller.gameLevel = button.tag;
    controller.gameLevel = 33;
    }
   
}

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerBeforeViewController:(UIViewController *)viewController
{
    if ([viewController isKindOfClass:MFLevelsViewController.class])
    {
    NSUInteger index = ((MFLevelsViewController *) viewController).pageIndex;
    NSLog(@"\nbefore view controller, got index %d", index);
    if ((index == 0) || (index == NSNotFound)) {
        return nil;
    }
    
    
    index--;
    NSLog(@"returning index %d", index);
    return [self viewControllerAtIndex:index];
    }
    else if ([viewController isKindOfClass:MFHelpScreenViewController.class])
    {
        NSUInteger index = ((MFLevelsViewController*) viewController).pageIndex;
        
        if ((index == 0) || (index == NSNotFound)) {
            return nil;
        }

        index --;
        
        return [self helpViewControllerAtIndex:index];
    }
    
    return nil;
}

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController
{
    if ([viewController isKindOfClass:MFLevelsViewController.class])
    {
        NSUInteger index = ((MFLevelsViewController*) viewController).pageIndex;
        NSLog(@"\nafter view controller, got index %d", index);
        
        if (index == NSNotFound) {
            return nil;
        }
        
        int numScreens = self.numLevels / NUM_LEVELS_PER_SCREEN;
        NSLog(@"numScreens = %d", numScreens);
        index++;
        if (index == numScreens) {
            return nil;
        }
        NSLog(@"returning index %d", index);
        return [self viewControllerAtIndex:index];
    }
    else if ([viewController isKindOfClass:MFHelpScreenViewController.class])
    {
        NSUInteger index = ((MFLevelsViewController*) viewController).pageIndex;
        
        index ++;
        if (index == NUM_HELP_SCREENS)
        {
            return nil;
        }
        
        return [self helpViewControllerAtIndex:index];
    }
    
    return nil;
}

- (MFLevelsViewController *)viewControllerAtIndex:(NSUInteger)index
{
    NSLog(@"viewControllerAtIndex %d", index);
    int numScreens = self.numLevels / NUM_LEVELS_PER_SCREEN;
    if (index >= numScreens || index < 0) {
        return nil;
    }
    
    // Create a new view controller and pass suitable data.
    MFLevelsViewController *pageContentViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"PageContentViewController"];
    
    NSString *titleText = [NSString stringWithFormat:@"Levels"];
    
    pageContentViewController.titleText = titleText;
    pageContentViewController.pageIndex = index;
    pageContentViewController.numLevels = self.numLevels;
    
    return pageContentViewController;
}


- (MFHelpScreenViewController *)helpViewControllerAtIndex:(NSUInteger)index
{
    NSLog(@"viewControllerAtIndex %d", index);
    if (index >= NUM_HELP_SCREENS || index < 0) {
        return nil;
    }
    
    // Create a new view controller and pass suitable data.
    NSString *boardID = [NSString stringWithFormat:@"HelpScreenViewController%d", index + 1];
    MFHelpScreenViewController *pageContentViewController = [self.storyboard instantiateViewControllerWithIdentifier:boardID];
    pageContentViewController.pageIndex = index;
    
    return pageContentViewController;
}


- (NSInteger)presentationCountForPageViewController:(UIPageViewController *)pageViewController
{
    if (pageViewController == self.pageViewController)
    {
        int numScreens = self.numLevels / NUM_LEVELS_PER_SCREEN;
        return numScreens;
    }
    else if (pageViewController == self.helpPageViewController)
    {
        return NUM_HELP_SCREENS;
    }
    
    return 0;
}

- (NSInteger)presentationIndexForPageViewController:(UIPageViewController *)pageViewController
{
    return 0;
}

@end
