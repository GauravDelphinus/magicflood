//
//  MFHelpRootViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 12/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFHelpRootViewController.h"
#import "MFHelpScreenViewController.h"
#import "MFGameConstants.h"

@interface MFHelpRootViewController ()
@property (strong, nonatomic) IBOutlet UIButton *mCancelButton;

@end

@implementation MFHelpRootViewController
- (IBAction)dismissScreen:(id)sender {
    [self dismissViewControllerAnimated:NO completion:nil];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
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
    
    //add background image
    UIImage* _backGround = [UIImage imageNamed:@"bg_sky_blue.png"];
    UIImageView* _backGroundView = [[UIImageView alloc] initWithImage:_backGround];
    
    _backGroundView.frame = self.view.frame;
    _backGroundView.contentMode = UIViewContentModeScaleToFill;
    
    [self.view addSubview:_backGroundView];
    
    
    [self addChildViewController:self.helpPageViewController];
    [self.view addSubview: self.helpPageViewController.view];
    [self.view bringSubviewToFront:self.helpPageViewController.view];
    
    //now bring the cancel button to the front, so we can SEE it!
    [self.view bringSubviewToFront:self.mCancelButton];
    
    //[self presentViewController:self.helpPageViewController animated:YES completion:nil];
    
    //page control's color
    NSArray *subviews = self.helpPageViewController.view.subviews;
    UIPageControl *pageControl = nil;
    for (int i=0; i<[subviews count]; i++) {
        if ([[subviews objectAtIndex:i] isKindOfClass:[UIPageControl class]]) {
            pageControl = (UIPageControl *)[subviews objectAtIndex:i];
            
            pageControl.pageIndicatorTintColor = [UIColor lightGrayColor];
            pageControl.currentPageIndicatorTintColor = [UIColor whiteColor];
            pageControl.backgroundColor = [UIColor clearColor];
        }
    }

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


- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerBeforeViewController:(UIViewController *)viewController
{
            NSUInteger index = ((MFHelpScreenViewController*) viewController).pageIndex;
        
        if ((index == 0) || (index == NSNotFound)) {
            return nil;
        }
        
        index --;
        
        return [self helpViewControllerAtIndex:index];
    

}

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController
{
        NSUInteger index = ((MFHelpScreenViewController*) viewController).pageIndex;
        
        index ++;
        if (index == NUM_HELP_SCREENS)
        {
            return nil;
        }
        
        return [self helpViewControllerAtIndex:index];
    

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

        return NUM_HELP_SCREENS;

}

- (NSInteger)presentationIndexForPageViewController:(UIPageViewController *)pageViewController
{
    return 0;
}


@end
