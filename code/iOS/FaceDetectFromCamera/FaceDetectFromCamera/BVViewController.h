//
//  BVViewController.h
//  FaceDetectFromCamera
//
//  Created by BeyondVincent on 13-5-19.
//  Copyright (c) 2013年 BeyondVincent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVCaptureOutput.h>

@interface BVViewController : UIViewController<AVCaptureVideoDataOutputSampleBufferDelegate>
@property (weak, nonatomic) IBOutlet UIImageView *originalImage;
@property (weak, nonatomic) IBOutlet UIImageView *resultImage;

@property (nonatomic) BOOL flag;

- (IBAction)openCamera:(id)sender;
- (IBAction)startDetect:(id)sender;

@end
