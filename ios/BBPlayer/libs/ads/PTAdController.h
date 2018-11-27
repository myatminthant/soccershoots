#ifndef PTADCONTROLLER_H
#define PTADCONTROLLER_H

#include "ads/PTAdObject.h"

#define PTAdControllerCallbackSelector(_SELECTOR) (PTAdControllerCallback)(&_SELECTOR)
typedef void (cocos2d::CCObject::*PTAdControllerCallback)();

class PTAdController
{
public:
    PTAdController();

    static PTAdController* shared();

    void initAdNetworks();

    bool isBannerVisible();

    void showBanner( const char* adNetworkId );
    void hideBanner();
    void showInterstitial( const char* adNetworkId );
    void hideInterstitial( );

    void showRewardedVideo(const char* adNetworkId);
    void rewardedVideoDidEnd();
    bool isRewardedVideoAvialable(const char *adNetworkId);

    void bannerDidFail(const char* adNetworkId);
    void interstitialDidFail(const char* adNetworkId);

    void setMusic( bool value );


    PTAdObject* bannerObject(const char* adNetworkId);
    PTAdObject* intesrtitialObject(const char* adNetworkId);
    PTAdObject* rewardedVideoObject(const char* adNetworkId);

    const char* bannerBackup(const char* adNetworkId);
    const char* interstitialBackup(const char* adNetworkId);

    void setTarget(cocos2d::CCObject *listener, PTAdControllerCallback selector);

private:
    PTAdObject* _adBanner;
    PTAdObject* _adInterstitial;
    PTAdObject* _adRewardedVideo;

    cocos2d::CCObject *_callbackListener;
    PTAdControllerCallback _callbackSelector;
};

#endif // PTADCONTROLLER_H
