LOCAL_PATH := $(call my-dir)
PROJECT_ROOT := $(LOCAL_PATH)/../../..

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(PROJECT_ROOT)/src/Common
LOCAL_C_INCLUDES += $(PROJECT_ROOT)/src/Common

LOCAL_MODULE := magicflood
LOCAL_SRC_FILES := MainActivityJNI.cpp
LOCAL_SRC_FILES += MFGameActivityJNI.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFGrid.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFGlobalInterface.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFGridInterface.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFObstacle.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFIAPInterface.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFInAppProduct.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFNativeLog.cpp
LOCAL_SRC_FILES += $(PROJECT_ROOT)/src/Common/MFGridData.cpp
LOCAL_SRC_FILES += MFInAppPurchaseManagerJNI.cpp

#LOCAL_SHARED_LIBRARIES += libstlport
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
