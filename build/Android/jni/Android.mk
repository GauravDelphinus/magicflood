LOCAL_PATH := $(call my-dir)
PROJECT_ROOT := $(LOCAL_PATH)/../../..

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(PROJECT_ROOT)/src/Common
LOCAL_MODULE := magicflood
LOCAL_SRC_FILES := MFGameActivityJNI.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFGrid.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFGridInterface.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFObstacle.cpp

include $(BUILD_SHARED_LIBRARY)
