//
//  MFViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import "MFViewController.h"
#import "MFGameConstants.h"

@interface MFViewController ()

@property (strong, nonatomic) IBOutlet UILabel *mPlayGameButtonLabel;
@property (strong, nonatomic) IBOutlet UILabel *mHowToPlayButtonLabel;
@property (strong, nonatomic) IBOutlet UILabel *mAboutButtonLabel;

@end

@implementation MFViewController

/*********************  Init / Setup Routines **************************/

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self initializePreferences];
    
    [self setupStrings];
    
    [self setupBackground];
}

/**
 Set the DEFAULT preferences, for use when there's nothing
 set.  Picked from MFGameConstants.h
 **/
-(void)initializePreferences
{
    // set defaults
    NSDictionary *userDefaultsDefaults = [NSDictionary dictionaryWithObjectsAndKeys:
                                          [NSNumber numberWithInt:DEFAULT_LAST_UNLOCKED_LEVEL], @PREFERENCE_LAST_UNLOCKED_LEVEL,
                                          [NSNumber numberWithInt:DEFAULT_LAST_PLAYED_LEVEL], @PREFERENCE_LAST_PLAYED_LEVEL,
                                          [NSNumber numberWithInt:DEFAULT_LAST_COMPLETED_LEVEL], @PREFERENCE_LAST_COMPLETED_LEVEL,
                                          [NSNumber numberWithInt:INITIAL_COINS_ALLOCATED], @PREFERENCE_TOTAL_COINS_EARNED,
                                          [NSNumber numberWithBool:YES], @PREFERENCE_SOUND,
                                          [NSNumber numberWithBool:NO], @PREFERENCE_ADS_REMOVED,
                                          nil];
    [[NSUserDefaults standardUserDefaults] registerDefaults:userDefaultsDefaults];
}

-(void)setupStrings
{
    NSString *playGameButtonText = NSLocalizedStringFromTable (@"play_game_text", nil, @"");
    [self.mPlayGameButtonLabel setText:playGameButtonText];
    
    NSString *howToPlayButtonText = NSLocalizedStringFromTable (@"how_to_play_game_text", nil, @"");
    [self.mPlayGameButtonLabel setText:howToPlayButtonText];
    
    NSString *aboutButtonText = NSLocalizedStringFromTable (@"about_game_text", nil, @"");
    [self.mPlayGameButtonLabel setText:aboutButtonText];
}

/**
 Set the background image.
 **/
-(void)setupBackground
{
    UIImage* _backGround = [UIImage imageNamed:@"bg_sky_blue.png"];
    UIImageView* _backGroundView = [[UIImageView alloc] initWithImage:_backGround];
    
    _backGroundView.frame = self.view.frame;
    _backGroundView.contentMode = UIViewContentModeScaleToFill;
    
    [self.view addSubview:_backGroundView];
    [self.view sendSubviewToBack:_backGroundView];
}

/*********************  User Actions **************************/

/**
 Launch the Levels Screen to start the game play.
 **/
- (IBAction)launchGame:(id)sender {
    UIViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"LevelsRootViewController"];
    
    [self presentViewController:controller animated:YES completion:nil];
}

/**
 Launch the How to Play Screen.
 **/
- (IBAction)launchHelpScreens:(id)sender {
    
    UIViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"HelpRootViewController"];
    
    [self presentViewController:controller animated:YES completion:nil];
}

/**
 Launch the About Screen.
 **/
- (IBAction)launchAboutScreen:(id)sender {
    UIViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"AboutViewController"];
    
    [self presentViewController:controller animated:YES completion:nil];

}

/*********************  System Callbacks **************************/

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//hide status bar
- (BOOL)prefersStatusBarHidden
{
    return YES;
}


@end
