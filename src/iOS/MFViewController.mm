//
//  MFViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 20/11/14.
//  Copyright (c) 2014 EzeeIdeas. All rights reserved.
//

#import "MFViewController.h"
#import "MFGameConstants.h"
#import "MFUtils.h"

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
        
    [MFUtils setBackgroundImage:self darkenBackground:NO];
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
                                          [NSNumber numberWithBool:NO], @PREFERENCE_STARS_UNLOCKED,
                                          [NSNumber numberWithBool:NO], @PREFERENCE_HURDLE_SMASHERS_UNLOCKED,
                                          [NSNumber numberWithInt:INITIAL_STARS_ALLOCATED], @PREFERENCE_TOTAL_STARS_EARNED,
                                          [NSNumber numberWithInt:INITIAL_HURDLE_SMASHERS_ALLOCATED], @PREFERENCE_TOTAL_HURDLE_SMASHERS_EARNED,
                                          [NSNumber numberWithInt:INITIAL_BRIDGES_ALLOCATED], @PREFERENCE_TOTAL_BRIDGES_EARNED,
                                          [NSNumber numberWithInt:0], @PREFERENCE_STAR_PLACEMENT_COUNT,
                                          [NSNumber numberWithInt:0], @PREFERENCE_HURDLE_SMASHER_PLACEMENT_COUNT,
                                          [NSNumber numberWithInt:0], @PREFERENCE_BRIDGE_PLACEMENT_COUNT,
                                          nil];
    [[NSUserDefaults standardUserDefaults] registerDefaults:userDefaultsDefaults];
}

/*********************  User Actions **************************/

/**
 Launch the Levels Screen to start the game play.
 **/
- (IBAction)launchGame:(id)sender {
    UIViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"LevelsRootViewController"];
    
    controller.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    [self presentViewController:controller animated:YES completion:nil];
}

/**
 Launch the How to Play Screen.
 **/
- (IBAction)launchHelpScreens:(id)sender {
    
    UIViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"HelpRootViewController"];
    
    controller.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    [self presentViewController:controller animated:YES completion:nil];
}

/**
 Launch the About Screen.
 **/
- (IBAction)launchAboutScreen:(id)sender {
    UIViewController *controller = [self.storyboard instantiateViewControllerWithIdentifier:@"AboutViewController"];
    
    controller.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    [self presentViewController:controller animated:YES completion:nil];

}

/*********************  System Callbacks **************************/

//hide status bar
- (BOOL)prefersStatusBarHidden
{
    return YES;
}


@end
