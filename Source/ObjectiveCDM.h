//
//  ObjectiveCDM.h
//  ObjectiveCDM-Example
//
//  Created by James Huynh on 16/5/14.
//
//

#import <Foundation/Foundation.h>
#import "ObjectiveCDMDownloadBatch.h"
#import "ObjectiveCDMDownloadTask.h"
#import "BEReachability.h"

typedef BEReachability Reachability;

@class ObjectiveCDMDownloadBatch;
@protocol ObjectiveCDMUIDelegate;
@protocol ObjectiveCDMDataDelegate;

@interface ObjectiveCDM : NSObject <NSURLSessionDownloadDelegate> {
    NSURLSession *downloadSession;
    ObjectiveCDMDownloadBatch* currentBatch;
    int64_t initialDownloadedBytes;
    int64_t totalBytes;
    Reachability *internetReachability;
}

+ (instancetype) sharedInstance;
- (void) setInitialDownloadedBytes:(int64_t)initialDownloadedBytes;
- (void) setTotalBytes:(int64_t)totalBytes;
- (void) downloadBatch:(NSArray *)arrayOfDownloadInformation;
- (NSArray *) addBatch:(NSArray *)arrayOfDownloadInformation;
- (NSArray *) downloadingTasks;
- (void) startDownloadingCurrentBatch;
- (ObjectiveCDMDownloadTask *) addDownloadTask:(NSDictionary *)dictionary;
- (void) cancelAllOutStandingTasks;
- (void) continueInCompletedDownloads;
- (void) suspendAllOnGoingDownloads;
- (BOOL) isDownloading;
- (NSArray *) downloadRateAndRemainingTime;

@property(nonatomic, assign) FileHashAlgorithm fileHashAlgorithm;
@property(nonatomic, retain) id<ObjectiveCDMUIDelegate> uiDelegate;
@property(nonatomic, retain) id<ObjectiveCDMDataDelegate> dataDelegate;

@end

@protocol ObjectiveCDMUIDelegate <NSObject>

@required
- (void) didFinishAll;

@optional
- (void) didReachProgress:(float)progress;
- (void) didHitDownloadErrorOnTask:(ObjectiveCDMDownloadTask* ) task;
- (void) didFinishOnDownloadTaskUI:(ObjectiveCDMDownloadTask *) task;
- (void) didReachIndividualProgress:(float)progress onDownloadTask:(ObjectiveCDMDownloadTask* ) task;

@end

@protocol ObjectiveCDMDataDelegate <NSObject>

@required
- (void) didFinishAllForDataDelegate;

@optional
- (void) didFinishDownloadTask:(ObjectiveCDMDownloadTask *)downloadInfo;

@end