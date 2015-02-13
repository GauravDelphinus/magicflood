//
//  MFLevelsRootViewController.m
//  Magic Flood
//
//  Created by Anukrity Jain on 14/2/15.
//  Copyright (c) 2015 EzeeIdeas. All rights reserved.
//

#import "MFLevelsRootViewController.h"
#import "MFGlobalInterface.h"
#import "MFGridInterface.h"

@interface MFLevelsRootViewController ()
@property (strong, nonatomic) IBOutlet UIButton *mCancelButton;
@property (strong, nonatomic) IBOutlet UILabel *mTitleLabel;

@end

@implementation MFLevelsRootViewController
- (IBAction)dismissScreen:(id)sender {
    [self dismissViewControllerAnimated:NO completion:nil];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.numLevels = getNumLevels();
    
    // Create page view controller
    self.pageViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"PageViewController"];
    self.pageViewController.dataSource = self;
    
    MFLevelsViewController *startingViewController = [self viewControllerAtIndex:0];
    NSArray *viewControllers = @[startingViewController];
    [self.pageViewController setViewControllers:viewControllers direction:UIPageViewControllerNavigationDirectionForward animated:NO completion:nil];
    
    // Change the size of page view controller
    NSLog(@"launchLevels, width = %d, height = %d", self.view.frame.size.width, self.view.frame.size.height);
    //self.pageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height - 30);
    self.pageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
    //self.pageViewController.view.backgroundColor = [[UIColor blueColor] colorWithAlphaComponent:0.5f];
    
    
    //[self presentViewController:self.pageViewController animated:YES completion:nil];
    //add background image
    UIImage* _backGround = [UIImage imageNamed:@"bg_sky_blue.png"];
    UIImageView* _backGroundView = [[UIImageView alloc] initWithImage:_backGround];
    
    _backGroundView.frame = self.view.frame;
    _backGroundView.contentMode = UIViewContentModeScaleToFill;
    
    [self.view addSubview:_backGroundView];
    
    
    [self addChildViewController:self.pageViewController];
    [self.view addSubview: self.pageViewController.view];
    [self.view bringSubviewToFront:self.pageViewController.view];
    
    //now bring the cancel button and title label to the front, so we can SEE them!
    [self.view bringSubviewToFront:self.mCancelButton];
    [self.view bringSubviewToFront:self.mTitleLabel];
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
    if ([viewController isKindOfClass:MFLevelsViewController.class])
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
    
    return nil;
}

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController
{
    if ([viewController isKindOfClass:MFLevelsViewController.class])
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
       return nil;
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
    if (pageViewController == self.pageViewController)
    {
        int numScreens = self.numLevels / NUM_LEVELS_PER_SCREEN;
        return numScreens;
    }
    
    
    return 0;
}

- (NSInteger)presentationIndexForPageViewController:(UIPageViewController *)pageViewController
{
    return 0;
}


@end
