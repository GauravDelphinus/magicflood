//
//  MFGameDialogController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 7/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFGameDialogController.h"

@interface MFGameDialogController ()
@property (strong, nonatomic) IBOutlet UIView *dialogView;

@end

@implementation MFGameDialogController

/*********************  Init / Setup Routines **************************/

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.dialogView.layer.cornerRadius = 10;
    self.dialogView.layer.masksToBounds = YES;
}

/*********************  Dialog Button Callback Actions **************************/

- (IBAction)positiveAction1ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_1];
    [self dismiss];
}
- (IBAction)positiveAction2ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_2];
    [self dismiss];
}
- (IBAction)positiveAction3ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_3];
    [self dismiss];
}
- (IBAction)positiveAction4ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_4];
    [self dismiss];
}
- (IBAction)positiveAction5ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_5];
    [self dismiss];
}
- (IBAction)negativeAction1ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_1];
    [self dismiss];
}
- (IBAction)negativeAction2ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_2];
    [self dismiss];
}
- (IBAction)negativeAction3ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_3];
    [self dismiss];
}
- (IBAction)negativeAction4ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_4];
    [self dismiss];
}
- (IBAction)negativeAction5ButtonPressed:(id)sender {
    [self.delegate gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_5];
    [self dismiss];
}

/**
 Dismiss the dialog by removing the view, and show
 a fade out animation.
 **/
-(void)dismiss
{
    [UIView animateWithDuration:0.3f animations:^{
        self.view.alpha = 0.0f;
    } completion:^(BOOL finished) {
        [self.view removeFromSuperview];
        [self removeFromParentViewController];
    }];
    
    //release references
    self.delegate = nil;
    
    self.mIAPManager.mQueryDelegate = nil; //unregister the query delegate
    self.mIAPManager = nil;
}


@end
