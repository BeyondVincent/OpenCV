//
//  BVViewController.m
//  OpenCVFaceDetect
//
//  Created by BeyondVincent on 13-5-18.
//  Copyright (c) 2013年 BeyondVincent. All rights reserved.
//

#import "BVViewController.h"
#import "BVImageHelper.h"
#import <AVFoundation/AVFoundation.h>

@interface BVViewController ()

@end

@implementation BVViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)loadImage:(id)sender
{
    self.originalImage.image = [UIImage imageNamed:@"111"];
}

- (IBAction)detectFace:(id)sender
{
    self.resultImage.image = [BVImageHelper opencvFaceDetect:self.originalImage.image];
}

@end
