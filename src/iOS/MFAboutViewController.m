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
#import "MFGameConstants.h"

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
    NSURL *facebookURL = [NSURL URLWithString:@FACEBOOK_APP_URL];
    if ([[UIApplication sharedApplication] canOpenURL:facebookURL]) {
        //show the page in the Facebook App on the device
        [[UIApplication sharedApplication] openURL:facebookURL];
    } else {
        //show the facebook page in a web browser
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@FACEBOOK_PAGE_URL]];
    }
}

/**
 The Ratings button was pressed.  Launch iTunes App Store with the game page opened.
 **/
- (IBAction)launchItunesStore:(id)sender {
    NSString *iTunesLink = @ITUNES_APP_URL;
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:iTunesLink]];
}

/**
 The Email button was pressed.
 **/
- (IBAction)launchEmailFeedback:(id)sender {
    if ([MFMailComposeViewController canSendMail]) {
        MFMailComposeViewController *composeViewController = [[MFMailComposeViewController alloc] initWithNibName:nil bundle:nil];
        [composeViewController setMailComposeDelegate:self];
        [composeViewController setToRecipients:@[@FEEDBACK_EMAIL]];
        NSString *subject = nil;
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad)
        {
            
            subject = [NSString stringWithFormat:NSLocalizedString(@"feedback_email_subject", @""), "iPad"];
        }
        else
        {
            subject = [NSString stringWithFormat:NSLocalizedString(@"feedback_email_subject", @""), "iPhone"];
        }
        [composeViewController setSubject:subject];
        
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
