/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.jakubdziworski.trashfalll;
import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.Chartboost.CBAgeGateConfirmation;
import com.chartboost.sdk.ChartboostDelegate;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxEditText;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxRenderer;


import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ConfigurationInfo;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.Toast;

import com.chartboost.sdk.*;
import com.chartboost.sdk.Model.CBError.CBClickError;
import com.chartboost.sdk.Model.CBError.CBImpressionError;
import com.heyzap.sdk.ads.HeyzapAds;
import com.heyzap.sdk.ads.HeyzapAds.OnStatusListener;
import com.heyzap.sdk.ads.HeyzapInterstitialActivity;
import com.heyzap.sdk.ads.InterstitialAd;

import com.playhaven.android.Placement;
import com.playhaven.android.PlacementListener;
import com.playhaven.android.PlayHaven;
import com.playhaven.android.PlayHavenException;
import com.playhaven.android.req.OpenRequest;
import com.playhaven.android.req.RequestListener;
import com.playhaven.android.view.FullScreen;
import com.playhaven.android.view.MoreGames;
import com.playhaven.android.view.PlayHavenListener;
import com.playhaven.android.view.PlayHavenView;
import com.playhaven.android.view.PlayHavenView.DismissType;
import com.playhaven.android.view.Windowed;
public class TrashFall extends Cocos2dxActivity{
	private Cocos2dxGLSurfaceView mGLView;
	 //MOJE
    static TrashFall me = null; //this activity
    public Chartboost cb;	//ads
	public Placement placement;
	static Boolean ignoreHeyZap;
	static Boolean requestToShow;
	//IN THIS METHOD THE MORE APPS SHOULD SHOW
    static void showAdmobJNI(){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				me.requestToShow=true;
				me.cb.showMoreApps();
			}
		});
	}
    static void hideAdmobJNI(){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
			//
			}
		});
    }
  //MOJE
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		me=this;
		requestToShow=false;
		ignoreHeyZap=false;
		if (detectOpenGLES20()) {
			// get the packageName,it's used to set the resource path
			String packageName = getApplication().getPackageName();
			super.setPackageName(packageName);

            // FrameLayoutx
            ViewGroup.LayoutParams framelayout_params =
                new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT,
                                           ViewGroup.LayoutParams.FILL_PARENT);
            FrameLayout framelayout = new FrameLayout(this);
            framelayout.setLayoutParams(framelayout_params);

            // Cocos2dxEditText layout
            ViewGroup.LayoutParams edittext_layout_params =
                new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT,
                                           ViewGroup.LayoutParams.WRAP_CONTENT);
            Cocos2dxEditText edittext = new Cocos2dxEditText(this);
            edittext.setLayoutParams(edittext_layout_params);

            // ...add to FrameLayout
            framelayout.addView(edittext);

            // Cocos2dxGLSurfaceView
	        mGLView = new Cocos2dxGLSurfaceView(this);

            // ...add to FrameLayout
            framelayout.addView(mGLView);

	        mGLView.setEGLContextClientVersion(2);
	        mGLView.setCocos2dxRenderer(new Cocos2dxRenderer());
            mGLView.setTextField(edittext);
           //REKAMY
           //heyzap
            HeyzapAds.start(me);
            HeyzapAds.setOnStatusListener(new OnStatusListener() {
				
				@Override
				public void onShow(String arg0) {
				}
				
				@Override
				public void onHide(String arg0) {
					
				}
				@Override
				public void onFailedToShow(String arg0) {
					if(me.requestToShow)
					me.startActivity(FullScreen.createIntent(me, me.placement));
				}
				
				@Override
				public void onFailedToFetch(String arg0) {
					me.ignoreHeyZap=true;
				}
				
				@Override
				public void onClick(String arg0) {
				}
				
				@Override
				public void onAvailable(String arg0) {
				}
				
				@Override
				public void onAudioStarted() {
				}
				
				@Override
				public void onAudioFinished() {
				}
			});
           //Configure UpSight
            try {
                PlayHaven.configure(this, "e4e702715ca44093b4e8252c6868a9a0", "552556b1064e4e99a004e876a5cc8986");
            } catch (PlayHavenException e) {   
                e.printStackTrace();
            }
            OpenRequest open = new OpenRequest();
            open.send(this);
            placement = new Placement("placement"); 
            placement.preload(this); 
        
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!CHARTBOOST PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // Configure Chartboost
            this.cb = Chartboost.sharedChartboost();
            String appId = "537a029889b0bb644bb33177";
            String appSignature = "17e5feea52e85552f80947909583bec1b7000f9b";
            this.cb.onCreate(this, appId, appSignature,  this.chDel);
            this.cb.startSession();
            this.cb.cacheMoreApps();
            CBPreferences.getInstance().setImpressionsUseActivities(true);
          //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!CHARTBOOST PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            
            // Set framelayout as the content view
			setContentView(framelayout);
		}
		else {
			Log.d("activity", "don't support gles2.0");
			finish();
		}	
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!CHARTBOOST PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	private ChartboostDefaultDelegate chDel = new ChartboostDefaultDelegate() {
		@Override
		public void didFailToLoadMoreApps(CBImpressionError arg0) {
			if(me.requestToShow){
				if(me.ignoreHeyZap)
				me.startActivity(FullScreen.createIntent(me, me.placement));
				else InterstitialAd.display(me);
			}
			
		}
	};
	 @Override
	 protected void onPause() {
	     super.onPause();
	     mGLView.onPause();
	 }

	 @Override 
	 protected void onStart(){
		 super.onStart();
		 this.cb.onStart(this);
	 }
	 @Override
	 protected void onResume() {
	     super.onResume();
	     mGLView.onResume();
	 }
	 @Override
	 protected void onDestroy() {
	     super.onDestroy();
	     this.cb.onDestroy(this);
	 }

	 @Override
	 public void onBackPressed() {
	     // If an interstitial is on screen, close it. Otherwise continue as normal.
	     if (this.cb.onBackPressed())
	         return;
	     else
	         super.onBackPressed();
	 }
	 private boolean detectOpenGLES20() 
	 {
	     ActivityManager am =
	            (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
	     ConfigurationInfo info = am.getDeviceConfigurationInfo();
	      return (info.reqGlEsVersion >= 0x20000);
	 }
     static {
         System.loadLibrary("game");
     }
}