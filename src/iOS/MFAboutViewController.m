//
//  MFAboutViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 12/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFAboutViewController.h"
#import "MFIAPManager.h"
#import "MFUtils.h"

@interface MFAboutViewController ()
@end

@implementation MFAboutViewController

/*********************  Init / Setup Routines **************************/

- (void)viewDidLoad {
    [super viewDidLoad];

    [MFUtils setBackgroundImage:self];
}

/*********************  User Actions **************************/

/**
 The X button was pressed.
 **/
- (IBAction)dismissScreen:(id)sender {
    [self dismissViewControllerAnimated:NO completion:nil];
}

/**
 The Restore Purchases button was pressed.
 **/
- (IBAction)restorePurchases:(id)sender {
    MFIAPManager *iapManager = [[MFIAPManager alloc] init];
    [iapManager restorePurchases];
}

/**
 The Facebook buttonw as pressed.
 **/
- (IBAction)launchFacebook:(id)sender {
    NSURL *facebookURL = [NSURL URLWithString:@"fb://profile/1410732689221094"];
    if ([[UIApplication sharedApplication] canOpenURL:facebookURL]) {
        [[UIApplication sharedApplication] openURL:facebookURL];
    } else {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://facebook.com/magicfloodgame"]];
    }
}

/**
 The Ratings button was pressed.
 **/
- (IBAction)launchItunesStore:(id)sender {
    NSString *iTunesLink = @"itms://itunes.apple.com/us/app/apple-store/id469337564?mt=8f";
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:iTunesLink]];
}

/**
 The Email button was pressed.
 **/
- (IBAction)launchEmailFeedback:(id)sender {
    if ([MFMailComposeViewController canSendMail]) {
        MFMailComposeViewController *composeViewController = [[MFMailComposeViewController alloc] initWithNibName:nil bundle:nil];
        [composeViewController setMailComposeDelegate:self];
        [composeViewController setToRecipients:@[@"ezeeideas@gmail.com"]];
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
        {
            [composeViewController setSubject:@"Feedback related to MagicFlood on iPad"];
        }
        else
        {
            [composeViewController setSubject:@"Feedback related to MagicFlood on iPhone"];
        }
        [self presentViewController:composeViewController animated:YES completion:nil];
    }
}

/**
 Callback from the email composer screen.
 **/
- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{
    //Add an alert in case of failure
    [self dismissViewControllerAnimated:YES completion:nil];
}

/*********************  System Callbacks **************************/

//hide status bar
- (BOOL)prefersStatusBarHidden {
    return YES;
}

@end
