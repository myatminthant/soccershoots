#import "AdIntegrator.h"

@implementation AdIntegrator

+ (id)shared{
    static AdIntegrator* integrator = nil;
    @synchronized(self){
        if(integrator == nil){
            integrator = [[self alloc] init];
        }
    }
    return integrator;
}

#pragma mark Core Methods

- (void)initAds{
    NSLog(@"[Ads] initialization");
}

-(void)showBanner{
    NSLog(@"[Ads] show banner");
}

-(void)hideBanner{
    NSLog(@"[Ads] hide banner");
}

-(bool)isBannerVisible{
    return true;
}

-(bool)isRewardedVideoAvialable{
    return true;
}

-(void)showInterstitial{
    NSLog(@"[Ads] show interstitial");
}

-(void)showRewardedVideo{
    NSLog(@"[Ads] show rewarded video");
}

#pragma mark Integration

@end

