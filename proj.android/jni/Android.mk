

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := helloworld/main.cpp \
                  ../../Classes/AppDelegate.cpp \
                  ../../Classes/MainMenu.cpp \
				  ../../Classes/Utils.cpp \
				  ../../Classes/Trash.cpp \
				  ../../Classes/Game.cpp \
				  ../../Classes/HUD.cpp \
				  ../../Classes/Background.cpp \
				  ../../Classes/SpriteWithText.cpp \
				  ../../Classes/Pause.cpp \
				  ../../Classes/GameOver.cpp \
				  ../../Classes/AchievmentPopUp.cpp \
				  ../../Classes/AchievmentDisplayer.cpp

                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   
APP_PLATFORM := android-10
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static

NDK_MODULE_PATH := $(LOCAL_PATH)/../ndk-modules
            
include $(BUILD_SHARED_LIBRARY)
$(call import-add-path,/cygdrive/d/Cocos2_0/cocos2dx)
$(call import-add-path,/cygdrive/d/Cocos2_0/cocos2dx/platform/third_party/android/prebuilt)
$(call import-module,CocosDenshion/android) $(call import-module,cocos2dx)
