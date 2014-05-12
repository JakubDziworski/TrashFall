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

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;

import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;
import android.widget.LinearLayout;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxEditText;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxRenderer;

import android.app.ActivityManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ConfigurationInfo;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup.LayoutParams;


public class TrashFall extends Cocos2dxActivity{
	private Cocos2dxGLSurfaceView mGLView;
	 //MOJE
    static Activity me = null;
    static AdView adView;
	private static final String AD_UNIT_ID = "ca-app-pub-5237730302123518/6004792589";

    static void showAdmobJNI(){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				adView.setVisibility(View.VISIBLE);
			}
		});
	}
    static void hideAdmobJNI(){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				adView.setVisibility(View.INVISIBLE);
			}
		});
    }
  //MOJE
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		me = this;
		if (detectOpenGLES20()) {
			// get the packageName,it's used to set the resource path
			String packageName = getApplication().getPackageName();
			super.setPackageName(packageName);
			
            // FrameLayout
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

            // Cocos2dxGLSurfaceView
	        mGLView = new Cocos2dxGLSurfaceView(this);

            // ...add to FrameLayout
	        framelayout.addView(edittext);
            framelayout.addView(mGLView);
            AdRequest adRequest = new AdRequest.Builder()
            .addTestDevice("51811170E1DCAFF84F4A72E88C453812")
            .build();
        // Start loading the ad in the background.
	        mGLView.setEGLContextClientVersion(2);
	        mGLView.setCocos2dxRenderer(new Cocos2dxRenderer());
            mGLView.setTextField(edittext);
            // Set framelayout as the content view
            try{
            adView = new AdView(this);
    	    adView.setAdSize(AdSize.BANNER);
    	    adView.setAdUnitId(AD_UNIT_ID);
			setContentView(framelayout);
			adView.loadAd(adRequest);
			adView.setBackgroundColor(Color.BLACK);
            FrameLayout.LayoutParams adParams = new FrameLayout.LayoutParams(
                    FrameLayout.LayoutParams.WRAP_CONTENT, 
                    FrameLayout.LayoutParams.WRAP_CONTENT, 
                    Gravity.BOTTOM |Gravity.CENTER_HORIZONTAL);
            addContentView(adView, adParams);
            adView.setBackgroundColor(0);
            }
            catch(Exception e){
            	Log.d("","ADMOB error: " + e);
            }
			
		}
		else {
			Log.d("activity", "don't support gles2.0");
			finish();
		}
	}
	@Override
	 protected void onPause() {
	     super.onPause();
	     mGLView.onPause();
	 }

	 @Override
	 protected void onResume() {
	     super.onResume();
	     mGLView.onResume();
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


