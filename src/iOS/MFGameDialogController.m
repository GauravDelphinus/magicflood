//
//  MFGameDialogController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 7/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFGameDialogController.h"
#import "MFGameViewController.h"

@interface MFGameDialogController ()

@end

@implementation MFGameDialogController
- (IBAction)positiveAction1ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_1];
    [self dismiss];
}
- (IBAction)positiveAction2ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_2];
    [self dismiss];
}
- (IBAction)positiveAction3ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_3];
    [self dismiss];
}
- (IBAction)positiveAction4ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_4];
    [self dismiss];
}
- (IBAction)positiveAction5ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_POSITIVE_ACTION_5];
    [self dismiss];
}
- (IBAction)negativeAction1ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_1];
    [self dismiss];
}
- (IBAction)negativeAction2ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_2];
    [self dismiss];
}
- (IBAction)negativeAction3ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_3];
    [self dismiss];
}
- (IBAction)negativeAction4ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_4];
    [self dismiss];
}
- (IBAction)negativeAction5ButtonPressed:(id)sender {
    MFGameViewController *controller = self.delegate;
    [controller gameDialogOptionSelected:self.dialogType WithOption:GAME_DIALOG_NEGATIVE_ACTION_5];
    [self dismiss];
}


-(void)dismiss
{
    [UIView animateWithDuration:0.3f animations:^{
        self.view.alpha = 0.0f;
    } completion:^(BOOL finished) {
        [self.view removeFromSuperview];
        [self removeFromParentViewController];
    }];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
