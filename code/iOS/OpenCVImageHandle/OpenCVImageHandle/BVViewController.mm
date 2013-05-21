//
//  BVViewController.m
//  OpenCVImageHandle
//
//  Created by BeyondVincent on 13-5-18.
//  Copyright (c) 2013年 BeyondVincent. All rights reserved.
//

#import "BVViewController.h"
#import "BVImageHelper.h"

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

- (IBAction)showOriginalImage:(id)sender
{
    self.originalImage.image = [UIImage imageNamed:@"1"];
}

- (IBAction)showHSVImage:(id)sender
{
    cv::Mat hsvMat;
    
    cv::Mat inputMat = [BVImageHelper cvMatFromUIImage:[UIImage imageNamed:@"1"]];
    
    cv::cvtColor(inputMat, hsvMat, CV_BGR2HSV);
    
    UIImage *image = [BVImageHelper UIImageFromCVMat:hsvMat];
    self.HSVImage.image = image;
}

- (IBAction)showGRAYImage:(id)sender
{
    cv::Mat grayMat;
    
    cv::Mat inputMat = [BVImageHelper cvMatFromUIImage:[UIImage imageNamed:@"1"]];
    
    cv::cvtColor(inputMat, grayMat, CV_BGR2GRAY);
    
    UIImage *image = [BVImageHelper UIImageFromCVMat:grayMat];
    self.GRAYImage.image = image;
}

- (IBAction)showBINARYImage:(id)sender
{
    cv::Mat binaryMat;
    cv::Mat grayMat;
    cv::Mat inputMat = [BVImageHelper cvMatFromUIImage:[UIImage imageNamed:@"1"]];
    cv::cvtColor(inputMat, grayMat, CV_BGR2GRAY);
    
    cv::threshold(grayMat, binaryMat, self.binarySlider.value, 255, CV_THRESH_BINARY);
    
    UIImage *image = [BVImageHelper UIImageFromCVMat:binaryMat];
    self.BINARYImage.image = image;
}

- (IBAction)thresholdValueChange:(id)sender
{
    [self showBINARYImage:nil];
}
@end
