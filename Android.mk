LOCAL_PATH:= $(call my-dir)

#---------------------------
# hvrst
#---------------------------
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= hvrst.cpp
LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog

LOCAL_MODULE:= hvrst
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_INIT_RC := init.hvrst.rc
include $(BUILD_EXECUTABLE)
