//
//  BVViewController.h
//  OpenCVFaceDetect
//
//  Created by BeyondVincent on 13-5-18.
//  Copyright (c) 2013年 BeyondVincent. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BVViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIImageView *originalImage;
@property (weak, nonatomic) IBOutlet UIImageView *resultImage;

- (IBAction)loadImage:(id)sender;
- (IBAction)detectFace:(id)sender;

@end
