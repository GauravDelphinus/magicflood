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
    
    UIViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"HelpRootViewController"];
    
    [self presentViewController:controller animated:YES completion:nil];
    
    /*
    
    UIPageControl *pageControl = [UIPageControl appearance];
    pageControl.pageIndicatorTintColor = [UIColor lightGrayColor];
    pageControl.currentPageIndicatorTintColor = [UIColor whiteColor];
    pageControl.backgroundColor = [UIColor clearColor];
     */
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
    UIViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"LevelsRootViewController"];
    
    [self presentViewController:controller animated:YES completion:nil];
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

//hide status bar
- (BOOL)prefersStatusBarHidden {
    return YES;
}


@end
