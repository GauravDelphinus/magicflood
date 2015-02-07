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

@interface MFViewController ()
@property (strong, nonatomic) IBOutlet UIImageView *mLogoImageView;

@end

@implementation MFViewController
- (IBAction)launchGame:(id)sender {
    [self launchLevelsViewController];
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
    self.pageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height - 30);
    
    [self presentViewController:self.pageViewController animated:YES completion:nil];
    
    /*
    [self addChildViewController:_pageViewController];
    [self.view addSubview:_pageViewController.view];
    [self.pageViewController didMoveToParentViewController:self];
     */
    
    UIPageControl *pageControl = [UIPageControl appearance];
    pageControl.pageIndicatorTintColor = [UIColor lightGrayColor];
    pageControl.currentPageIndicatorTintColor = [UIColor blackColor];
    pageControl.backgroundColor = [UIColor whiteColor];

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
    NSUInteger index = ((MFLevelsViewController *) viewController).pageIndex;
    NSLog(@"\nbefore view controller, got index %d", index);
    if ((index == 0) || (index == NSNotFound)) {
        return nil;
    }
    
    
    index--;
    NSLog(@"returning index %d", index);
    return [self viewControllerAtIndex:index];
}

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController
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

- (NSInteger)presentationCountForPageViewController:(UIPageViewController *)pageViewController
{
    int numScreens = self.numLevels / NUM_LEVELS_PER_SCREEN;
    return numScreens;
}

- (NSInteger)presentationIndexForPageViewController:(UIPageViewController *)pageViewController
{
    return 0;
}

@end
