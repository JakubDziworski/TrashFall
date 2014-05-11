

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
				  ../../Classes/AchvDisplayer.cpp \
				  ../../Classes/StatsDisplayer.cpp \
				 ../../Classes/Animated.cpp \
				 ../../Classes/LoadingNode.cpp \
				 ../../Classes/Bomb.cpp \
				 ../../../cocos2dx/platform/android/jni/JniURL.cpp \
				 ../../../cocos2dx/platform/android/jni/JniAdManager.cpp

                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../../cocos2dx/platform/android/jni

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static

            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) $(call import-module,cocos2dx)
