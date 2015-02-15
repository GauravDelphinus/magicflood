//
//  MFAboutViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 12/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFAboutViewController.h"
#import "MFIAPManager.h"

@interface MFAboutViewController ()

@end

@implementation MFAboutViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)dismissScreen:(id)sender {
    [self dismissViewControllerAnimated:NO completion:nil];
}
- (IBAction)restorePurchases:(id)sender {
    MFIAPManager *iapManager = [[MFIAPManager alloc] init];
    
    
}
- (IBAction)launchFacebook:(id)sender {
    NSURL *facebookURL = [NSURL URLWithString:@"fb://profile/1410732689221094"];
    if ([[UIApplication sharedApplication] canOpenURL:facebookURL]) {
        [[UIApplication sharedApplication] openURL:facebookURL];
    } else {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://facebook.com/magicfloodgame"]];
    }
}
- (IBAction)launchItunesStore:(id)sender {
    NSString *iTunesLink = @"itms://itunes.apple.com/us/app/apple-store/id469337564?mt=8f";
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:iTunesLink]];
}
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

- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{
    //Add an alert in case of failure
    [self dismissViewControllerAnimated:YES completion:nil];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
