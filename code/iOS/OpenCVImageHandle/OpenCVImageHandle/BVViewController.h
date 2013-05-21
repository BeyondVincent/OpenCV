//
//  BVViewController.h
//  OpenCVImageHandle
//
//  Created by BeyondVincent on 13-5-18.
//  Copyright (c) 2013年 BeyondVincent. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BVViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIImageView *originalImage;
@property (weak, nonatomic) IBOutlet UIImageView *HSVImage;
@property (weak, nonatomic) IBOutlet UIImageView *GRAYImage;
@property (weak, nonatomic) IBOutlet UIImageView *BINARYImage;

@property (weak, nonatomic) IBOutlet UISlider *binarySlider;

- (IBAction)showOriginalImage:(id)sender;
- (IBAction)showHSVImage:(id)sender;
- (IBAction)showGRAYImage:(id)sender;
- (IBAction)showBINARYImage:(id)sender;

- (IBAction)thresholdValueChange:(id)sender;


@end
