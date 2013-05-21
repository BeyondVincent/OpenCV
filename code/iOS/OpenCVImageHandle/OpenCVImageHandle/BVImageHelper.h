//
//  BVImageHelper.h
//  OpenCVImageHandle
//
//  Created by BeyondVincent on 13-5-18.
//  Copyright (c) 2013年 BeyondVincent. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BVImageHelper : NSObject

+ (cv::Mat)cvMatFromUIImage:(UIImage *)image;

+ (UIImage *)UIImageFromCVMat:(cv::Mat)cvMat;
@end
